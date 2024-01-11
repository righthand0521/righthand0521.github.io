@echo off
title Clean Recycle
echo.&chcp 65001 > nul

call:func_cleanRecycle C:
call:func_cleanRecycle D:

:: pause
echo.&timeout /t 3 > nul
exit


::--------------------------------------------------------------
::-- func_cleanRecycle
::--------------------------------------------------------------
:func_cleanRecycle
set drive=%1
echo func_cleanRecycle: %drive%\$RECYCLE.BIN
if exist %drive%\$RECYCLE.BIN (
	pushd %drive%\$RECYCLE.BIN
	del /s /q .
	popd
)
echo.&timeout /t 1 > nul
goto:eof
