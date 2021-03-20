Linux
===
### [The Linux Kernel Archives](https://www.kernel.org/)
### [The Linux Kernel documentation](https://www.kernel.org/doc/html/latest/index.html)
---
### Upgrade Ubuntu Operating System to Latest Release
```
# cat /etc/os-release
# do-release-upgrade -d
```
---
### Set Static IP Address in Ubuntu 18.04 LTS
```
# vim /etc/network/interfaces

# The loopback network interface
auto lo
iface lo inet loopback

# The primary network interface
auto ens33
# iface ens33 inet dhcp
iface ens33 inet static
address 192.168.0.1
netmask 255.255.255.0
gateway 192.168.0.254
dns-nameservers 8.8.8.8 168.95.1.1
up ip addr add 192.168.0.1/24
up ip route add 192.168.0.0/24 via 192.168.0.254
up route add -net 192.168.0.0 netmask 255.255.255.0 gw 192.168.0.254
```
### Set Static IP Address in Ubuntu 20.04.1 LTS
```
# cat /etc/cloud/cloud.cfg.d/subiquity-disable-cloudinit-networking.cfg
network: {config: disabled}
```
```
# vim /etc/netplan/00-installer-config.yaml

# This is the network config written by 'subiquity'
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
```
# netplan apply
```
### Set Static IP Address in CentOS, Fedora
```
# vim /etc/sysconfig/network-scripts/ifcfg-ens192

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
---
### root login
```
# sudo -i passwd root
# sudo systemctl get-default
# sudo systemctl set-default multi-user.target
# sudo systemctl isolate multi-user.target
# sudo systemctl get-default
```
```
# sudo vim /lib/systemd/system/getty@.service

ExecStart=-/sbin/agetty --autologin root --noclear %I $TERM
```
---
### Boot to Command Line
```
# systemctl get-default
# systemctl set-default multi-user.target
# systemctl set-default graphical.target
```
---
### Change /bin/sh -> /bin/dash to /bin/sh -> /bin/bash
```
# dpkg-reconfigure dash
no
```
---
### Set Host Name
```
# hostnamectl set-hostname U20x64
```
---
### Auto-Start <Service> on Boot
```
# service --status-all

# update-rc.d <Service> enable
# update-rc.d <Service> disable

# systemctl enable <Service>
# systemctl disable <Service>
```
---
### LAMP: Linux, Apache, MySQL, PHP
```
# apt install tasksel -y
# tasksel
LAMP server
```
```
# apt install apache2
# apt install php
# apt install libapache2-mod-php
# service apache2 restart
# vim phpinfo.php
<?php
    phpinfo();
?>
```
```
# vim /etc/apache2/apache2.conf

# allow html with <?php ?>
AddType application/x-httpd-php .php .htm .html

# /etc/init.d/apache2 stop
# /etc/init.d/apache2 start
```
#### [htpasswd-generator](http://www.htaccesstools.com/htpasswd-generator/)
```
# vim /etc/apache2/.htpasswd

# admin / password
admin:$apr1$4u2HLeXv$ovmebujuSOgLg9VibH4531
```
```
# mkdir /var/www/html/auth
# vim /etc/apache2/sites-enabled/000-default.conf

<VirtualHost *:80>
    <Directory "/var/www/html/auth">
        AuthType Basic
        AuthName "Restricted Content"
        AuthUserFile /etc/apache2/.htpasswd
        Require valid-user
    </Directory>
</VirtualHost>
```
```
# systemctl restart apache2
# service --status-all
# update-rc.d apache2 enable
```
### Change Port
```
# vim /etc/apache2/ports.conf

# Listen 80
Listen 8080

# vim /etc/apache2/sites-enabled/000-default.conf

<VirtualHost *:8080>
```
### [Ubuntu18.04 Apache2 配置 python3 CGI](https://pmvt.cn/develop/python3-apache2-cgi.html)
```
# a2enmod cgid
# systemctl restart apache2
# chmod 705 /usr/lib/cgi-bin/test.cgi
```
### CentOS, Fedora
```
# yum install httpd

# systemctl start httpd.service
# systemctl enable httpd.service

# firewall-cmd --permanent --add-service=http
# firewall-cmd --permanent --add-service=https
# firewall-cmd --reload
# firewall-cmd --list-all

# vim /etc/httpd/conf/httpd.conf

# yum install php
# systemctl restart httpd.service
```
### Installing Apache on Windows Subsystem for Linux
#### [APR_TCP_DEFER_ACCEPT error when starting Apache2 #1953](https://github.com/microsoft/WSL/issues/1953)
```
# vim /etc/apache2/apache2.conf

# (92)Protocol not available: AH00076: Failed to enable APR_TCP_DEFER_ACCEPT
AcceptFilter http none
AcceptFilter https none
```
---
### SSH
```
apt install openssh-server -y
```
```
# vim /etc/ssh/sshd_config

PermitRootLogin yes
```
```
# service ssh restart
# service --status-all
# update-rc.d ssh enable
```
```
ssh/scp without password
# ssh-keygen -t rsa -b 2048
# ssh-copy-id <User Name>@<IP Address>

Remove existed host
# ssh-keygen -f "/root/.ssh/known_hosts" -R "<IP Address>"
```
```
SSH Login Windows 10 Ubuntu bash

# vim /etc/ssh/sshd_config

PasswordAuthentication yes

# ssh-keygen -A
# service ssh --full-restart
```
---
### FTP
```
apt install vsftpd -y
```
```
# vim /etc/vsftpd.conf

local_enable=YES
write_enable=YES
local_umask=022
use_localtime=NO
pam_service_name=ftp
```
```
# service vsftpd restart
# service --status-all
# update-rc.d vsftpd enable
```
```
FTPS Setting

# ls -l /etc/ssl/certs/ssl-cert-snakeoil.pem
# ls -l /etc/ssl/private/ssl-cert-snakeoil.key
# ls -l /etc/ssl/private

# openssl req -x509 -nodes -days 3650 -newkey rsa:2048 -keyout /etc/ssl/private/vsftpd.pem -out /etc/ssl/private/vsftpd.pem
Country Name (2 letter code) [AU]:TW
State or Province Name (full name) [Some-State]:Taiwan
Locality Name (eg, city) []:Hischun
Organization Name (eg, company) [Internet Widgits Pty Ltd]:NCTU
Organizational Unit Name (eg, section) []:School
Common Name (e.g. server FQDN or YOUR name) []:nctu.edu.tw
Email Address []:righthand0521.cs97g@g2.nctu.edu.tw

# vim /etc/vsftpd.conf

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
---
### Samba
```
# apt install samba samba-common -y
```
```
# mkdir WorkingSpace
# smbpasswd -a root
# vim /etc/samba/smb.conf

