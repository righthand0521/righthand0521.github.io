@echo off
title reboot by shutdown.exe
chcp 65001

set arg1=%1
:: C:\WINDOWS\system32\shutdown.exe -r -f -t %arg1%

timeout /t 3
exit
