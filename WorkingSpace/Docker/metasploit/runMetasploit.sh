#!/bin/sh

[ ${#} -lt 1 ] && echo "Options: <Module> <RHOSTS>" && exit 255
Module="${1}"
RHOSTS="${2}"
echo "[${LINENO}]: ${Module}; ${RHOSTS}"

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
