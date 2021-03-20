Registry
===
### [regedit](https://zh.wikipedia.org/wiki/%E6%B3%A8%E5%86%8C%E8%A1%A8)
```
電腦->連線網路磁碟機->資料夾    HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Map Network Drive MRU
```
---
### 檔案總管從「本機」中移除「NameSpace」.reg
```
Windows 10 檔案總管->從「本機」中移除「NameSpace」

HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\MyComputer\NameSpace
HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Explorer\MyComputer\NameSpace

從「本機」中移除「Desktop」      {B4BFCC3A-DB2C-424C-B029-7FE99A87C641}
從「本機」中移除「Downloads」    {374DE290-123F-4565-9164-39C4925E467B}  {088e3905-0323-4b02-9826-5d99428e115f}
從「本機」中移除「文件」         {A8CDFF1C-4878-43be-B5FD-F8091C1C60D0}  {d3162b92-9365-467a-956b-92703aca08af}
從「本機」中移除「音樂」         {1CF1260C-4DD0-4ebb-811F-33C572699FDE}  {3dfdf296-dbec-4fb4-81d1-6a3438bcf4de}
從「本機」中移除「圖片」         {3ADD1653-EB32-4cb0-BBD7-DFA0ABB5ACCA}  {24ad3ad4-a569-4530-98e1-ab02f9417aa8}
從「本機」中移除「影片」         {A0953C92-50DC-43bf-BE83-3742FED03C9C}  {f86fa3ab-70d2-4fc7-9c99-fcbf05467f3a}
從「本機」中移除「3D 物件」      {0DB7E03F-FC29-4DC6-9020-FF41B59E513A}
```
### connectToSambaFromWindows10.reg
```
Windows 10 Connect to Linux Samba

HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\LanmanWorkstation\Parameters\AllowInsecureGuestAuth=dword:00000001
```
---