[global]
# make samba follow symlink outside the shared path
follow symlinks = yes
wide links = yes
unix extensions = no

# Support Windows XP SMB Version
# server max protocol = NT1
min protocol = NT1
lanman auth = yes
ntlm auth = yes

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
```
# service smbd restart
# service --status-all
# update-rc.d smbd enable
```
```
# apt install cifs-utils -y
# mount -t cifs -o user=<id>,pass=<pw> //<Remote IP>/<Remote Path> <Local Path>
# mount -t cifs -o rw,user=<id>,pass=<pw>,vers=1.0 //<Remote IP>/<Remote Path> <Local Path> -v
```
### CentOS, Fedora
```
# yum install samba -y

# pdbedit -a root

# service smb start
# service nmb start
# systemctl enable smb.service
# systemctl enable nmb.service

遇到權限不足時
# vim /etc/selinux/config
SELINUX=disabled

# firewall-cmd --permanent --add-service=samba
# firewall-cmd --reload
# firewall-cmd --list-all

# chkconfig smb on
# chkconfig nmb on
```
---
### tmux(1) — terminal multiplexer
```
# apt install tmux
```
```
列出所有 Sessions
# tmux ls

繼續使用第0個Sessions; 若要繼續使用指定的session, 可使用attach並指定要續用的session編號
# tmux attach -t 0

Ctrl+b, 再輸入f        在所有window視窗中搜尋關鍵字
```
```
Panes(分割視窗)
在tmux的環境中, 若想要將window視窗分割成多個pane, 並管理建立的panes, 可以使用以下的操作組合鍵:
Ctrl+b, 再輸入 %        垂直分割視窗
Ctrl+b, 再輸入 "        水平分割視窗
Ctrl+b, 再輸入 o        以輪流方式輪流切換pane
Ctrl+b, 再輸入 方向鍵   切換至指定方向的pane
Ctrl+b, 再輸入 空白鍵   切換佈局
Ctrl+b, 再輸入 !        將目前的pane抽出來, 獨立建立一個window視窗
Ctrl+b, 再輸入 x        關閉目前的pane
```
```
Windows
若要建立與管理多個windows視窗, 可以使用以下的操作組合鍵:
Ctrl+b, 再輸入 c        建立新window視窗(create)
Ctrl+b, 再輸入 w        以視覺化選單切換window視窗; 在切換視窗時, 如果不清楚每個視窗的內容,
                        使用Ctrl+b再輸入w的方式, 以選單配合預覽的方式選擇視窗
Ctrl+b, 再輸入 n        切換至下一個window視窗(next)
Ctrl+b, 再輸入 p        切換至上一個window視窗(previous)
Ctrl+b, 再輸入 數字鍵   切換至指定的window視窗
Ctrl+b, 再輸入 &        關閉目前的window視窗
```
```
Sessions
每執行一個tmux就會建立一個 session, 若要列出目前所有的 sessions, 可以執行：
Ctrl+b, 再輸入 $        重新命名目前的session
Ctrl+b, 再輸入 d        分離目前的session(detach), 離開tmux環境
Ctrl+b, 再輸入 s        以視覺化選單切換 session; 在tmux環境之下切換session的時候,
                        使用Ctrl+b再輸入s的方式, 可以快速預覽每個session並選擇需要的session
Ctrl+b, 再輸入 L        切換至上一個使用過的session
Ctrl+b, 再輸入 (        切換至上一個session
Ctrl+b, 再輸入 )        切換至下一個session
```
#### [在 tmux 裡捲動分割區](http://exsultatech.logdown.com/posts/234936-scrolling-in-tmux-partition)
```
Ctrl-b, 再輸入 [        在分割區裡面捲動畫面; 進入"copy mode", 可以用 vim 的游標移動指令來操作畫面了.
設定捲動 buffer size    在 ~/.tmux.conf 裡面的這行 set -g history-limit 9999
```
---
### RDP
```
# apt install xrdp -y
# apt install tigervnc-standalone-server -y
# systemctl enable xrdp
# netstat -antpu | grep 3389
tcp6    0    0 :::3389    :::*    LISTEN    1893/xrdp
```
---
### Telnet
```
# apt install xinetd telnetd -y
```
```
# vim /etc/inetd.conf

telnet stream tcp nowait telnetd /usr/sbin/tcpd /usr/sbin/in.telnetd
```
```
# vim /etc/xinetd.conf

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
```
# vim /etc/xinetd.d/telnet

