# Linux

- A space before a bash command is not recorded in history

## /dev/null

```bash
2> /dev/null
&> /dev/null
> /dev/null 2>&1
```

## arp-scan(1) - The ARP scanner

```bash
apt install arp-scan -y

arp-scan --interface eth0 192.168.0.0/24
arp-scan --interface eth0 --localnet
```

## awk(1) - pattern scanning and processing language

- awk 'pattern + {action}'

```bash
awk '{print $0}'
awk '{print $NF,$0}'
awk '{print substr($0,2,length($0)-2)}'

awk '{if(length($0)>20) print $0}'

awk '/inet / {print $2}'
awk '/inet addr/ {print substr($2,6)}'

awk '{a[$2]++}END {for(i in a) {print a[i] " " i}}'
awk '{total+=$2}END {print total}'
awk 'match($0, /[[:digit:]]{10}([^,]+)/) { print substr( $0, RSTART, RLENGTH )}'

awk -F":" '{print $1}'
awk -v s=$start '$1 >= s && $1 <= $(date"+%s") {print}'
```

- remove newline

```bash
# awk NF=NF RS= OFS=+
```

## bc(1) - An arbitrary precision calculator language

```bash
echo "5+50*3/20 + (19*2)/7" | bc
echo "5+50*3/20 + (19*2)/7" | bc -l
echo "scale=3; 5+50*3/20 + (19*2)/7" | bc -l

printf "%.3f\n" $(echo "5+50*3/20 + (19*2)/7" | bc -l)

echo "obase=2; 11" | bc
```

## crontab(1) - maintain crontab files for individual users (Vixie Cron)

