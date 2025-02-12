#!/bin/sh

case "${#}" in
"1")
    if [ "${1}" == "bash" ]; then
        bash
        exit 0
    fi
    echo "Options: <Module> <RHOSTS>"
    exit 255
    ;;
"2")
    Module="${1}"
    RHOSTS="${2}"
    echo "[${LINENO}]: ${Module}; ${RHOSTS}"
    ;;
*)
    echo "Options: <Module> <RHOSTS>"
    exit 255
    ;;
esac

meterpreter="/tmp/meterpreter.rc"
[ -e "${meterpreter}" ] && rm "${meterpreter}"
{
    echo "use ${Module}"
    echo "set RHOSTS ${RHOSTS}"
    echo "run"
    echo
    echo "exit"
} >>${meterpreter}
[ -e "${meterpreter}" ] && cat ${meterpreter}
echo
sleep 1
msfconsole -r ${meterpreter}
echo
sleep 1
[ -e "${meterpreter}" ] && rm "${meterpreter}"

exit 0