service telnet
{
    disable = no
    flags = IPv6
    socket_type = stream
    wait = no
    user = root
    server = /usr/sbin/in.telnetd
    log_on_failure += USERID
}
```
```
# /etc/init.d/xinetd restart
# service --status-all
# systemctl enable xinetd
```
```
# vim /etc/pam.d/login

# auth required lib/security/pam_securetty.so
# auth [success=ok new_authtok_reqd=ok ignore=ignore user_unknown=bad default=die] pam_securetty.so
```
### CentOS, Fedora
```
# yum install telnet-server -y

# systemctl enable telnet.socket
# systemctl start telnet.socket

# firewall-cmd --permanent --add-port=23/tcp
# firewall-cmd --reload
# firewall-cmd --list-port
# firewall-cmd --list-all
```
---
### TFTP
```
# apt install tftp-hpa tftpd-hpa -y
```
```
# mkdir /var/www/html/tftp
# chmod 0777 /var/www/html/tftp
# chown nobody.nogroup -R /var/www/html/tftp
# vim /etc/default/tftpd-hpa

TFTP_USERNAME="tftp"
TFTP_DIRECTORY="/var/www/html/tftp"
TFTP_ADDRESS="0.0.0.0:69"
TFTP_OPTIONS="-l -c -s"
```
```
# service tftpd-hpa restart
# service --status-all
# systemctl enable tftpd-hpa
```
```
# tftp <IP Address>
tftp> get test.txt
tftp> put test.txt
tftp> quit
```
---
### NTP
```
# apt install ntpdate -y
# ntpdate 211.22.103.157
# ntpdate time.stdtime.gov.tw
```
---
### vim
```
# apt install vim -y
# apt install vim-gtk -y
# vim --version | head -n2