- [Cron expression generator by Cronhub. Schedule and monitor jobs without any infra work.](https://crontab.cronhub.io/)

```bash
ls -l /var/spool/cron/crontabs/
```

```bash
# m h  dom mon dow   command
# m分鐘(0-59), h小時(0-23), dom日期(1-31), mon月份(1-12), dow星期(0-6), command需要執行的command.
# '*'    代表任何時刻都接受的意思
# ','    代表分隔時段        30 9,17 * * * command => 早上9點半和下午五點半都執行command
# '-'    代表一段時間範圍    15 9-12 * * * command => 從9點到12點的每個15分都執行command
# '/n'   代表每n個單位間隔   */5 * * * *   command => 每隔5分鐘執行一次command)
#
# For more information see the manual pages of crontab(5) and cron(8)
# @reboot  Run once at startup
# @yearly  Run once a year     0 0 1 1 * command
# @monthly Run once a month    0 0 1 * * command
# @weekly  Run once a week     0 0 * * 0 command
# @daily   Run once a day      0 0 * * * command
# @hourly  Run once an hour    0 * * * * command
```

```bash
0 1 * * *           tar -zcvf $(date +"\%Y\%m\%d").tgz /var/lib/jenkins/jobs
0 0,6,12,18 * * *   tar -zcvf /root/`date +"\%Y\%m\%d"`.tgz tmp/; chmod 744 `date +"\%Y\%m\%d"`.tgz
```

## curl(1) - transfer a URL

- 通過使用 -v 和 -trace獲取更多的連結資訊

```bash
curl ipinfo.io
curl ifconfig.me
curl v4.ifconfig.co
curl v6.ifconfig.co
```

```bash
curl --connect-timeout 3 --max-time 3 --retry 3 <HTTP URL>
curl --local-port $(((RANDOM%10000)+10000)) <HTTP URL>
curl -w "Status Code: %{http_code}" <HTTP URL>
curl <HTTP URL> --output <Local File Path>
curl -s --insecure <HTTP URL>
```

```bash
curl -v --proxy-insecure -x https://192.168.0.1:3128 -k -L https://www.google.com/
curl -v --proxy-insecure -x https://admin:password@192.168.0.1:3128 -k -L https://www.google.com/
```

- 列出public_html下的所有資料夾和檔案 and 下載xss.php檔案

```bash
curl -u ftpuser:ftppass -O ftp://ftp_server/public_html/
curl -u ftpuser:ftppass -O ftp://ftp_server/public_html/xss.php
```

- 上傳檔案到FTP伺服器, 通過 -T 選項可將指定的本地檔案上傳到FTP伺服器上
  - 將myfile.txt檔案上傳到伺服器
  - 同時上傳多個檔案
  - 從標準輸入獲取內容儲存到伺服器指定的檔案中

```bash
curl -u ftpuser:ftppass -T myfile.txt ftp://ftp.testserver.com
curl -u ftpuser:ftppass -T "{file1,file2}" ftp://ftp.testserver.com
curl -u ftpuser:ftppass -T - ftp://ftp.testserver.com/myfile_1.txt
```

- Send Email

```bash
echo 'From: <sender@example.com>' >> mail.txt
echo 'To: <receiver@example.com>' >> mail.txt
echo 'Subject: Sending Email Using Curl' >> mail.txt
curl -v --insecure "smtp://msa.hinet.net:25" --mail-from "<example@gmail.com>" --mail-rcpt "<example@gmail.com>" -T mail.txt
```

## cut(1) - remove sections from each line of files

- This prints each line of the input starting at column 6

```bash
cut -c6- <file>
```

## date(1) - print or set the system date and time

- [Epoch & Unix Timestamp Conversion Tools](https://www.epochconverter.com/)

```bash
date +"%Y/%m/%d %H:%M:%S"
date +"%Y/%m/%d %H:%M:%S" -d yesterday
date +"%Y/%m/%d %H:%M:%S" --date='@2147483647'
date -D "%s" -d $(( $(date +%s) - 86400))
date -s @'1558403074'
```

- Date to Timestamp

```bash
date -d "2019-10-06T22:20:36+08:00" +%s
```

- Timestamp to Date

```bash
date "+%Y-%m-%d %T" --date=@1601867260
```

```bash
while sleep 1; do tput sc; tput cup 0 $(($(tput cols)-32)); date +"%s: %Y/%m/%d %H:%M:%S"; tput rc; done
```

## dd(1) - convert and copy a file

```bash
dd if=/dev/zero of=zero.dat; rm -f zero.dat
dd if=/dev/zero of=1MB count=1024 bs=1024
dd if=/dev/zero bs=1K count=1 >> helloWorld
```

## diff(1) - compare files line by line

```bash
diff -ruN ori/ new/ > file.patch
```

```text
-r: recursive, so do subdirectories.
-u: unified style, if your system lacks it or if recipient may not have it, use "-c".
-N: treat absent files as empty.
```

## dos2unix(1) - DOS/MAC to UNIX text file format converter

```bash
apt install dos2unix -y
```

```bash
find . -type f -print0 | xargs -0 dos2unix
```

## dpkg(1) - package manager for Debian

- 列出已安裝的'package'

```bash
dpkg -l
```

- 顯示該'package'的版本

```bash
dpkg -l package
```

- 列出與該'package'關聯的文件

```bash
dpkg -L package
```

## du(1) - estimate file space usage

```bash
du --max-depth=1 -h <path>
```

## ethtool(8) - query or control network driver and hardware settings

```bash
ethtool -i eth0

ethtool -K eth0 tso off
ethtool -K eth0 gro off
ethtool -K eth0 gso off
ethtool -K eth0 tx off
ethtool -K eth0 sg off
ethtool -K eth0 rvo off
ethtool -K eth0 rx-vlan-offload off

ethtool -k eth0 | grep ": on"
```

## export - Set export attribute for shell variables.

```bash
export TERM=xterm
```

## find(1) - search for files in a directory hierarchy

```bash
find . -name "*.asp" -exec bash -c 'mv "$1" "${1%.asp}".html' - '{}' \;

find . -name "*.o" -exec ls -l {} \;
find . -regex '.*\(so\|pyc\|xml\|html\)$' -exec ls -l {} \;
find . -type f -newermt 2018-12-01 ! -newermt 2018-12-02 -exec ls -l {} \;

find . -name "*.o" -exec echo rm -rf {} \; -exec rm -rf {} \;
find . -regex '.*\(so\|pyc\|xml\|html\)$' -exec echo rm -rf {} \; -exec rm -rf {} \;
find . -type f -newermt 2018-12-01 ! -newermt 2018-12-02 -exec echo rm -rf {} \; -exec rm -rf {} \;
```

- [How to replace spaces in file names using a bash script](https://stackoverflow.com/questions/2709458/how-to-replace-spaces-in-file-names-using-a-bash-script)

```bash
find -name "* *" -type d | rename 's/ /_/g'
find -name "* *" -type f | rename 's/ /_/g'
```

## ftpput(1) - Upload a file to a ftp server

```bash
ftpput -u <ID> -p <PW> -P <Port> <IP Address> <dst target path> <src file path>
```

## grep(1) - print lines matching a pattern

- [Regular expressions in grep ( regex ) with examples](https://www.cyberciti.biz/faq/grep-regular-expressions/)

```bash
grep -rl ".asp" . | xargs -i sed -i 's/.asp/.html/g' {}
```

## history(3) - GNU History Library

-List of commands you use most often

```bash
history | awk '{a[$2]++}END {for(i in a) {print a[i] " " i}}' | sort -rn | head
```

## hping3(8) - send (almost) arbitrary TCP/IP packets to network hosts

```bash
hping3 -q -n -a 10.0.0.1 --udp -s 53 --keep -p 68 --flood 192.168.0.1
hping3 -i u10000 -S -p 80 192.168.0.1
hping3 -c 10 -d 120 -S -w 64 -p 21 --flood --rand-source 192.168.0.1
```

## httperf(1) - HTTP performance measurement tool

```bash
httperf --hog --server 192.168.0.1 --num-conn 2500 --rate 500 --num-call 1 --timeout 5 --port 80
```

## ifconfig(8) - configure a network interface

```bash
ifconfig eth0 | awk '/inet / {print $2}' | cut -f 2 -d :
ifconfig eth0 promisc
ifconfig eth0 -promisc
```

## inotifywait(1) - inotifywait, fsnotifywait - wait for changes to files using inotify or fanotify

```bash
apt install inotify-tools -y

inotifywait -m -r /tmp/monitor
inotifywait -m -r -e create /tmp/monitor
inotifywait -m -r -e create /tmp/monitor | while read -r directory action file; do \
echo "${action}, ${directory}${file}"; \
done
```

## ip(8) - show / manipulate routing, devices, policy routing and tunnels

```bash
ip -c -br a
ip addr show eth0 | awk '/inet / {print $2}' | cut -f 1 -d /
```

```bash
ip addr add [IP Address]/16 dev [Interface]
ip addr del [IP Address]/16 dev [Interface]
```

```bash
ip link set eth0 mtu 1500
ip link set eth0 promisc on
ip link set eth0 promisc off
```

```bash
ip route add 172.16.0.0/16 dev eth0
ip route add 172.16.0.0/16 via 192.168.0.1 dev eth0
```

```bash
ip tunnel add tun6to4 mode sit ttl 128 remote 192.168.0.1 local 192.168.0.2
ip link set dev tun6to4 up
ip -6 addr add 2002:c0a8:38fe::1/24 dev tun6to4

ip -6 addr del 2002:c0a8:38fe::1/16 dev tun6to4
ip link set dev tun6to4 down
ip tunnel del tun6to4 mode sit ttl 128 remote 192.168.0.1 local 192.168.0.2
```

## iperf(1) - perform network throughput tests

```bash
iperf -s

iperf -c 192.168.0.1 -w 100M -t 120 -i 10
```

```text
-c 192.168.0.1: Server端的IP
-w 100M: 測試的檔案大小
-t 120: 監視測量數據時間為120秒
-i 10: 每隔10秒將數據顯示出來
```

## jq(1) - Command-line JSON processor

```bash
echo 0 | jq 'todate'
echo 2147483647 | jq 'todate'
echo 4294967297 | jq 'todate'
jq -n '0 | strftime("%FT%T%z")'
```

```bash
echo '{"a":"1", "b":"2", "c":"3"}' | jq -r 'keys[]'
echo '[{"username":"user1"},{"username":"user2"}]' | jq '. | length'
echo '{"users":[{"username":"user1"},{"username":"user2"}]}' | jq '.users | length'
```

```bash
echo '[{"id":"u1", "pw":"p1"},{"id":"u2", "pw":"p2"}]' | jq -c '.[]'
echo '[{"id":"u1", "pw":"p1"},{"id":"u2", "pw":"p2"}]' | jq -r '.[] | select(.id == "u2")'
```

```bash
echo '[{"username":"user1"},{"username":"user2"}]' | jq '.+ [{"username":"user3"}]'
```

```bash
echo '[{"id":"u1", "pw":"p1", "name":"n1"},{"id":"u2", "pw":"p2", "name":"n2"}]' \
| jq -r '. | keys[] as $k | "\($k), \(.[$k] | .id), \(.[$k] | .name)"'
```

- Update one value in array of dicts, using jq

```bash
echo '[{"format":"geojson","id":"foo"},{"format":"geojson","id":"bar"},{"format":"zip","id":"baz"}]' \
| jq 'map(if .id=="baz" then .format="csv" else . end)' | jq -c .

echo '[{"format":"geojson","id":"foo"},{"format":"geojson","id":"bar"},{"format":"zip","id":"baz"}]' \
| jq 'map((select(.id == "baz") | .format) |= "csv")' | jq -c .
```

```bash
jq --arg arg1 ${arg1} --arg arg2 ${arg2} '.[].arg1 = $arg1 | .[].arg1 = $arg1 | .[].arg2 = $arg2 | del(.[].arg3)'
```

## ln(1) - make links between files

```bash
ln -s <target path><symbolic path>
```

## man(1) - an interface to the system reference manuals

```bash
apt install manpages-dev -y
```

- Convert man Page Info to pdf Format: man -t <Command Name> | ps2pdf - <File Name>.pdf

```bash
man -t ls | ps2pdf - ls.pdf
```

```bash
man sleep
man 3 sleep
```

```text
Linux的man手冊共有以下幾個章節
1，標準命令
2，系統調用
3，庫函數
4，專用設備（設備說明）
5，文件格式（文件格式）
6，遊戲和玩具（遊戲和娛樂）
7，雜項
8，行政命令（Administrative Commands）
```

## minicom(1) - friendly serial communication program

```bash
apt install minicom -y

alias minicom='minicom --color=on'
```

```bash
dmesg | grep tty
ls -l /dev/ttyUSB0
lsusb

cat < /dev/ttyUSB0 >| test
```

- minicom -s

```bash
- 選擇A設定  "Serial port setup"
- 選擇B設定Serial device為/dev/ttyUSB0
- 選擇E設定BPS/Par/Bits為11520 8N1
- 選擇F設定Hardware flow control 為  No
- 選擇G設定Software flow control 為  No
- 按一下enter回上一層選單準備儲存設定值。
- 選擇selected "save setup as dfl"
- 選擇slected "exit from minicom"
```

```bash
minicom
minicom --capturefile=testFile
```

```bash
# vim script.txt
start:
    expect "boot"
    send ""
    send "ls"
    sleep 1
    goto start

minicom -S script.txt -C output.txt
```

## nc, netcat(1) - arbitrary TCP and UDP connections and listens

- Port Scanning

```bash
netcat -z -n -v <IP> <Port Range> 2>&1 | grep succeeded
nc -z -n -v 192.168.0.1 1-1000 2>&1 | grep succeeded
```

## ncat(1) - Concatenate and redirect sockets

>> <https://ithelp.ithome.com.tw/articles/10278494>

```bash
apt install ncat -y
```

```text
-l 啟動監聽模式
-v 輸出詳細資訊
-n 不要解析 DNS
-p 指定 port
-e 設定連線後執行的程式
```

```bash
ncat -lvn -p <port>
ncat <IP> <port> -e /bin/bash
ncat -l -p 1234 -vn
ncat -l -p 1234
ncat -l -p 1234 -u
```

## ncdu(1) - NCurses Disk Usage

```bash
apt install ncdu -y
```

## netstat(8) - Print network connections, routing tables, interface statistics, masquerade connections, and multicast memberships

- netstat -ntulp

```bash
t: tcp
u: udp
n: don't resolve names
l: display listening server sockets
p: display PID/Program name for sockets
```

## nl(1) - number lines of files

### openssl(1) - OpenSSL command line tool

```bash
apt install libpcap-dev libssl-dev -y
```

```bash
openssl version -a
openssl ciphers -v
```

- Generate ROOT CA

```bash
openssl genrsa -des3 -out CA.key 2048
chmod og-rwx CA.key

openssl req -new -key CA.key -out CA.req
openssl x509 -req -days 3650 -sha1 -extensions v3_ca -signkey CA.key -in CA.req -out CA.crt

rm -f CA.req
```

- Generate Server CA

```bash
openssl genrsa -out FTPServer.key 1024
chmod og-rwx FTPServer.key

openssl req -new -key FTPServer.key -out FTPServer.req
openssl x509 -req -days 730 -sha1 -extensions v3_req -CA CA.crt -CAkey CA.key -CAserial CA.srl -CAcreateserial \
-in FTPServer.req -out FTPServer.crt

rm -f FTPServer.req
```

- Generate Client CA

```bash
openssl genrsa -des3 -out ClientCA.key 2048
chmod og-rwx ClientCA.key

openssl req -new -key ClientCA.key -out ClientCA.req
openssl x509 -req -days 730 -sha1 -extensions v3_req \
-CA RootCA.crt -CAkey RootCA.key  -CAserial RootCA.srl -CAcreateserial \
-in ClientCA.req -out ClientCA.crt

rm -f ClientCA.req

openssl pkcs12 -export -in ClientCA.crt -inkey ClientCA.key -out ClientCA.pfx
```

- To encrypt with aes-256-cbc cipher

```bash
openssl enc -aes-256-cbc -e -in <input_file> -out <output_file>
```

- To decrypt an encrypted file

```bash
openssl enc -aes-256-cbc -d -in <input_file> -out <output_file>
```

-To list all available cipher algorithms

```bash
openssl list-cipher-algorithms
```

## patch(1) - apply a diff file to an original

```bash
patch -p0 < file.patch
```

## ping, ping6(8) - send ICMP ECHO_REQUEST to network hosts

```text
-q quiet
-c nb of pings to perform
```

## pkill(1) - look up or signal processes based on name and other attributes

```bash
pkill -kill -t pts/1
```

## printenv(1) - print all or part of environment

```bash
printenv PATH
echo $PATH
```

## pstree(1) - display a tree of processes

## route(8) - show / manipulate the IP routing table

```bash
route [-A inet|inet6][-6] -n
route add default gw <IP Address> <Adapter>
route delete default gw <IP Address> <Adapter>
```

## rsync(1) - a fast, versatile, remote (and local) file-copying tool

```bash
rsync -azP <source> <destination>
rsync -avzh <Local Path> <Remote ID>@<Remote IP>:<Remote Path>
```

## scp(1) — secure copy (remote file copy program)

```bash
scp <Local Path> <Remote User>@<Remote IP>:/<Remote Path>
scp <Remote User>@<Remote IP>:/<Remote Path> <Local Path>
```

```bash
-O
Use the legacy SCP protocol for file transfers instead of the SFTP protocol.
Forcing the use of the SCP protocol may be necessary for servers that do not implement SFTP,
for backwards compatibility for particular filename wildcard patterns
and for expanding paths with a '~' prefix for older SFTP servers.
```

## sed(1) - stream editor for filtering and transforming text

```bash
sed -i 's#\(.*/root:\).*#\1/bin/sh#' /etc/passwd
sed -i -e 's|#force_color_prompt=yes|force_color_prompt=yes|' .bashrc
```

```bash
version="$(cat /proc/version | awk '/Linux/ {print $3}')"
src='KERN_DIR="/usr/src/linux-headers-3.19.0-25-generic"'
dst='KERN_DIR="/usr/src/linux-headers-'$version'"'
sed -i -e "s#$src#$dst#" test.txt
```

```bash
echo "10.0.0.1" | sed -e 's/10.0.0/192.168.1/g'
t1="10.0.0"; t2="192.168.1"; echo "10.0.0.1" | sed -e "s/$t1/$t2/g"
```

- Remove NewLine

```bash
sed ':a;N;$!ba;s/\n/+/g'
```

- Removing ANSI Color Codes from Text Stream

```bash
echo -e '\e[0;32m{"ip":"192.168.0.1","online":true}\e[0m' | sed 's/\x1b\[[0-9;]*m//g'
echo -e '\e[0;32m{"ip":"192.168.0.1","online":true}\e[0m' | sed -r "s/\x1B\[([0-9]{1,3}(;[0-9]{1,2})?)?[mGK]//g"
```

```bash
sed 's/^M$//'
sed 's/\r$//'
sed -r "s/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[mGK]//g"
sed ':a;N;$!ba;s/\n/\n\t\t/g'
```

## seq(1) - print a sequence of numbers

```bash
seq -w 1 11
```

## ser2net(8) - Serial to network proxy

```bash
apt install ser2net -y
```

```bash
cat /etc/ser2net.conf
service --status-all
update-rc.d ser2net enable
systemctl enable ser2net
```

## socat(1) - Multipurpose relay (SOcket CAT)

```bash
apt install socat -y
```

```bash
# Syslog Server
socat -u udp4-listen:514, bind=192.168.0.1 open:/tmp/syslog, creat, append
```

## ssh(1) - OpenSSH SSH client (remote login program)

```bash
ssh -o ConnectTimeout=10 -o StrictHostKeyChecking=no root@<IP>
ssh -o ServerAliveInterval=600 root@<IP>

ssh -vv -oCiphers=aes128-cbc,3des-cbc,blowfish-cbc <IP>
ssh -vv -oMACs=hmac-md5 <IP>

ssh -o "Compression yes" -vv <IP>
ssh -o "Compression no" -vv <IP>

ssh -C -vv <IP>
```

## sshpass(1) - noninteractive ssh password provider

```bash
apt install sshpass -y
```

- Provide password as argument (security unwise)

```bash
sshpass -p <password> ssh -o StrictHostKeyChecking=no -p <port> <username>@<IP> '<command>'
```

- Take password to use from file

```bash
sshpass -f <password filename> ssh -o StrictHostKeyChecking=no -p <port> <username>@<IP> '<command>'
```

- Password is passed as env-var "SSHPASS"

```bash
export SSHPASS='password'
sshpass -e ssh -o StrictHostKeyChecking=no -p <port> <username>@<IP> '<command>'
```

- scp remote file to local

```bash
sshpass -p <password> scp <username>@<IP>:$<remote path> <local path>
```

- scp local file to remote

```bash
sshpass -p <password> scp <local path> <username>@<IP>:$<remote path>
```

## stat(1) - display file or file system status

```bash
stat -c "%a %n" <file path>
```

## strace(1) - trace system calls and signals

- strace -f <cmd>

```bash
strace -f ping localhost &> log
```

- strace -p <pid>

```bash
strace -p $(ps aux | grep ping | grep -v grep | awk '{print $1}')
```

## stty(1) - change and print terminal line settings

- stty -F /dev/ttyUSB0

```text
speed 115200 baud; line = 0;
min = 1; time = 5;
ignbrk -brkint -icrnl ixoff -imaxbel
-opost -onlcr
-isig -icanon -iexten -echo -echoe -echok -echoctl -echoke
```

```bash
stty -a -F /dev/ttyUSB0

stty -F /dev/ttyUSB0 115200 -echo igncr -icanon onlcr ixon min 0 time 5
stty -F /dev/ttyUSB0 speed 115200 cs8 -parenb -cstopb -echo

exec 5<>/dev/ttyUSB0
cat <&5
echo "test" >&5
exec 5<&-
```

- [How to change the width of remote serial console?](https://unix.stackexchange.com/questions/106644/how-to-change-the-width-of-remote-serial-console)

```bash
stty rows 50 cols 132
```

## tac(1) - concatenate and print files in reverse

## tabs(1) - set tabs on a terminal

## tail(1) - output the last part of files

```bash
tail -f <path> --pid=<pid>
```

```bash
apt install multitail -y
```

## tar(1) - an archiving utility

```bash
tar cvf <File>.tar <Dir Path>
tar xvf <File>.tar

tar zcvf <File>.tgz <Dir Path>
tar zxvf <File>.tgz

tar jcvf <File>.tbz2 <Dir Path>
tar jxvf <File>.tbz2
```

## tc(8) - show / manipulate traffic control settings

```bash
# up interface
ifconfig ens38 up
# ingress
tc qdisc add dev ens38 ingress
tc filter add dev ens38 parent ffff: protocol all u32 match u8 0 0 action mirred egress mirror dev ens35
# egress
tc qdisc add dev ens38 handle 1: root prio
tc filter add dev ens38 parent 1: protocol all u32 match u8 0 0 action mirred egress mirror dev ens35

# cleanup
tc qdisc del dev ens38 ingress
tc qdisc del dev ens38 root
# down interface
ifconfig ens38 down
```

- [使用Kernel NetEm和tc模擬復雜網絡環境](https://www.codeprj.com/zh/blog/9ce0a71.html)

```bash
modprobe sch_netem

tc qdisc add dev ens38 handle ffff: ingress
tc filter add dev ens38 parent ffff: matchall action mirred ingress mirror dev ens35
tc filter add dev ens38 parent ffff: matchall action mirred egress mirror dev ens35
tc filter add dev ens38 parent ffff: protocol ip u32 match ip protocol 6 0xff action mirred egress mirror dev ens35
tc filter add dev ens38 parent ffff: protocol ip u32 match ip protocol 6 0xff ip dport 80 0xffff action mirred egress mirror dev ens35

tc -s qdisc ls dev ens38
tc -s -p filter ls dev ens38 parent ffff:

tc filter del dev ens38 parent ffff:
tc qdisc del dev ens38 handle ffff: ingress
```

- [lonelymtn/mirror-port.sh](https://gist.github.com/lonelymtn/5a3e0f7d4a44f95141a7)

## tcpdump(8) - dump traffic on a network

```bash
tcpdump -C 100 -nnvvXSs 1514 -w `uname -n`_`date +"%Y%m%d%H%M%S"`.pcap
tcpdump -G 86400 -nnvvXSs 1514 -w %Y%m%d%H%M%S.pcap
```

```bash
tcpdump -nn ether host aa:bb:cc:11:22:33
tcpdump -nn src host 192.168.0.1
tcpdump -nn not port 23
tcpdump -nn udp and port 5353 and 5354
tcpdump -nn net not 192.168.0.0/24
```

```bash
tcpdump -nni eth0 arp
tcpdump -nni eth0 icmp
```

```bash
tcpdump -i eth0 'ether[20:2] == 0x2000'
```

- RIPv2

```bash
tcpdump -i eth0 -v -s0 udp and port 520
```

- RIPng

```bash
tcpdump -i eth0 -v -s0 udp and port 521
```

- DHCP

```bash
tcpdump -i eth0 port 67 or port 68 -e -n
```

- DHCPv6

```bash
tcpdump -i eth0 port 546 or port 547 -e -n
```

- LLDP

```bash
tcpdump -i eth0 ether proto 0x88cc
```

```bash
tcpdump -r file.pcap
tcpdump -r file.pcap -#enqt > output.txt 2>&1
tcpdump -xXr file.pcap | awk '{print $10}'
```

- Split Pcap Size

```bash
tcpdump -r <pcap file> -w <output pcap file> -C <Per Pcap Size>
```

## [Tcpreplay - Pcap editing and replaying utilities](https://tcpreplay.appneta.com/)

```bash
apt install tcpreplay -y
```

- Install - tcpreplay version: 4.3.1 (build git:v4.3.1)

```bash
apt install build-essential libpcap-dev -y
wget https://github.com/appneta/tcpreplay/releases/download/v4.3.1/tcpreplay-4.3.1.tar.xz
tar -xJf tcpreplay-4.3.1.tar.xz
cd tcpreplay-4.3.1
./configure
make
make install
ln -s /usr/local/bin/tcpreplay
ln -s /usr/local/bin/tcpprep
ln -s /usr/local/bin/tcprewrite"
```

### tcpprep(1) - Create a tcpreplay cache cache file from a pcap file

```bash
tcpprep --auto=client --pcap=test.pcap --cachefile=test.cache
```

### tcprewrite(1) - Rewrite the packets in a pcap file

```bash
tcprewrite --enet-dmac=00:00:00:11:11:11,00:00:00:11:11:12 --enet-smac=ff:ff:ff:11:11:11,ff:ff:ff:11:11:12 \
--endpoints=192.168.0.1:192.168.1.1 --cachefile=test.cache --infile=test.pcap --outfile=testOutput.pcap

tcprewrite --pnat=192.168.0.1:192.168.1.1 --infile=test.pcap --outfile=testOutput.pcap
```

### tcpreplay(1) - Replay network traffic stored in pcap files

```bash
tcpreplay --loop=1 --pps=300 --cachefile=test.cache --intf1=eth0 --intf2=eth1 testOutput.pcap
tcpreplay --loop=1 --multiplier=1 --timer=gtod -2 --intf1=eth0 --intf2=eth1 test.pcap

tcpreplay-edit --pnat=192.168.0.1:192.168.1.1,192.168.0.2:192.168.1.2 -i eth1 test.pcap
```

## [tcpping](https://neoctobers.readthedocs.io/en/latest/linux/tcpping_on_ubuntu.html)

```bash
cd /usr/bin/; wget https://pingpros.com/pub/tcpping; chmod 755 tcpping; cd -

tcpping v1.7 Richard van den Berg <richard@vdberg.org>
Usage: tcpping [-d] [-c] [-C] [-w sec] [-q num] [-x count] ipaddress [port]
        -d   print timestamp before every result
        -c   print a columned result line
        -C   print in the same format as fping's -C option
        -w   wait time in seconds (defaults to 3)
        -r   repeat every n seconds (defaults to 1)
        -x   repeat n times (defaults to unlimited)
See also: man tcptraceroute
```

## telnet(1) - user interface to the TELNET protocol

```bash
apt install telnet-ssl -y
```

```bash
telnet fe80::d8ed:ef53:e0d3:336%eth0
telnet -b <src ip> <dst ip>
```

## timedatectl(1) - Control the system time and date

```bash
timedatectl set-timezone 'Asia/Taipei'
timedatectl set-timezone UTC
timedatectl set-time "00:00:00"
```

## timeout(1) - run a command with a time limit

```bash
timeout --preserve-status -s 9 -k 3 3 ping 8.8.8.8
```

```text
--kill-after=DURATION
--signal=SIGNAL
```

## top(1) - display Linux processes

## tr(1) - translate or delete characters

```bash
tr -d '\015'
tr -cd '\11\12\40-\176'
tr -cd "[:print:]\t\r\n"
tr -cd "[:print:]\f\v\t\r\n"
tr -d "\n"
```

- reverse a list of words

```bash
echo "1 2 3 4 5" | tr ' ' '\n' | tac | tr '\n' ' '; echo
```

- Upper Case and Lower Case Translate

```bash
echo "The" | tr 'a-z' 'A-Z'
echo "The" | tr 'A-Z' 'a-z'
```

## ulimit(3) - get and set user limits

```bash
ulimit -a

kill -ABRT <pid>
kill -SEGV <pid>
```

## uniq(1) - report or omit repeated lines

## vmstat(8) - Report virtual memory statistics

## wget(1) - The non-interactive network downloader

```bash
wget -qO- v4.ifconfig.co
wget -qO- v6.ifconfig.co
wget -qO- icanhazip.com
```

```bash
wget --spider -S http://192.168.0.1 | awk '/^  HTTP/{print $2}'
wget --spider -S http://192.168.0.1 --http-user=root --http-password=password 2>&1 | awk '/^  HTTP/{print $2}'
```

```bash
wget -e use_proxy=yes -e http_proxy=http://192.168.0.1:3128 http://askubuntu.com
```

```bash
wget --user-agent="User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.246" -qO- http://httpbin.org

wget --user-agent="User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_1; en-US) \
AppleWebKit/532.0 (KHTML, like Gecko) Chrome/4.0.209.0 Safari/532.0" -qO- http://httpbin.org
```

```bash
wget -r -np -R "index.html*" http://192.168.0.1/download/ -P /tmp -o /dev/null
```

## xxd(1) - make a hexdump or do the reverse

## yes(1) - output a string repeatedly until killed

- [Minimal code CPU stress-tester…](https://codegolf.stackexchange.com/questions/21191/minimal-code-cpu-stress-tester)

```bash
yes :|sh&sleep 10;kill $!
yes > /dev/null & yes > /dev/null & yes > /dev/null & yes > /dev/null & sleep 10; killall yes
```

- [How to generate a memory shortage using bash script](https://stackoverflow.com/questions/20200982/how-to-generate-a-memory-shortage-using-bash-script)

```bash
yes | tr \\n x | head -c $((20*1024*1024)) | grep n & sleep 1
```

## zip(1) - package and compress (archive) files

```bash
zip <FileName.zip> <DirName>
unzip <FileName.zip>
```

```bash
zip -e -r <FileName.zip> <DirName>

Enter password:
Verify password:
```
