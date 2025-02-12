# [Linux](https://www.kernel.org/)

- [The Linux Kernel documentation](https://www.kernel.org/doc/html/latest/index.html)
- [Vim Cheat Sheet](https://vim.rtorr.com/)

## Settings

### root login

```bash
sudo -i passwd root
sudo systemctl get-default
sudo systemctl set-default multi-user.target
sudo systemctl isolate multi-user.target
sudo systemctl get-default
```

```bash
sudo vim /lib/systemd/system/getty@.service

ExecStart=-/sbin/agetty --autologin root --noclear %I $TERM
```

### Boot to Command Line

```bash
systemctl get-default
systemctl set-default multi-user.target
systemctl set-default graphical.target
```

### Change /bin/sh -> /bin/dash to /bin/sh -> /bin/bash

```bash
dpkg-reconfigure dash

no
```

### Upgrade Ubuntu Operating System to Latest Release

```bash
cat /etc/os-release
do-release-upgrade -d
```

### Set Static IP Address

#### Ubuntu 18.04 LTS

- vim /etc/network/interfaces

```bash
# The loopback network interface
auto lo
iface lo inet loopback

auto eth0
# iface eth0 inet dhcp
iface eth0 inet static
address 192.168.0.1
netmask 255.255.255.0
gateway 192.168.0.254
dns-nameservers 8.8.8.8 168.95.1.1
up ip addr add 192.168.0.1/24
up ip route add 192.168.0.0/24 via 192.168.0.254
up route add -net 192.168.0.0 netmask 255.255.255.0 gw 192.168.0.254
```

#### Ubuntu 20.04.1 LTS

- cat /etc/cloud/cloud.cfg.d/subiquity-disable-cloudinit-networking.cfg

```bash
network: {config: disabled}
```

- vim /etc/netplan/00-installer-config.yaml

```bash
network:
  ethernets:
    ens160:
      # dhcp4: true
      addresses: [192.168.0.1/24]
      gateway4: 192.168.0.254
      nameservers:
        addresses: [8.8.8.8, 168.95.1.1]
  version: 2
```

- netplan apply

#### Ubuntu 22.04 LTS

> netplan generate: `gateway4` has been deprecated, use default routes instead

- vim /etc/netplan/00-installer-config.yaml

```bash
# This is the network config written by 'subiquity'
network:
  ethernets:
    ens32:
      addresses:
      - 192.168.0.1/24
      nameservers:
        addresses:
        - 8.8.8.8
      routes:
          - to: default
            via: 192.168.0.254
  version: 2
```

##### Multiple Interface

```bash
# This is the network config written by 'subiquity'
# Multiple Interface
network:
  version: 2
  ethernets:
    eth0:
      dhcp4: false
      addresses: [192.168.1.10/24]
      gateway4: 192.168.1.254
      nameservers:
        addresses:
        - 8.8.8.8
    eth1:
      dhcp4: false
      addresses: [192.168.2.10/24]
      # gateway4: 192.168.2.254
    eth2:
      dhcp4: false
      addresses: [192.168.3.10/24]
      # gateway4: 192.168.3.254
```

##### VLAN

```bash
# This is the network config written by 'subiquity'
# VLAN
network:
  version: 2
  ethernets:
    eth0:
      dhcp4: false
      # addresses: [192.168.56.10/24]
      # gateway4: 192.168.56.1
      # nameservers:
        # addresses:
        # - 8.8.8.8
  vlans:
    eth0.56:
      id: 56
      link: eth0
      addresses: [192.168.56.10/24]
      gateway4: 192.168.56.1
      nameservers:
        addresses:
        - 8.8.8.8
```

- netplan apply

#### CentOS, Fedora

- vim /etc/sysconfig/network-scripts/ifcfg-ens192

```bash
TYPE=Ethernet
NM_CONTROLLED="yes"
HWADDR="00:11:22:33:44:55"
BOOTPROTO="static"
NAME="ens192"
ONBOOT="yes"
IPADDR="192.168.0.1"
NETMASK="255.255.255.0"
GATEWAY="192.168.0.254"
DNS1="8.8.8.8"
DNS2="8.8.4.4"
NETWORKING_IPV6=no
IPV6INIT=no
```

### Disable IPv6 in Ubuntu

- vim /etc/sysctl.conf

```bash
# Disable IPv6
net.ipv6.conf.all.disable_ipv6 = 1
net.ipv6.conf.default.disable_ipv6 = 1
net.ipv6.conf.lo.disable_ipv6 = 1
net.ipv6.conf.eth0.disable_ipv6 = 1
```

```bash
sysctl -p
ip a | grep inet6
```

```bash
sysctl -w net.ipv6.conf.all.disable_ipv6=1
sysctl -w net.ipv6.conf.default.disable_ipv6=1
sysctl -w net.ipv6.conf.eth0.disable_ipv6=1
sysctl -w net.ipv6.conf.all.disable_ipv6=0
sysctl -w net.ipv6.conf.default.disable_ipv6=0
sysctl -w net.ipv6.conf.eth0.disable_ipv6=0
```

### DNS Setting

```bash
rm /var/lib/ubuntu-release-upgrader/release-upgrade-available
vim /etc/systemd/resolved.conf
systemctl restart systemd-resolved
```

### Set Host Name

```bash
hostnamectl set-hostname U20x64
```

### Adjust Date Time

```bash
timedatectl set-timezone 'Asia/Taipei'
timedatectl set-timezone UTC
localectl set-locale LC_TIME=en_GB.UTF-8
```

```bash
# cat /etc/timezone
Asia/Taipei

#  ls -l /etc/localtime
lrwxrwxrwx 1 root root 31 Dec  2 15:13 /etc/localtime -> /usr/share/zoneinfo/Asia/Taipei
```

#### CentOS, Fedora

```bash
rm -f /etc/localtime; ln -s /usr/share/zoneinfo/Asia/Taipei /etc/localtime
rm -f /etc/localtime; ln -s /usr/share/zoneinfo/GMT /etc/localtime
```

### crontab -l

- [Crontab Generator](https://crontab-generator.org/)
- [crontab guru](https://crontab.guru/)

```bash
cat /var/spool/cron/crontabs/root
```

```bash
# For more information see the manual pages of crontab(5) and cron(8)
# @reboot   Run once at startup
# @yearly   Run once a year     0 0 1 1 * command
# @monthly  Run once a month    0 0 1 * * command
# @weekly   Run once a week     0 0 * * 0 command
# @daily    Run once a day      0 0 * * * command
# @hourly   Run once an hour    0 * * * * command
#
# m h  dom mon dow   command
# @yearly   dd if=/dev/zero of=zero.dat; rm -f zero.dat
# @yearly   apt --installed list
# @yearly   service --status-all
#
@reboot     ntpdate 211.22.103.157
@monthly    apt update; apt upgrade -y; apt dist-upgrade -y; apt autoclean; apt autoremove -y; apt update; reboot
```

#### Set MAILTO variable to stop cron daemon from sending email

```bash
# Output of the crontab jobs (including errors) is sent through
# email to the user the crontab file belongs to (unless redirected).
MAILTO=""
```

### source /etc/bash.bashrc

```bash
# @reboot
tabs 4
ulimit -c unlimited

# export
export LESS_TERMCAP_mb=$'\e[1;32m'
export LESS_TERMCAP_md=$'\e[1;32m'
export LESS_TERMCAP_me=$'\e[0m'
export LESS_TERMCAP_se=$'\e[0m'
export LESS_TERMCAP_so=$'\e[01;33m'
export LESS_TERMCAP_ue=$'\e[0m'
export LESS_TERMCAP_us=$'\e[1;4;31m'

# alias
alias tree='tree -C --charset ASCII'
alias treel='tree -C --charset ASCII -pugsD'
alias targzc='tar -zcvf'
alias targzd='tar -zxvf'
alias tarbz2c='tar jcvf'
alias tarbz2d='tar jxvf'
alias ip='ip -c'
alias grepin='grep --color=auto -irnw --include=*.{c,cpp,h}'
alias pylint='pylint --disable=missing-docstring'
alias google-chrome='google-chrome -no-sandbox'
```

### source ~/.bashrc

```bash
sed -i -e 's|#force_color_prompt=yes|force_color_prompt=yes|' .bashrc
```

```bash
force_color_prompt=yes
```

### vim /etc/sudoers

```bash
# Allow members of group sudo to execute any command
%sudo   ALL=(ALL:ALL) ALL
right   ALL=(ALL:ALL) NOPASSWD:ALL
jenkins ALL=(ALL:ALL) NOPASSWD:ALL
```

### vim /etc/sysctl.conf

```bash
kernel.core_pattern = core.%e.%p.%t
```

## Service

### vim

```bash
apt install vim -y
apt install vim-gtk -y
vim --version | head -n2
```

```text
:%! xxd     // Vim 16 進位編輯器
:%! xxd -r  // Vim 使用 xxd -r 轉換為二進位資料
```

### Auto-Start <Service> on Boot

```bash
service --status-all

update-rc.d <Service> enable
update-rc.d <Service> disable

systemctl enable <Service>
systemctl disable <Service>
```

### Apache

```bash
apt install apache2 -y

service --status-all
update-rc.d apache2 enable

/etc/init.d/apache2 start
/etc/init.d/apache2 stop
service apache2 restart
systemctl restart apache2
```

- vim /etc/apache2/apache2.conf

```bash
# allow html with <?php ?>
AddType application/x-httpd-php .php .htm .html
```

#### [htpasswd-generator](http://www.htaccesstools.com/htpasswd-generator/)

- vim /etc/apache2/.htpasswd

```bash
# admin / password
admin:$apr1$4u2HLeXv$ovmebujuSOgLg9VibH4531
```

- mkdir /var/www/html/auth
- vim /etc/apache2/sites-enabled/000-default.conf

```bash
<VirtualHost *:80>
    <Directory "/var/www/html/auth">
        AuthType Basic
        AuthName "Restricted Content"
        AuthUserFile /etc/apache2/.htpasswd
        Require valid-user
    </Directory>
</VirtualHost>
```

#### Change Port

- vim /etc/apache2/ports.conf

```bash
# Listen 80
Listen 8080
```

- vim /etc/apache2/sites-enabled/000-default.conf

```bash
<VirtualHost *:8080>
```

#### [Apache2 : Configure SSL/TLS](https://www.server-world.info/en/note?os=Ubuntu_24.04&p=httpd&f=3)

```bash
a2ensite default-ssl
a2enmod ssl
systemctl restart apache2
```

#### [Ubuntu18.04 Apache2 配置 python3 CGI](https://pmvt.cn/develop/python3-apache2-cgi.html)

```bash
a2enmod cgid
systemctl restart apache2
chmod 705 /usr/lib/cgi-bin/test.cgi
```

#### Installing Apache on Windows Subsystem for Linux

[APR_TCP_DEFER_ACCEPT error when starting Apache2 #1953](https://github.com/microsoft/WSL/issues/1953)

- vim /etc/apache2/apache2.conf

```bash
# (92)Protocol not available: AH00076: Failed to enable APR_TCP_DEFER_ACCEPT
AcceptFilter http none
AcceptFilter https none
```

#### Apache2 Miss PHP Modules when Ubuntu Upgrade

```bash
# service apache2 status

× apache2.service - The Apache HTTP Server
     Loaded: loaded (/lib/systemd/system/apache2.service; enabled; vendor preset: enabled)
     Active: failed (Result: exit-code) since Wed 2022-06-08 10:18:02 CST; 12s ago
       Docs: <https://httpd.apache.org/docs/2.4/>
    Process: 16544 ExecStart=/usr/sbin/apachectl start (code=exited, status=1/FAILURE)
        CPU: 12ms

systemd[1]: Starting The Apache HTTP Server...
apachectl[16547]: apache2: Syntax error on line 140 of /etc/apache2/apache2.conf: Syntax error on line 3 of /etc/apache2/mods-enabled/php7.4.load: Cannot load /usr/lib/apache2/modules/libphp7.4.so into server: /usr/lib/apache2/modules/lib>
apachectl[16544]: Action 'start' failed.
apachectl[16544]: The Apache error log may have more information.
systemd[1]: apache2.service: Control process exited, code=exited, status=1/FAILURE
systemd[1]: apache2.service: Failed with result 'exit-code'.
systemd[1]: Failed to start The Apache HTTP Server.
```

```bash
netstat -antpu | grep apache2

apt install libapache2-mod-php7.4 -y
apt upgrade apache2 -y
apt upgrade php -y

ls -l /etc/apache2/mods-enabled/php*
ls -l /etc/apache2/mods-available/php*

ln -s /etc/apache2/mods-available/php8.1.conf /etc/apache2/mods-enabled
ln -s /etc/apache2/mods-available/php8.1.load /etc/apache2/mods-enabled

rm /etc/apache2/mods-enabled/php7.4.conf
rm /etc/apache2/mods-enabled/php7.4.load
```

### SSH

```bash
apt install openssh-server -y

service ssh restart
service --status-all
update-rc.d ssh enable
```

- vim /etc/ssh/sshd_config

```bash
PermitRootLogin yes
```

#### ssh/scp without password

```bash
ssh-keygen -t rsa -b 2048
ssh-copy-id <User Name>@<IP Address>
```

#### Remove existed host

```bash
ssh-keygen -f "/root/.ssh/known_hosts" -R "<IP Address>"
```

#### SSH Login Windows 10 Ubuntu bash

- vim /etc/ssh/sshd_config

```bash
PasswordAuthentication yes
```

```bash
ssh-keygen -A
service ssh --full-restart
```

#### Log SSH Client History

- vim /etc/bash.bashrc

```bash
export PROMPT_COMMAND='RETRN_VAL=$?;logger -p local6.debug "$(whoami) [$$]: $(echo $SSH_CLIENT): $(history 1 | sed "s/^[ ]*[0-9]\+[ ]*//" ) [$RETRN_VAL]"'
```

- vim /etc/rsyslog.conf

```bash
local6.debug /var/log/command.log
```

```bash
service rsyslog restart

apt install lnav -y
```

#### [開啟WSL2的SSH服務](https://2formosa.blogspot.com/2020/07/enable-ssh-server-on-WSL2.html)

```bash
# service ssh start
sshd: no hostkeys available
```

```bash
dpkg-reconfigure openssh-server
service ssh start
```

### FTP

```bash
apt install vsftpd -y

service vsftpd restart
service --status-all
update-rc.d vsftpd enable
```

- vim /etc/vsftpd.conf

```bash
listen=YES
local_enable=YES
write_enable=YES
local_umask=022
use_localtime=NO
pam_service_name=ftp
```

#### Change Port

- vim /etc/vsftpd.conf

```bash
listen_port=2121
```

#### FTPS Setting

```bash
ls -l /etc/ssl/certs/ssl-cert-snakeoil.pem
ls -l /etc/ssl/private/ssl-cert-snakeoil.key
ls -l /etc/ssl/private
```

- openssl req -x509 -nodes -days 3650 -newkey rsa:2048 -keyout /etc/ssl/private/vsftpd.pem -out /etc/ssl/private/vsftpd.pem

```bash
Country Name (2 letter code) [AU]:TW
State or Province Name (full name) [Some-State]:Taiwan
Locality Name (eg, city) []:Hischun
Organization Name (eg, company) [Internet Widgits Pty Ltd]:NCTU
Organizational Unit Name (eg, section) []:School
Common Name (e.g. server FQDN or YOUR name) []:nctu.edu.tw
Email Address []:righthand0521.cs97g@g2.nctu.edu.tw
```

- vim /etc/vsftpd.conf

```bash
rsa_cert_file=/etc/ssl/certs/ssl-cert-snakeoil.pem
# rsa_cert_file=/etc/ssl/private/vsftpd.pem
rsa_private_key_file=/etc/ssl/private/ssl-cert-snakeoil.key
# rsa_private_key_file=/etc/ssl/private/vsftpd.pem
ssl_enable=YES
allow_anon_ssl=NO
force_local_data_ssl=YES
force_local_logins_ssl=YES
ssl_tlsv1=YES
ssl_sslv2=NO
ssl_sslv3=NO
require_ssl_reuse=NO
ssl_ciphers=HIGH
```

#### Anonymous

```bash
mkdir -p /var/www/html/tftp/
chown nobody:nogroup /var/www/html/tftp/
echo "vsftpd test file" | sudo tee /var/www/html/tftp/test.txt
```

- vim /etc/vsftpd.conf

```bash
# Allow anonymous FTP? (Disabled by default).
anonymous_enable=YES
#
#
# Point users at the directory we created earlier.
anon_root=/var/www/html/tftp/
# Stop prompting for a password on the command line.
no_anon_password=YES
# Show the user and group as ftp:ftp, regardless of the owner.
hide_ids=YES
# Limit the range of ports that can be used for passive FTP
pasv_min_port=40000
pasv_max_port=50000
#
#
# Uncomment this to allow local users to log in.
local_enable=YES
#
# Uncomment this to enable any form of FTP write command.
write_enable=YES
#
# Default umask for local users is 077. You may wish to change this to 022,
# if your users expect that (022 is used by most other ftpd's)
local_umask=022
#
# Uncomment this to allow the anonymous FTP user to upload files. This only
# has an effect if the above global write enable is activated. Also, you will
# obviously need to create a directory writable by the FTP user.
anon_upload_enable=YES
#
# Uncomment this if you want the anonymous FTP user to be able to create
# new directories.
anon_mkdir_write_enable=YES
```

```bash
ftp://<IP Address>

# ftp -p <IP Address>
anonymous
```

### RDP

```bash
apt install xrdp -y
apt install tigervnc-standalone-server -y

systemctl enable xrdp

netstat -antpu | grep 3389

cat /var/log/xrdp-sesman.log
cat /var/log/xrdp.log
cat /var/log/Xorg.0.log
```

### Telnet

```bash
apt install xinetd telnetd -y
```

- vim /etc/inetd.conf

```bash
telnet stream tcp nowait telnetd /usr/sbin/tcpd /usr/sbin/telnetd
```

- vim /etc/xinetd.conf

```bash
defaults
{
# Please note that you need a log_type line to be able to use log_on_success
# and log_on_failure. The default is the following :
# log_type = SYSLOG daemon info

instances = 60
log_type = SYSLOG authpriv
log_on_success = HOST PID
log_on_failure = HOST
cps = 25 30
}
```

- vim /etc/xinetd.d/telnet

```bash
service telnet
{
    disable = no
    flags = IPv6
    socket_type = stream
    wait = no
    user = root
    server = /usr/sbin/telnetd
    log_on_failure += USERID
}
```

```bash
/etc/init.d/xinetd restart
service --status-all
systemctl enable xinetd
```

- vim /etc/pam.d/login

```bash
auth required lib/security/pam_securetty.so
auth [success=ok new_authtok_reqd=ok ignore=ignore user_unknown=bad default=die] pam_securetty.so
```

### TFTP

```bash
apt install tftp-hpa tftpd-hpa -y

service tftpd-hpa restart
service --status-all
systemctl enable tftpd-hpa

mkdir /var/www/html/tftp
chmod 0777 /var/www/html/tftp
chown nobody.nogroup -R /var/www/html/tftp
```

- vim /etc/default/tftpd-hpa

```bash
TFTP_USERNAME="tftp"
TFTP_DIRECTORY="/var/www/html/tftp"
TFTP_ADDRESS="0.0.0.0:69"
TFTP_OPTIONS="-l -c -s"
```

```bash
tftp <IP Address>

tftp> get test.txt
tftp> put test.txt
tftp> quit
```

### NTP

- [Taiwan — tw.pool.ntp.org](https://www.ntppool.org/zone/tw)
- [如何在Ubuntu 18.04 LTS上安裝NTP服務器和客戶端](https://ubuntuqa.com/zh-tw/article/8807.html)

```bash
apt install ntpdate -y

ntpdate 211.22.103.157
ntpdate time.stdtime.gov.tw
```

``` bash
apt install ntp -y
```

- vim /etc/ntp.conf

```bash
server 0.tw.pool.ntp.org
server 1.tw.pool.ntp.org
server 2.tw.pool.ntp.org
server 3.tw.pool.ntp.org

ufw allow from any to any port 123 proto udp
```

### X Window

```bash
apt install x11-apps -y

printenv DISPLAY
export DISPLAY=:10.0

xcalc
xclock
xeyes
```

### Xfce4

```bash
apt install xfce4 -y

printenv DISPLAY
export DISPLAY=:10.0

ln -s /usr/bin/startxfce4 /root/.xsession

startxfce4
```

### tmux(1) — terminal multiplexer

```bash
apt install tmux -y
```

```bash
tmux ls   # 列出所有 Sessions
tmux attach -t 0  # 繼續使用第0個Sessions; 若要繼續使用指定的session, 可使用attach並指定要續用的session編號
```

```text
Ctrl+b, 再輸入f        在所有window視窗中搜尋關鍵字

在tmux的環境中, 若想要將window視窗分割成多個pane, 並管理建立的panes, 可以使用以下的操作組合鍵:
Ctrl+b, 再輸入 %        垂直分割視窗
Ctrl+b, 再輸入 "        水平分割視窗
Ctrl+b, 再輸入 o        以輪流方式輪流切換pane
Ctrl+b, 再輸入 方向鍵    切換至指定方向的pane
Ctrl+b, 再輸入 空白鍵    切換佈局
Ctrl+b, 再輸入 !        將目前的pane抽出來, 獨立建立一個window視窗
Ctrl+b, 再輸入 x        關閉目前的pane

若要建立與管理多個windows視窗, 可以使用以下的操作組合鍵:
Ctrl+b, 再輸入 c        建立新window視窗(create)
Ctrl+b, 再輸入 w        以視覺化選單切換window視窗; 在切換視窗時, 如果不清楚每個視窗的內容, 使用Ctrl+b再輸入w的方式, 以選單配合預覽的方式選擇視窗
Ctrl+b, 再輸入 n        切換至下一個window視窗(next)
Ctrl+b, 再輸入 p        切換至上一個window視窗(previous)
Ctrl+b, 再輸入 數字鍵    切換至指定的window視窗
Ctrl+b, 再輸入 &        關閉目前的window視窗

每執行一個tmux就會建立一個 session, 若要列出目前所有的 sessions, 可以執行：
Ctrl+b, 再輸入 $        重新命名目前的session
Ctrl+b, 再輸入 d        分離目前的session(detach), 離開tmux環境
Ctrl+b, 再輸入 s        以視覺化選單切換 session; 在tmux環境之下切換session的時候, 使用Ctrl+b再輸入s的方式, 可以快速預覽每個session並選擇需要的session
Ctrl+b, 再輸入 L        切換至上一個使用過的session
Ctrl+b, 再輸入 (        切換至上一個session
Ctrl+b, 再輸入 )        切換至下一個session
```

#### [在 tmux 裡捲動分割區](http://exsultatech.logdown.com/posts/234936-scrolling-in-tmux-partition)

```text
Ctrl-b, 再輸入 [        在分割區裡面捲動畫面; 進入"copy mode", 可以用 vim 的游標移動指令來操作畫面了.
設定捲動 buffer size    在 ~/.tmux.conf 裡面的這行 set -g history-limit 9999
```

### tree(1) - list contents of directories in a tree-like format.

```bash
apt install tree -y
alias tree='tree --charset ASCII'
alias tree='tree -C --charset ASCII'
alias treel='tree -pugsD --charset ASCII'
```

### 7-Zip

```bash
apt install p7zip-full -y

7z a -ttar -so fileName.tar fileName | 7z a -si fileName.tgz
```

```batch
"C:\Program Files\7-Zip\7z.exe" a -ttar -so fileName.tar fileName | "C:\Program Files\7-Zip\7z.exe" a -si fileName.tgz
```

### Google Chrome

```bash
wget -c https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
dpkg -i google-chrome-stable_current_amd64.deb
```

```bash
dpkg: error processing package google-chrome-stable (--install):
 dependency problems - leaving unconfigured
Processing triggers for desktop-file-utils (0.26-1ubuntu3) ...
Processing triggers for mailcap (3.70+nmu1ubuntu1) ...
Processing triggers for man-db (2.10.2-1) ...
Errors were encountered while processing:

apt --fix-broken install -y
apt install gconf-service -y
dpkg -i google-chrome-stable_current_amd64.deb
```

```bash
google-chrome --version
alias google-chrome='google-chrome -no-sandbox'
```

```bash
apt remove google-chrome-stable
apt purge google-chrome-stable
apt autoremove
rm -rf ~/.config/google-chrome
```

#### [Solving Google Chrome's gpu-process error message in Ubuntu Linux](https://simpleit.rocks/linux/ubuntu/fixing-common-google-chrome-gpu-process-error-message-in-linux/)

```bash
# vim /usr/bin/google-chrome
exec -a "$0" "$HERE/chrome" "$@" --no-sandbox --disable-gpu --disable-software-rasterizer
```

### Google Drive

```bash
add-apt-repository ppa:alessandro-strada/ppa
apt install google-drive-ocamlfuse -y
mkdir ~/google-drive
google-drive-ocamlfuse ~/google-drive
```

### FileZilla

```bash
apt install filezilla -y
```

### upnpc(1) - miniupnpc library test client

- [MiniUPnP Project HomePage](http://miniupnp.free.fr/)
- [Reference Manual: upnpc - interact with an external UPnP Internet Gateway Device](http://v2.nat32.com/upnpc.htm)
- [Use upnpc Mapping to External Network](http://blog.chinaunix.net/uid-20648944-id-3134810.html)

```bash
apt install miniupnpc -y
```

- Add/Delete Port Mapping

```bash
upnpc -a ip port external_port tcp | udp
upnpc -d external_port tcp | udp
```

- List Port Mapping and Status

```bash
upnpc -l
upnpc -s
```

- External IP address

```bash
upnpc -e
```

- Initialize device list

```bash
upnpc -i
```

- Map these ports to this host

```bash
upnpc -r port1 tcp | udp
```

### dibbler

- [DHCPv6: Dibbler - a portable DHCPv6](http://klub.com.pl/dhcpv6/)

```bash
apt install dibbler-server dibbler-client -y

mkdir /var/lib/dibbler
```

- vim /etc/dibbler/server.conf

```bash
# Logging level range: 1(Emergency)-8(Debug)
log-level 8

# Don't log full date
log-mode short

iface "eth0" {
    # clients should renew every half an hour
    t1 1800

    # In case of troubles, after 45 minutes, ask any server
    t2 2700

    # Addresses should be prefered for an hour
    prefered-lifetime 3600

    # and should be valid for 2 hours
    valid-lifetime 7200

    # assign addresses from this pool
    class {
        pool 2001:3633:1111::/48
    }

    # assign /48 prefixes from this pool
    pd-class {
        pd-pool 2001:3633:3333::/48
        pd-length 48
    }

    # provide DNS server location to the clients
    option dns-server 2001:4860:4860::8888,2001:4860:4860::8844

    # provide their domain name
    option domain right.com
}
```

### radvd

- [Linux IPv6 Router Advertisement Daemon (radvd)](https://radvd.litech.org/)

```bash
apt install radvd -y

/etc/init.d/radvd start
/etc/init.d/radvd stop
/etc/init.d/radvd restart
```

- vim /etc/sysctl.conf

```bash
net.ipv6.conf.all.forwarding=1
```

```bash
sysctl -p
```

- vim /etc/rc.local

```bash
# Enable RADVD
```

- vim /etc/radvd.conf

```bash
interface eth0
{
    # Enable Send Route Advertisement(RA)
    AdvSendAdvert on;

    # Enable Managed bit
    AdvManagedFlag on;

    # Enable Other Configure bit
    AdvOtherConfigFlag on;

    # Set min && MAX interval to send RA
    MinRtrAdvInterval 10;
    MaxRtrAdvInterval 30;

    prefix 2001:4861:4861::/64
    {
        AdvOnLink on;
        AdvAutonomous on;
        AdvRouterAddr on;

        AdvPreferredLifetime 55;
        AdvValidLifetime 66;
    };

    route 2001:4191:4191::/64
    {
        AdvRouteLifetime 20;
        AdvRoutePreference medium; #low|medium|high
    };

    RDNSS 2001:4860:4860::8844
    {
        AdvRDNSSLifetime 30;
    };
};
```

## [Magic SysRq key](https://en.wikipedia.org/wiki/Magic_SysRq_key)

- [Linux Magic System Request Key Hacks](https://www.kernel.org/doc/html/latest/admin-guide/sysrq.html)
- [使用 SysRq 鍵讓當機的 Linux 安全地重新開機](https://blog.gtwang.org/linux/safe-reboot-of-linux-using-magic-sysrq-key/)

## Fix Fail Question

### Certificate verification failed: The certificate is NOT trusted. The certificate chain uses expired certificate.

- [apt-get update failed because certificate verification failed because handshake failed on nodesource](https://askubuntu.com/questions/1095266/apt-get-update-failed-because-certificate-verification-failed-because-handshake)

```bash
apt install ca-certificates
```

### Windows 10 Could not Connect to Ubuntu Samba

- [Windows 10 login information for accessing samba share protected directory located on Ubuntu 18.04](https://askubuntu.com/questions/1093290/windows-10-login-information-for-accessing-samba-share-protected-directory-locat)

- vim /etc/samba/smbusers

```bash
root = "root@example.com"
```

- vim /etc/samba/smb.conf

```bash
[global]
username map = /etc/samba/smbusers
```

```bash
service smbd restart
```

### [解決 Ubuntu 20.04 LTS 每次登入出現錯誤訊息" Failed to connect to https://changelogs.ubuntu.com/meta-release-lts. Check your Internet connection or proxy settings "](https://medium.com/@yosblog/%E8%A7%A3%E6%B1%BA-ubuntu-20-04-lts-%E9%8C%AF%E8%AA%A4%E8%A8%8A%E6%81%AF-failed-to-connect-to-https-changelogs-ubuntu-com-meta-release-lts-a67be4fec64b)

```bash
ping google.com
curl https://changelogs.ubuntu.com/meta-release-lts

cat /var/lib/ubuntu-release-upgrader/release-upgrade-available
rm /var/lib/ubuntu-release-upgrader/release-upgrade-available
```

### watchdog: Bug: soft lockup - CPU#1 stuck

```bash
cat /proc/sys/kernel/watchdog_thresh
echo 30 > /proc/sys/kernel/watchdog_thresh

vim /etc/sysctl.conf
# watchdog
kernel.watchdog_thresh=30

sysctl -w kernel.watchdog_thresh=30
sysctl -p

reboot
```
