@echo off
title Auto Telnet
chcp 65001

call:func_method1 192.168.0.1
:: call:func_method2 192.168.0.1

exit

::--------------------------------------------------------------
::-- func_method1
::--------------------------------------------------------------
: func_method1
set pIP=%1

set execCommandFile="%~dp0\autoTelnet.txt"
start telnet %pIP%
cscript //nologo %execCommandFile%

goto:eof

::--------------------------------------------------------------
::-- func_method2
::--------------------------------------------------------------
: func_method2
set pIP=%1

set execCommandFile="%~dp0\autoTelnet.vbs"
if exist %execCommandFile% (
	del %execCommandFile%
)

echo set sh=WScript.CreateObject("WScript.Shell") > %execCommandFile%

echo WScript.Sleep 1000>> %execCommandFile%
echo sh.SendKeys "root{ENTER}">> %execCommandFile%

echo WScript.Sleep 1000>> %execCommandFile%
echo sh.SendKeys "password{ENTER}">> %execCommandFile%

echo WScript.Sleep 1000>> %execCommandFile%
echo sh.SendKeys "uname -a{ENTER}">> %execCommandFile%

echo WScript.Sleep 1000>> %execCommandFile%
echo sh.SendKeys "sleep 3{ENTER}">> %execCommandFile%

echo WScript.Sleep 1000>> %execCommandFile%
echo sh.SendKeys "exit{ENTER}">> %execCommandFile%

echo WScript.Sleep 1000>> %execCommandFile%
echo sh.SendKeys "{ENTER}">> %execCommandFile%

start telnet %pIP%
cscript //nologo %execCommandFile%

:: del %execCommandFile%

goto:eof
