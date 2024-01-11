# [NET-SNMP](http://www.net-snmp.org/)

```bash
apt install snmp snmpd snmptrapd -y
apt install snmp-mibs-downloader -y
apt install libsnmp-base libsnmp-perl -y
apt install build-essential libperl-dev libsnmp-dev -y
```

```bash
snmpget -v2c -c <Community> -On <IP> <OID>
snmpwalk -v2c -c <Community> -On -CptT <IP> <OID>
snmpwalk -v3 -l noAuthNoPriv -u <User> <IP> <OID>
```

## snmpd

```bash
service --status-all
update-rc.d snmpd enable
service snmpd status
service snmpd start
service snmpd restart
```

```bash
net-snmp-config --snmpconfpath

snmpd -c /etc/snmp/snmpd.conf
snmpd -f -Le -d -c /etc/snmp/snmpd.conf
```

- vim /etc/snmp/snmpd.conf

```bash
# agentaddress  127.0.0.1,[::1]
agentAddress  udp:0.0.0.0:161

# Other Configuration
# override [-rw] OID TYPE VALUE
override .1.3.6.1.2.1.1.1.0 octet_str "Hello, world."
```

## [snmptrapd](https://blog.jangmt.com/2016/03/snmpd-trap-ups.html)

```bash
net-snmp-config --default-mibdirs
killall -e snmptrapd
snmptrapd
netstat -antulp | grep snmp
tail -f /var/log/syslog
```

- vim /etc/snmp/snmptrapd.conf

```bash
# 以 SNMP v2c 版本, 通訊接收寫入的密碼是 public
# SNMP v2c with community as public
authCommunity   log,execute,net public

# 底下這兩個 traphandle 是很常見的範例, 以 SNMPv2-MIB::coldStart 這個 MIB
# 來觸發後面的 command 動作 /etc/snmp/traps.sh cold
# traphandle SNMPv2-MIB::coldStart    /etc/snmp/traps.sh cold
# traphandle SNMPv2-MIB::warmStart    /etc/snmp/traps.sh warmStart

# 預設的觸發,可以在 traps.sh 產生的 traps.txt 看到紀錄
# 也可以從 /var/log/syslog(ubunut) or /var/log/message(centos) 看到紀錄
# traphandle default  /etc/snmp/traps.sh default

# 這個是 MEGATEC 測試後的 AC 斷電、復電的 MIB 值
# for UPSagent HDP801 (MEGATEC)
traphandle SNMPv2-SMI::mib-2.33.1.6.3.6     /etc/snmp/traps.sh HDP_AC_lost
traphandle SNMPv2-SMI::mib-2.33.1.6.3.2     /etc/snmp/traps.sh HDP_AC_restore

# 關於 MIB 會因為不同的 UPS 裝置送出的 MIB 值都不一樣, 實際請參考你的 UPS MIB 相對應的值
# 底下備註是不同 UPS 在實際斷電時, snmptrapd 接收到的 MIB LOG
```

- vim /etc/snmp/traps.sh

```bash
#!/bin/bash
# --------------------------------------------
# ref:http://www.net-snmp.org/wiki/index.php/TUT:Configuring_snmptrapd
# --------------------------------------------
logfile='/etc/snmp/traps.txt'

read host
read ip
vars=

while read oid val
do
    if [ "$vars" = "" ]
    then
        vars="$oid = $val"
    else
        vars="$vars, $oid = $val"
    fi
done
echo "trap: $1 $host $ip $vars" > $logfile

# ---------------------------------------------
# by mtchang 2016.3.17
# ---------------------------------------------
actionfile='/etc/snmp/action.txt'
ACstat=$(tail -n1 $logfile | cut -d: -f2 | cut -d" " -f2)

# log to debug
echo "$ACstat $(whoami) $(date)"
echo "$ACstat $(whoami) $(date)" > $actionfile

if [[ "${ACstat}" == "HDP_AC_restore" ]]; then
    echo "shutdown -c 'Utility power has been restore'" >> $actionfile
    #echo "shutdown -c 'Utility power has been restore'" | bash
    #echo "ssh mtchang@192.168.1.181 'sudo /home/mtchang/cmd/snmptrapd_cancel_poweroff.sh'" | bash
    exit 0
elif [[ "${ACstat}" == "HDP_AC_lost" ]]; then
    echo "shutdown -h -P 3 'After 3 minutes will be Poweroff. The UPS is not on battery power'" >> $actionfile
    #echo "shutdown -h -P 3 'After 3 minutes will be Poweroff. The UPS is not on battery power'" | bash
    #echo "ssh mtchang@192.168.1.181 'sudo /home/mtchang/cmd/snmptrapd_poweroff.sh' &" | bash
    exit 0
else
    echo "ACstat=${ACstat},Nothing to do." >> $actionfile
    exit 1
fi
```

### send snmptrap test to 192.168.0.1

```bash
snmptrap -v2c -cpublic 192.168.0.1 "" SNMPv2-MIB::coldStart SNMPv2-MIB::coldStart s "test coldStart"
snmptrap -v2c -cpublic 192.168.0.1 "" 1.3.6.1.2.1.1.1.0 1.3.6.1.2.1.1.1.0 s ''
snmptrap -v1 -cpublic 192.168.0.1 "" localhost 3 0 ''
snmptrap -v1 -cpublic 192.168.0.1 NET-SNMP-EXAMPLES-MIB::netSnmpExampleHeartbeatNotification
"" 6 17 "" netSnmpExampleHeartbeatRate i 123456
```

## mib2c

