#!/bin/sh

###
kill_all() {
    echo "==== Trapped by killall ===="
    exit 255
}
f_monitor() {
    inotifywait -m -r -e create ${MONITOR_PATH} | while read -r directory action file; do
        message="$(printf "[%s]%s    %s, %s%s" "$(date +%s)" "$(date +'%Y/%m/%d %T %Z')" "${action}" "${directory}" "${file}")"
        echo "${message}"
        echo "${message}" >>"${LOG_PATH}"

        if [ ${#MAIL_FROM} -eq 0 ] || [ ${#MAIL_TO} -eq 0 ]; then
            continue
        fi
        SMTP_SERVER="smtp://msa.hinet.net:25"
        curl -v --insecure "${SMTP_SERVER}" --mail-from "${MAIL_FROM}" --mail-rcpt "${MAIL_TO}" \
            -F '=(;type=multipart/alternative' \
            -F '=plain text message' -F '= <body><pre>'"${message}"'<br></pre></body>;type=text/html' -F '=)' \
            -H "Subject: [EdgeTest]${file} to SMB${OPTIONS} Server" -H "From: ${MAIL_FROM}" -H "To: ${MAIL_TO}" \
            >/dev/null 2>&1
    done
}

###
trap kill_all EXIT
[ ${#} -lt 1 ] && echo "Options: <v1|v2|v3> [MAIL_FROM] [MAIL_TO]" && exit 255
OPTIONS="${1}"
MAIL_FROM=""
MAIL_TO=""
if [ ${#} -ge 3 ]; then
    MAIL_FROM="${2}"
    MAIL_TO="${3}"
fi
echo "================================"
echo "SMB${OPTIONS} Server"
echo "From: ${MAIL_FROM}"
echo "To: ${MAIL_TO}"
echo "================================"
echo

###
MONITOR_PATH="/home"
SAMBA_PATH="/etc/samba"
LOG_PATH="/tmp/samba.log"
case "${OPTIONS}" in
"v1" | "v2" | "v3")
    mv ${SAMBA_PATH}/smb.conf ${SAMBA_PATH}/smb.ori
    cp ${SAMBA_PATH}/smb${OPTIONS}.conf ${SAMBA_PATH}/smb.conf
    service nmbd start
    service nmbd status
    echo
    service smbd start
    service smbd status
    echo

    # tree ${MONITOR_PATH}

    [ -e "${LOG_PATH}" ] && rm -f ${LOG_PATH}
    f_monitor &

    tail -f /dev/null
    ;;
"bash")
    bash
    ;;
*)
    echo "${OPTIONS}: Not Support Now"
    ;;
esac

exit 0
