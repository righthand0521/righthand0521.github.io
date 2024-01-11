@echo off
title File List
chcp 65001

SETLOCAL

echo Select Display Format: name/path
set /p format=
IF /i "%format%"=="name" goto displayFileName
IF /i "%format%"=="path" goto displayFilePath
echo Not found.
goto end
exit


::--------------------------------------------------------------
:displayFileName
for /r %%i in (*) do (
	echo %%~nxi
)
goto end

::--------------------------------------------------------------
:displayFilePath
for /r %%i in (*) do (
	echo %%i
)
goto end

::--------------------------------------------------------------
:end
pause
