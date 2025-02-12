#!/bin/sh

[ ${#} -lt 1 ] && echo "Options: <http|httpAuth|https|httpsAuth>" && exit 255
OPTION="${1}"
# echo "[${LINENO}]: ${OPTION}"

ProxySquidPath="/etc/squid"
ProxySquid="squid.conf.52"
ProxyConfig="${ProxySquidPath}/squid.conf"
ProxyRestart="service squid start"
case "${OPTION}" in
"http")
    ProxyFile="${ProxySquidPath}/${ProxySquid}.http"
    ProxyPort=3128
    TestProxy="http://${ProxyIP}:${ProxyPort}"
    ;;
"httpAuth")
    ProxyFile="${ProxySquidPath}/${ProxySquid}.httpAuth"
    ProxyPort=3128
    TestProxy="http://admin:password@${ProxyIP}:${ProxyPort}"
    ;;
"https")
    ProxyFile="${ProxySquidPath}/${ProxySquid}.https"
    ProxyPort=3129
    TestProxy="https://${ProxyIP}:${ProxyPort}"
    ;;
"httpsAuth")
    ProxyFile="${ProxySquidPath}/${ProxySquid}.httpsAuth"
    ProxyPort=3129
    TestProxy="https://admin:password@${ProxyIP}:${ProxyPort}"
    ;;
"bash")
    bash
    exit 0
    ;;
*)
    echo "$ERROR: {OPTION} is not support"
    exit 255
    ;;
esac
cp ${ProxyFile} ${ProxyConfig}
${ProxyRestart}
tail -F /var/log/squid/access.log 2>/dev/null
# tail -f /dev/null

exit 0
