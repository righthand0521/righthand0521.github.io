:: 刪除文件時出現 MS-DOS 功能無效	https://jingyan.baidu.com/article/454316ab2931c0f7a6c03a60.html
:: 將下面的內容另存為 dosdel.bat, 然後將刪不掉的文件拖動到 dosdel.bat 上面, 就可以刪除了.

@echo Y|cacls %* /t /e /c /g Everyone:f

DEL /F /A /Q \\?\%1

RD /S /Q \\?\%1

exit
