# [Server Message Block](https://en.wikipedia.org/wiki/Server_Message_Block)

## [Samba](https://en.wikipedia.org/wiki/Samba_(software))

### Install

```bash
apt install samba samba-common -y
apt install smbclient -y

service --status-all
update-rc.d smbd enable
service smbd start

mkdir WorkingSpace
smbpasswd -a root
```

### vim /etc/samba/smb.conf

- [samba 配置文件详解](https://www.cnblogs.com/JohnRain/p/10898755.html)
- [smb.conf](https://github.com/samba-team/samba/blob/master/examples/smb.conf.default)

```bash
[global]

# make samba follow symlink outside the shared path
follow symlinks = yes
wide links = yes
unix extensions = no

# Support Windows XP SMBv1 Version
min protocol = NT1
lanman auth = yes
ntlm auth = yes

# SMB Support Version
# min protocol=NT1
# min protocol=SMB2
# min protocol=SMB3
# max protocol=NT1
# max protocol=SMB2
# max protocol=SMB3

[root]
   path = /root/WorkingSpace
   browseable = no
   writable = yes
   guest ok = no
   force user = root
[homes]
   path = /home/%S/WorkingSpace
   browseable = no
   writable = yes
   valid users = %S
```

#### This one is useful for people to share files

```bash
[share]
   path = /home/public/share
   public = yes
   read only = no
```

```bash
smbclient //192.168.0.1/share -c "prompt off; get test; exit" -U % -m smb3
smbclient //192.168.0.1/share -c "prompt off; put test; exit" -U % -m smb3
smbclient //192.168.0.1/share -c "prompt off; get test; exit" -U % -m smb2
smbclient //192.168.0.1/share -c "prompt off; put test; exit" -U % -m smb2
curl -u : smb://192.168.0.1/share/test --output test
curl -u : smb://192.168.0.1/share/test --upload-file test
```

#### A publicly accessible directory, but read only, except for people in the "admin" group

```bash
[adminShare]
   path = /home/public/admin
   public = yes
   writable = no
   write list = @admin
```

```bash
smbclient //192.168.0.1/adminShare -c "prompt off; get test; exit" -U % -m smb3
smbclient //192.168.0.1/adminShare -c "prompt off; put test; exit" -U % -m smb3
smbclient //192.168.0.1/adminShare -c "prompt off; get test; exit" -U % -m smb2
smbclient //192.168.0.1/adminShare -c "prompt off; put test; exit" -U % -m smb2
curl -u : smb://192.168.0.1/adminShare/test --output test
curl -u : smb://192.168.0.1/adminShare/test --upload-file test

smbclient //192.168.0.1/adminShare -c "prompt off; get test; exit" -U admin%password -m smb3
smbclient //192.168.0.1/adminShare -c "prompt off; put test; exit" -U admin%password -m smb3
smbclient //192.168.0.1/adminShare -c "prompt off; get test; exit" -U admin%password -m smb2
smbclient //192.168.0.1/adminShare -c "prompt off; put test; exit" -U admin%password -m smb2
curl -u admin:password smb://192.168.0.1/adminShare/test --output test
curl -u admin:password smb://192.168.0.1/adminShare/test --upload-file test
```

#### [smb.conf — The configuration file for the Samba suite](https://www.samba.org/samba/docs/current/man-html/smb.conf.5.html)

- server multi channel support (G)

```text
This boolean parameter controls whether smbd(8) will support SMB3 multi-channel.

This parameter was added with version 4.4.

Note that this feature was still considered experimental up to 4.14.

Due to dependencies to kernel APIs of Linux or FreeBSD, it's only possible to use this feature on Linux and FreeBSD for now.
For testing this restriction can be overwritten by specifying force:server multi channel support=yes in addition.

This option is enabled by default starting with to 4.15 (on Linux and FreeBSD).

Default: server multi channel support = yes
```

```bash
server multi channel support = yes
aio read size = 1
aio write size = 1
```

#### map to guest (G)

```text
This parameter can take four different values,
which tell smbd(8) what to do with user login requests that don't match a valid UNIX user in some way.

The four settings are :
- Never
  Means user login requests with an invalid password are rejected. This is the default.
- Bad User
  Means user logins with an invalid password are rejected, unless the username does not exist,
  in which case it is treated as a guest login and mapped into the guest account.
- Bad Password
  Means user logins with an invalid password are treated as a guest login and mapped into the guest account.
  Note that this can cause problems as
  it means that any user incorrectly typing their password will be silently logged on as "guest" -
  and will not know the reason they cannot access files they think they should -
  there will have been no message given to them that they got their password wrong.
  Helpdesk services will hate you if you set the map to guest parameter this way :-).
- Bad Uid
  Is only applicable when Samba is configured in some type of domain mode security (security = {domain|ads})
  and means that user logins which are successfully authenticated but which have no valid Unix user account
  (and smbd is unable to create one) should be mapped to the defined guest account.
  This was the default behavior of Samba 2.x releases.
  Note that if a member server is running winbindd,
  this option should never be required because the nss_winbind library will export
  the Windows domain users and groups to the underlying OS via the Name Service Switch interface.

Note that this parameter is needed to set up "Guest" share services.
This is because in these modes the name of the resource being requested is not sent to the server
until after the server has successfully authenticated the client
so the server cannot make authentication decisions at the correct time (connection to the share) for "Guest" shares.

Default: map to guest = Never
Example: map to guest = Bad User
```

### Remote mount SMB

```bash
apt install cifs-utils -y

mount -t cifs -o user=<id>,pass=<pw> //<Remote IP>/<Remote Path> <Local Path>
mount -t cifs -o rw,user=<id>,pass=<pw>,vers=1.0 //<Remote IP>/<Remote Path> <Local Path> -v
```

#### Change Port

- vim /etc/samba/smb.conf

```bash
# smb ports = 445 139
smb ports = 33445 33139
```

### dockerhub

- [elswork/samba](https://hub.docker.com/r/elswork/samba)
- [dperson/samba](https://hub.docker.com/r/dperson/samba/)

### Tools

#### smbmap(1) - SMB enumeration tool

```bash
apt install smbmap -y

smbmap -H 0.0.0.0
```

## Windows

### [How to detect, enable and disable SMBv1, SMBv2, and SMBv3 in Windows](https://learn.microsoft.com/en-us/windows-server/storage/file-server/troubleshoot/detect-enable-and-disable-smbv1-v2-v3?tabs=server)

- [How to Check, Enable or Disable SMB Protocol Versions on Windows?](https://woshub.com/smb-1-0-support-in-windows-server-2012-r2/)
- [How to Manage Windows File Shares Using PowerShell](https://woshub.com/manage-windows-file-shares-with-powershell/)
- [Allow Anonymous Access to Shared Folder or Printer on Windows](https://woshub.com/anonymous-access-shared-folders-printers-windows/)

```bash
smbclient //192.168.0.1/Downloads -c "prompt off; get test; exit" -U admin%password -m smb3
smbclient //192.168.0.1/Downloads -c "prompt off; put test; exit" -U admin%password -m smb3

smbclient //192.168.0.1/Downloads -c "prompt off; get test; exit" -U admin%password -m smb2
smbclient //192.168.0.1/Downloads -c "prompt off; put test; exit" -U admin%password -m smb2

curl smb://admin:password@192.168.0.1/Downloads/puttyx64.exe --output test
curl smb://admin:password@192.168.0.1/Downloads/pcap.tgz --upload-file test
```

- regedit.exe /S SMBv1Disable.reg

```bat
Windows Registry Editor Version 5.00

; https://learn.microsoft.com/en-us/windows-server/storage/file-server/troubleshoot/detect-enable-and-disable-smbv1-v2-v3?tabs=server#tabpanel_1_server
;
; SMBv1 on SMB Server
;
; Registry entry: SMB1
; REG_DWORD: 0 = Disabled
; REG_DWORD: 1 = Enabled
; Default: 1 = Enabled (No registry key is created)
;
; regedit.exe /S SMBv1Disable.reg

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\LanmanServer\Parameters]
"SMB1"=dword:00000000
```

- regedit.exe /S SMBv1Enable.reg

```bast
Windows Registry Editor Version 5.00

; https://learn.microsoft.com/en-us/windows-server/storage/file-server/troubleshoot/detect-enable-and-disable-smbv1-v2-v3?tabs=server#tabpanel_1_server
;
; SMBv1 on SMB Server
;
; Registry entry: SMB1
; REG_DWORD: 0 = Disabled
; REG_DWORD: 1 = Enabled
; Default: 1 = Enabled (No registry key is created)
;
; regedit.exe /S SMBv1Enable.reg

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\LanmanServer\Parameters]
"SMB1"=dword:00000001
```

- regedit.exe /S SMBv2Disable.reg

```bat
Windows Registry Editor Version 5.00

; https://learn.microsoft.com/en-us/windows-server/storage/file-server/troubleshoot/detect-enable-and-disable-smbv1-v2-v3?tabs=server#tabpanel_1_server
;
; SMBv2/v3 on SMB Server
;
; Registry entry: SMB2
; REG_DWORD: 0 = Disabled
; REG_DWORD: 1 = Enabled
; Default: 1 = Enabled (No registry key is created)
;
; regedit.exe /S SMBv2Disable.reg

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\LanmanServer\Parameters]
"SMB2"=dword:00000000
```

- regedit.exe /S SMBv2Enable.reg

```bat
Windows Registry Editor Version 5.00

; https://learn.microsoft.com/en-us/windows-server/storage/file-server/troubleshoot/detect-enable-and-disable-smbv1-v2-v3?tabs=server#tabpanel_1_server
;
; SMBv2/v3 on SMB Server
;
; Registry entry: SMB2
; REG_DWORD: 0 = Disabled
; REG_DWORD: 1 = Enabled
; Default: 1 = Enabled (No registry key is created)
;
; regedit.exe /S SMBv2Enable.reg

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\LanmanServer\Parameters]
"SMB2"=dword:00000001
```

### Reference

- [Intellectual Property Rights Notice for Open Specifications Documentation](https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-nlmp/b38c36ed-2804-4868-a9ff-8dd3182128e4)
- [SMB compression](https://learn.microsoft.com/en-us/windows-server/storage/file-server/smb-compression?tabs=powershell%2Crobocopy%2Cgroup-policy)
- [How to enable SMB encryption on Windows Server](https://www.jorgebernhardt.com/how-to-enable-smb-encryption-on-windows-server/)
