@echo off
title Auto Putty Connect - putty.exe should be existed
chcp 65001 & echo.

call:func_CheckOSbits
call:func_execCommand 10
call:func_puttySSH 192.168.0.1 22 root password
:: del %execCommandFile%

echo.&timeout /t 3 > nul
exit


::--------------------------------------------------------------
::-- func_CheckOSbits
::--------------------------------------------------------------
:func_CheckOSbits
set putty=puttyx86.exe

reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set putty=puttyx86.exe || set putty=puttyx64.exe
echo.%putty%

goto:eof

::--------------------------------------------------------------
::-- func_execCommand
::--------------------------------------------------------------
: func_execCommand
set pWaitTime=%1

set execCommandFile="%~dp0\script.txt"
if exist %execCommandFile% (
	del %execCommandFile%
)
echo.execute command file: %execCommandFile%

echo.date>> %execCommandFile%
echo.uname -a>> %execCommandFile%

echo.sleep %pWaitTime%>> %execCommandFile%

goto:eof

::--------------------------------------------------------------
::-- func_puttySSH
::--------------------------------------------------------------
: func_puttySSH
set pIP=%1
set pPort=%2
set pID=%3
set pPW=%4

%putty% -ssh %pIP% -P %pPort% -l %pID% -pw %pPW% -m %execCommandFile% -t

goto:eof
