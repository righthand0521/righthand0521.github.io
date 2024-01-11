# [Batch File](https://zh.wikipedia.org/wiki/%E6%89%B9%E6%AC%A1%E6%AA%94)

```bat
@echo off
title Hello Batch File

chcp 65001
:: echo.&chcp 65001 > nul

pause
exit
```

```bat
set "SleepCommand=echo.&timeout /t 3 > nul"
%SleepCommand%
```

```bat
:: comment
rem comment
echo.   & :: comment
echo.   & rem comment
```

```bat
:: current path
echo.%~dp0

echo %HOMEDRIVE%%HOMEPATH%

echo.%date:~0,10% %time:~0,11%
```

```bat
set hour=%time:~0,2%
set dtStamp12=%date:~0,4%%date:~5,2%%date:~8,2%0%time:~1,1%%time:~3,2%%time:~6,2%
set dtStamp24=%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%%time:~6,2%

if "%hour:~0,1%" == " " (set dtStamp=%dtStamp12%) else (set dtStamp=%dtStamp24%)
echo %dtStamp%
```

```bat
start chrome
```

```bat
echo Enter some content:
set /p input=
echo Input: %input%
```

```bat
echo.Enter a option as the following:
echo. 1
echo. 2
echo. 3
set /p option= > nul
echo.
if %option%==1 (
    set output=1a
) else if %option%==2 (
    set output=2b
) else if %option%==3 (
    set output=3c
) else (
    echo.option %option% does not exist
    echo.&timeout /t 3 > nul
    exit
)
echo.%output%
```

```bat
set Arr[0]=cls
set Arr[1]=ipconfig
set Arr[2]=dir
set "x=0"

:SymLoop
if defined Arr[%x%] (
    call echo %%Arr[%x%]%%
    call %%Arr[%x%]%%
    set /a "x+=1"
    GOTO :SymLoop
)
```

```bat
call:func_1 argu1 argu2
call:func_2

pause
exit


::--------------------------------------------------------------
::-- func_1
::--------------------------------------------------------------
:func_1
set pArgu1=%~1
set pArgu2=%~2

echo.%pArgu1%
echo.%pArgu2%

echo.&timeout /t 1 > nul
goto:eof

::--------------------------------------------------------------
::-- func_2
::--------------------------------------------------------------
:func_2
echo.%~dp0

echo.&timeout /t 1 > nul
goto:eof
```

```bat
for /f "delims=" %%i IN ('dir /b /ad-h /t:c /od') do set pRecentFolder=%%i
echo.Most Recent Folder: %pRecentFolder%

for /r %pRecentFolder% %%f in (*) do echo %%f
```

---
