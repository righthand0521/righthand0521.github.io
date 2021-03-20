Application
===
### Google Chrome
```
# wget -c https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
# dpkg -i google-chrome-stable_current_amd64.deb

# apt remove google-chrome-stable
# apt purge google-chrome-stable
# apt autoremove
# rm -rf ~/.config/google-chrome
```
### [Solving Google Chrome's gpu-process error message in Ubuntu Linux](https://simpleit.rocks/linux/ubuntu/fixing-common-google-chrome-gpu-process-error-message-in-linux/)
```
# vim /usr/bin/google-chrome
exec -a "$0" "$HERE/chrome" "$@" --no-sandbox --disable-gpu --disable-software-rasterizer
```
---
### Google Drive
```
# add-apt-repository ppa:alessandro-strada/ppa
# apt install google-drive-ocamlfuse -y
# mkdir ~/google-drive
# google-drive-ocamlfuse ~/google-drive
```
---
### [minicom(1) - friendly serial communication program](https://linux.die.net/man/1/minicom)
```
# apt install minicom -y
# yum install minicom

# alias minicom='minicom --color=on'
```
```
# dmesg | grep tty
# ls -l /dev/ttyUSB0
# lsusb

# minicom -s
  - 選擇A設定  "Serial port setup"
  - 選擇B設定Serial device為/dev/ttyUSB0
  - 選擇E設定BPS/Par/Bits為11520 8N1
  - 選擇F設定Hardware flow control 為  No
  - 選擇G設定Software flow control 為  No
  - 按一下enter回上一層選單準備儲存設定值。
  - 選擇selected "save setup as dfl"
  - 選擇slected "exit from minicom"
# minicom
# minicom --capturefile=testFile
```
```
# vim script.txt

start:
    expect "boot"
    send ""
    send "ls"
    sleep 1
    goto start

# minicom -S script.txt -C output.txt
```
```
# cat < /dev/ttyUSB0 >| test
```
---
### [Binwalk](https://github.com/ReFirmLabs/binwalk)
```
# apt install binwalk -y
# binwalk -x xz -Mer <firmware file>

sasquatch
```
#### [Binwalk v2.3.1 releases – Firmware Analysis Tool](https://securityonline.info/introduction-to-binwalk-firmware-analysis-tool)
---
### FileZilla
```
"C:\Program Files\FileZilla FTP Client\filezilla.exe"
"C:\Program Files\FileZilla FTP Client\filezilla.exe" --close
"C:\Program Files\FileZilla FTP Client\filezilla.exe" --site="<Bookmarks>"
"C:\Program Files\FileZilla FTP Client\filezilla.exe" ftp://<user>:<passwod>@<ftp server ip>
"C:\Program Files\FileZilla FTP Client\filezilla.exe" ftp://<user>:<passwod>@<ftp server ip>/<ftp remote path> --local="<local path>"
```
---
### [Xming](https://zh.wikipedia.org/wiki/Xming)
---
### [OpenACS](https://openacs.org/)
```
Configuration Scripts

// This will output supported methods to server console
var methods = cpe.GetRPCMethods();
for (i=0; i<methods.length; i++)
{
    logger('Method:'+methods[i]);
}

// Get parameters.
var parameters = new Array();
parameters[0] = 'Device.';
var response = cpe.GetParameterValues(parameters);
logger('\nGetParam:'+response[0].name+'='+response[0].value);

// Set parameters.
var setParameters = new Array ();
setParameters[0] = {name: 'Device.Routing.Router.301.Enable', value: '1'};
cpe.SetParameterValues (setParameters, "commandKey");
```
#### [OpenACS configuration and scripting](https://blog.pierky.com/tag/openacs/)
---