:%! xxd			// Vim 16 進位編輯器
:%! xxd -r		// Vim 使用 xxd -r 轉換為二進位資料
```
---
### 7-Zip
```
# apt install p7zip-full -y
```
---
### tree(1) - list contents of directories in a tree-like format.
```
# apt install tree -y
# alias tree='tree --charset ASCII'
# alias tree='tree -C --charset ASCII'
# alias treel='tree -pugsD --charset ASCII'
```
### CentOS, Fedora
```
# yum install tree -y
```
---
### Adjust Date Time
```
# timedatectl set-timezone 'Asia/Taipei'
# timedatectl set-timezone UTC
# localectl set-locale LC_TIME=en_GB.UTF-8
```
### CentOS, Fedora
```
# rm -f /etc/localtime; ln -s /usr/share/zoneinfo/Asia/Taipei /etc/localtime
# rm -f /etc/localtime; ln -s /usr/share/zoneinfo/GMT /etc/localtime
```
---
### crontab -l
```
# cat /var/spool/cron/crontabs/root
```
```
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
Set MAILTO variable to stop cron daemon from sending email
```
# Output of the crontab jobs (including errors) is sent through
# email to the user the crontab file belongs to (unless redirected).
MAILTO=""
```
---
### source /etc/bash.bashrc
```
# @reboot
tabs 4

# export
export LESS_TERMCAP_mb=$'\e[1;32m'
export LESS_TERMCAP_md=$'\e[1;32m'
export LESS_TERMCAP_me=$'\e[0m'
export LESS_TERMCAP_se=$'\e[0m'
export LESS_TERMCAP_so=$'\e[01;33m'
export LESS_TERMCAP_ue=$'\e[0m'
export LESS_TERMCAP_us=$'\e[1;4;31m'

# alias
alias tree='tree --charset ASCII'
alias tree='tree -C --charset ASCII'
alias treel='tree -pugsD --charset ASCII'
alias targzc='tar -zcvf'
alias targzd='tar -zxvf'
alias tarbz2c='tar jcvf'
alias tarbz2d='tar jxvf'
alias grepin='grep --color=auto -irnw --include=*.{c,cpp,h}'
alias pylint='pylint --disable=missing-docstring'
alias google-chrome='google-chrome -no-sandbox'
```
---
### source ~/.bashrc
```
force_color_prompt=yes
```
---
###	vim /etc/sudoers
```
# Allow members of group sudo to execute any command
%sudo   ALL=(ALL:ALL) ALL
right   ALL=(ALL:ALL) NOPASSWD:ALL
jenkins ALL=(ALL:ALL) NOPASSWD:ALL
```
---
###	[Magic SysRq key](https://en.wikipedia.org/wiki/Magic_SysRq_key)
#### [Linux Magic System Request Key Hacks](https://www.kernel.org/doc/html/latest/admin-guide/sysrq.html)
#### [使用 SysRq 鍵讓當機的 Linux 安全地重新開機](https://blog.gtwang.org/linux/safe-reboot-of-linux-using-magic-sysrq-key/)
---
### [yum(8) - Linux man page](https://linux.die.net/man/8/yum)
```
# cd /etc/yum.repos.d/
# cd /etc/pki/rpm-gpg
# wget https://www.centos.org/keys/RPM-GPG-KEY-CentOS-7 --no-check-certificate
# rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6

# yum clean all
# yum update
```
#### [yum Tutorial and Examples](https://blog.gtwang.org/linux/yum-linux-command-tutorial-and-examples/)
---
