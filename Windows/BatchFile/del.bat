@echo off
title Delete Thumbs.db, sync.ffs_db and sync.ffs_lock
chcp 65001

del /s /ah Thumbs.db
:: call:func_delete Thumbs.db
del /s /ah sync.ffs_db
:: call:func_delete sync.ffs_db
del /s /ah sync.ffs_lock
:: call:func_delete sync.ffs_lock

timeout /t 3
:: pause
exit


::--------------------------------------------------------------
::-- func_delete
::--------------------------------------------------------------
:func_delete
set delArg=%1
echo func_delete: %delArg%

del /s /ah %delArg%

echo.&timeout /t 1 > nul
goto:eof
