@REM Windows 11恢復詳細版的右鍵選單: https://ithelp.ithome.com.tw/articles/10312844

reg add "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f /ve
taskkill /f /im explorer.exe & start explorer.exe

exit