# Windows

## [Microsoft Developer](https://developer.microsoft.com/en-us)

- [Develop extensions for Microsoft Edge](https://developer.microsoft.com/en-us/microsoft-edge/)

## [Windows 工具/系統管理工具](https://learn.microsoft.com/zh-tw/windows/client-management/administrative-tools-in-windows-10)

### [Service Control Manager](https://en.wikipedia.org/wiki/Service_Control_Manager)

- services.msc

### [Windows Task Scheduler](https://en.wikipedia.org/wiki/Windows_Task_Scheduler)

- [[D3] : Automatically schedule task on Windows](https://ithelp.ithome.com.tw/articles/10238969)

```powershell
param (
    [string]$TaskName = "MyDailyTask.ps1"
    [datetime]$ExcutionTime = "11:00am",
    [string]$TaskPath = "YourTaskNamePath.ps1"
 )

$Action = New-ScheduledTaskAction -Execute 'powershell.exe' -Argument $TaskPath
$Trigger = New-ScheduledTaskTrigger -Daily -At $ExcutionTime
$Settings = New-ScheduledTaskSettingsSet
$Task = New-ScheduledTask -Action $Action -Trigger $Trigger -Settings $Settings
Register-ScheduledTask -TaskName $TaskName -InputObject $Task
```

### [Windows Registry](https://en.wikipedia.org/wiki/Windows_Registry)

```text
regedit.exe
regedit.exe /s ".reg path"

Win+R -> regedit
```

- 電腦->連線網路磁碟機->資料夾

```text
HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Map Network Drive MRU
```

- Windows 10 檔案總管->從「本機」中移除「NameSpace」

```text
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

- Windows 10 Connect to Linux Samba

```text
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\LanmanWorkstation\Parameters\AllowInsecureGuestAuth=dword:00000001
```

- Interface List

```text
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\NetworkList\Profiles\
```

## [Windows Subsystem for Linux](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux)

- [WSL2-Linux-Kernel](https://github.com/microsoft/WSL2-Linux-Kernel)

```text
C:\Windows\System32\wsl.exe
C:\Windows\System32\wsl.exe sudo /usr/sbin/service cron start
C:\Windows\System32\wsl.exe sudo /usr/sbin/service ssh start
C:\Windows\System32\wsl.exe sudo /usr/sbin/service jenkins start
C:\Windows\System32\wsl.exe sudo /usr/sbin/service apache2 start
```

## [Windows 命令](https://docs.microsoft.com/zh-tw/windows-server/administration/windows-commands/windows-commands)

<details><summary>cmd.exe</summary>

```text
rem /?  在批次檔或 CONFIG.SYS 裡加上備註或說明。
```

```text
chcp /?  顯示或設定使用中的字碼頁編號。

chcp 65001
```

```text
systeminfo /?  此工具可顯示本機或遠端機器的作業系統設定資訊，包括 Service Pack 等級。
```

```text
ipconfig /?

ipconfig /all
ipconfig /displaydns
ipconfig /flushdns
```

```text
ping /?

ping <IP> -f -l <MTU Size>
```

```text
net /?

net use
net use <磁碟機代號>: \\<IP or HostName>\<資料夾名稱> /user:<Domain>\<Account> <Password>
net use z: \\192.168.1.xxx\myFiles /user:Domain\Administrator 123
net use z: \\192.168.1.xxx\myFiles /user:Domain\Administrator ""
net use z: /delete
```

```text
xcopy /?

xcopy C:\xxx F:\xxx /s
C:\xxx 為複製檔案來源位置: 例如要複製整個C槽就輸入C:\
F:\xxx 為複製目的位置: 例如要放到F槽的備份資料夾就輸入F:\備份
/s     為複製類型參數: 複製每個目錄及其包含的子目錄但不複製空目錄
```

[netsh](https://learn.microsoft.com/zh-tw/windows-server/networking/technologies/netsh/netsh)

```text
netsh /?

netsh interface show interface
netsh winsock reset

netsh interface ipv4 set address "Ethernet 2" source=dhcp
netsh interface ipv4 set dnsservers name="Ethernet 2" source=dhcp
netsh interface ipv4 set winsservers name="Ethernet 2" source=dhcp

netsh interface portproxy show all
netsh interface portproxy reset
netsh interface portproxy add v4tov4 listenport=3000 listenaddress=0.0.0.0 connectport=3000 connectaddress=192.168.0.1
netsh interface portproxy add v4tov4 listenport= listenaddress=0.0.0.0 connectport= connectaddress=192.168.0.1
```

```text
netstat /?  顯示通訊協定統計資料和目前的 TCP/IP 網路連線。
```

```text
route/?  操控網路路由表

route -p add 10.0.0.0 mask 255.0.0.0 192.168.0.1 metric 30 if 2
```

```text
tasklist /?  此工具會顯示本機或遠端電腦上，目前正在執行中的處理程序清單。
```

```text
taskkill /?  此工具可用於依據處理程序識別碼 (PID) 或影像名稱來終止工作。
```

```text
schtasks/?  讓系統管理員能夠在建立、刪除、查詢、變更，和執行，結束排程工作。

schtasks /create /f /tn "TaskName" /tr "dir" /sc onstart
schtasks /run /tn "TaskName"
schtasks /end /tn "TaskName"
schtasks /delete /tn "TaskName" /f
```

```text
dir /?  顯示檔案清單以列出目錄中的檔案及子目錄。

dir /b /ad-h /t:c /od
```

```text
type /?  顯示文字檔案的內容。
```

```text
del /?  刪除一個或多個檔案。

del /s /ah Thumbs.db
```

```text
rmdir /?  移除 (刪除) 一個目錄。

清理資源回收筒指令
rmdir /s /q %systemdrive%\$Recycle.bin
```

```text
rename /?  更改檔案名稱。
```

```text
date /?  顯示或設定日期。

date /t
```

```text
time /?  顯示或設定系統時間。

time /t
```

</details>

## Question

### Enable Telnet Server

```text
net localgroup TelnetClients /add
net localgroup TelnetClients <user> /add
net localgroup TelnetClients

# Change Telnet Server Auth
tlntadmn config sec -ntlm passwd
tlntadmn
```

### Windows 7 Default Dir Path is "MY Computer"

```text
%WINDIR%\explorer.exe ::{20D04FE0-3AEA-1069-A2D8-08002B30309D} ， ::{20D04FE0-3AEA-1069-A2D8-08002B30309D}
```

### Check Windows Bit

```text
reg Query "HKLM\Hardware\Description\System\CentralProcessor\0"
reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86"
```

### 新增的應用程式以在 Windows 10 啟動時自動執行

```text
選取 [開始] 按鈕, 並捲動以尋找您要在開機時執行的應用程式.
在應用程式上按右鍵, 選取 [更多], 然後選取 [開啟檔案位置].
這樣會開啟儲存應用程式捷徑的位置.
如果沒有 [開啟檔案位置] 的選項, 即表示該應用程式不會在開機時執行.

檔案位置開啟後, 按 Windows 鍵 + R, 輸入 shell:startup, 然後選取 [確定].
這會開啟 [啟動] 資料夾.
將檔案位置中的應用程式捷徑複製並貼到 [啟動] 資料夾.
```

- [如何讓 VMware Workstation 開機自動啟動虛擬機](https://superuser.com/questions/1420091/how-to-create-a-shortcut-to-a-vmware-workstation-player-15-vm)

```text
進入VMware Workstation的安裝目錄: C:\Program Files (x86)\VMware\VMware Workstation
在vmware.exe程序上點右鍵, 發送快捷方式到桌面.
在桌面快捷方式上點右鍵, 選屬性, 在"目標位置"加入 -x "<.vmx Path>", vmx替換成你的虛擬機絕對路徑, -x代表開啟虛擬機。
加入後如下： "C:\Program Files (x86)\VMware\VMware Workstation\vmware.exe" -x "<.vmx Path>"
最後剪切移動快捷方式到windows開機啟動路徑：
```

### macshift.exe: Macshift v2.0, MAC Changing Utility

```text
macshift.exe -i NIC1 000c29fff701
```
