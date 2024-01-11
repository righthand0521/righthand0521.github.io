@echo off
title Auto FTP
chcp 65001

set "SleepCommand=echo.&timeout /t 1 > nul"

for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%"
set ftpLogFile="%~dp0\%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%.log"

call:func_ftp "192.168.0.1" "root" "password" "tmp" "get download.txt"
call:func_ftp "192.168.0.1" "root" "password" "tmp" "put upload.txt"

%SleepCommand%
exit


::--------------------------------------------------------------
::-- func_ftp
::--------------------------------------------------------------
: func_ftp
set pIP=%~1
set pID=%~2
set pPW=%~3
set pRemotePath=%~4
set pCommand=%~5

set execCommandFile="%~dp0\autoFTP.txt"
if exist %execCommandFile% (
	del %execCommandFile%
)

echo open %pIP%>> %execCommandFile%
echo %pID%>> %execCommandFile%
echo %pPW%>> %execCommandFile%
echo cd %pRemotePath%>> %execCommandFile%
echo bin>> %execCommandFile%
echo hash>> %execCommandFile%
echo %pCommand%>> %execCommandFile%
echo quit>> %execCommandFile%

%SleepCommand%
ftp -s:%execCommandFile% >> %ftpLogFile%

%SleepCommand%
:: del %execCommandFile%

goto:eof