```bash
cd net-snmp-5.7.3
./configure --prefix=/usr/local/net-snmp
make
make install
ls -l /usr/local/net-snmp/share/snmp/mibs
export MIBS=+<fileName>-MIB
/usr/local/net-snmp/bin/snmptranslate -Tp -IR <ModuleName>
mib2c -c mib2c.scalar.conf <ModuleName>
mib2c -c mib2c.iterate.conf <ModuleName>
```

## net-snmp agent

- [net-snmp subagent development](https://www.programmersought.com/article/82972405466/)
- [net-snmp agent開發詳解](https://www.itread01.com/content/1547576287.html)
- [net-snmp添加自定義MIB](https://www.zendei.com/article/6043.html)
- [How to create statically linked net-snmp binaries](https://sourceforge.net/p/net-snmp/mailman/message/19058995/)

```bash
# vim /etc/snmp/snmp.conf
view   systemonly  included   .1

# snmpget -cpublic -v2c 127.0.0.1 1.3.6.1.4.1.16535.1.1.0

# cp Test-MIB.my /usr/share/snmp/mibs
# env MIBS="/usr/share/snmp/mibs/Test-MIB.my" mib2c -c mib2c.scalar.conf Test
```

### Subagent Extend

將生成的Test.c和Test.h文件編譯成可執行程式, 運行該程式和snmpd.
優點是操作簡單; 缺點是需要運行兩個程式才行.

```bash
# net-snmp-config
# net-snmp-config --compile-subagent Test Test.c
    generating the temporary code file: netsnmptmp.10386.c
    void init_Test(void);
    checking for init_Test in Test.c
    init_Test(void)
    checking for shutdown_Test in Test.c
    running: gcc  -g -O2 -fdebug-prefix-map=/build/net-snmp-RoWDVF/net-snmp-5.8+dfsg=. -fstack-protector-strong
    -Wformat -Werror=format-security -DNETSNMP_USE_INLINE -DNETSNMP_ENABLE_IPV6 -fno-strict-aliasing
    -DNETSNMP_REMOVE_U64 -g -O2 -fdebug-prefix-map=/build/net-snmp-RoWDVF/net-snmp-5.8+dfsg=. -fstack-protector-strong
    -Wformat  -DNETSNMP_USE_INLINE -Ulinux -Dlinux=linux  -D_REENTRANT -D_GNU_SOURCE -DDEBIAN
    -fwrapv -fno-strict-aliasing -pipe -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
    -I/usr/lib/x86_64-linux-gnu/perl/5.30/CORE   -I. -I/usr/include -o Test netsnmptmp.10386.c  Test.c
    -Wl,-Bsymbolic-functions -Wl,-z,relro -Wl,-z,now -L/usr/lib/x86_64-linux-gnu -lnetsnmpmibs
    -lnetsnmpagent -lnetsnmp -lnetsnmpmibs -lsensors -lpci -ldl  -lnetsnmpagent  -lwrap -Wl,-E -lnetsnmp  -lcrypto
    netsnmptmp.10386.c: In function ‘main’:
    netsnmptmp.10386.c:239:9: warning: ignoring return value of ‘write’,
    declared with attribute warn_unused_result [-Wunused-result]
      239 |         write(fd, buf, len);
          |         ^~~~~~~~~~~~~~~~~~~
    removing the temporary code file: netsnmptmp.10386.c
    subagent program Test created
# /usr/local/snmpd -c /usr/local/snmp/etc/snmpd.conf
# ./Test
```

### Static Build

將生成的Test.c和Test.h文件加入到相應的位置(<net-snmp src>/agent/mibgroups), 重新編譯snmp.
優點是不需要修改配置文件; 缺點是每次添加都得重新編譯.

```bash
# ./configure --enable-mini-agent \
    --with-default-snmp-version=3 \
    --with-sys-contact="aa@bb.com" \
    --with-sys-location=Home \
    --with-logfile=/var/log/snmpd.log \
    --with-persistent-directory=/var/net-snmp \
    --disable-shared \
    --enable-static \
    --disable-applications \
    --without-rpm \
    --without-dmalloc \
    --without-efence \
    --without-rsaref \
    --enable-mini-agent \
    --with-defaults \
    --prefix=/usr/local/snmp \
    --sysconfdir=/etc \
    --disable-manuals \
    --disable-debugging \
    --disable-scripts \
    --disable-mibs \
    --disable-mib-loading \
    --with-mib-modules=Test \
    --with-ldflags=-Bstatic
# make
# make install
```

### Dynamic Load

將生成的 Test.c 和 Test.h 編譯成 .so, 修改snmpd.conf.
優點是每次添加不需要重新編譯; 缺點是必須支持dlmod命令.

```bash
# vim Makefile
CC=gcc
FLAGS=-I. `net-snmp-config --cflags` -g
DLFLAGS=-shared -fPIC -g

Test.so: Test.c
    $(CC) $(CFLAGS) $(DLFLAGS) -c -o Test.o Test.c
    $(CC) $(CFLAGS) $(DLFLAGS) -o Test.so Test.o

.PHONY : clean
clean :
    rm -f *.so *.o

# vim /etc/snmp/snmp.conf
dlmod Test <Test.so Absolute path>/Test.so

# /usr/local/snmpd -f -L -DTest,dlmod -c /usr/local/snmp/etc/snmpd.conf
```

## php-snmp

```bash
apt install php-snmp
grep -rn "extension=php_snmp.dll" `locate php.ini`
grep -rn "display_errors" `locate php.ini`
service apache2 restart
```
