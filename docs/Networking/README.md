Networking
===
### [MAC Vendor List](https://gist.github.com/aallan/b4bb86db86079509e6159810ae9bd3e4)
---
### dibbler
```
# apt install dibbler-server dibbler-client -y
# mkdir /var/lib/dibbler
```
```
# vim /etc/dibbler/server.conf

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
---
### radvd
```
# apt install radvd -y
# /etc/init.d/radvd start
# /etc/init.d/radvd stop
# /etc/init.d/radvd restart
```
```
# vim /etc/sysctl.conf

net.ipv6.conf.all.forwarding=1

# sysctl -p
```
```
# vim /etc/rc.local

# Enable RADVD
```
```
# vim /etc/radvd.conf

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
---
### [NET-SNMP](http://www.net-snmp.org/)
```
# apt install snmp snmpd snmptrapd libsnmp-base libsnmp-dev snmp-mibs-downloader -y
```
```
# snmpget -v2c -c$community -On $ip $oid
# snmpwalk -v2c -c$community -On -CptT $ip $oid
```
### snmpd
```
# service --status-all
# update-rc.d snmpd enable
# service snmpd status
# service snmpd start
# service snmpd restart
```
```
# net-snmp-config --snmpconfpath
# snmpd -c /etc/snmp/snmpd.conf
# snmpd -f -Le -d -c /etc/snmp/snmpd.conf
```
```
# vim /etc/snmp/snmpd.conf

# Other Configuration
# override [-rw] OID TYPE VALUE
override .1.3.6.1.2.1.1.1.0 octet_str "Hello, world."
```
### [snmptrapd](https://blog.jangmt.com/2016/03/snmpd-trap-ups.html)
```
# net-snmp-config --default-mibdirs
# killall -e snmptrapd
# snmptrapd
# netstat -antulp | grep snmp
# tail -f /var/log/syslog
```
```
# vim /etc/snmp/snmptrapd.conf

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
```
# vim /etc/snmp/traps.sh

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
```
send snmptrap test to 192.168.0.1

# snmptrap -v2c -cpublic 192.168.0.1 "" SNMPv2-MIB::coldStart SNMPv2-MIB::coldStart s "test coldStart"
# snmptrap -v2c -cpublic 192.168.0.1 "" 1.3.6.1.2.1.1.1.0 1.3.6.1.2.1.1.1.0 s ''
# snmptrap -v1 -cpublic 192.168.0.1 "" localhost 3 0 ''
# snmptrap -v1 -cpublic 192.168.0.1 NET-SNMP-EXAMPLES-MIB::netSnmpExampleHeartbeatNotification "" 6 17 "" netSnmpExampleHeartbeatRate i 123456
```
### mib2c
```
# apt install build-essential libperl-dev libsnmp-dev -y

# cd net-snmp-5.7.3
# ./configure --prefix=/usr/local/net-snmp
# make
# make install

# ls -l /usr/local/net-snmp/share/snmp/mibs

# export MIBS=+<fileName>-MIB
# /usr/local/net-snmp/bin/snmptranslate -Tp -IR <ModuleName>
# mib2c -c mib2c.scalar.conf <ModuleName>
# mib2c -c mib2c.iterate.conf <ModuleName>
```
### php-snmp
```
# apt install php-snmp
# grep -rn "extension=php_snmp.dll" `locate php.ini`
# grep -rn "display_errors" `locate php.ini`
# service apache2 restart
```
---
### [lldpd](https://github.com/lldpd/lldpd)
```
# apt install lldpd -y
# service --status-all
# update-rc.d lldpd enable
# service lldpd status
# service lldpd start
# service lldpd restart

# vim /etc/lldpd.d/README.conf
configure system hostname 'Hello, hostname.'
configure system description 'Hello, description.'
```
### [lldpcli](http://manpages.ubuntu.com/manpages/trusty/man8/lldpcli.8.html)
```
# lldpcli show neighbors
# lldpcli show chassis
# lldpcli show configuration
# lldpcli show running-configuration
```
---
### upnpc(1) - miniupnpc library test client
```
# apt install miniupnpc

Add/Delete Port Mapping
# upnpc -a ip port external_port tcp | udp
# upnpc -d external_port tcp | udp

List Port Mapping and Status
# upnpc -l
# upnpc -s

External IP address
# upnpc -e

Initialize device list
# upnpc -i

Map these ports to this host
# upnpc -r port1 tcp | udp
```
#### [MiniUPnP Project HomePage](http://miniupnp.free.fr/)
#### [Use upnpc Mapping to External Network](http://blog.chinaunix.net/uid-20648944-id-3134810.html)
#### [Reference Manual: upnpc - interact with an external UPnP Internet Gateway Device](http://v2.nat32.com/upnpc.htm)
---
### [Mosquitto](https://oranwind.org/-edge-zai-ubuntu-an-zhuang-mosquitto-mqtt-broker-part-2/)
```
1. Install Mosquitto MQTT Broker
# apt install mosquitto -y
# service --status-all
# update-rc.d mosquitto enable
# systemctl enable mosquitto

2. Install Mosquitto Client
# apt install -y mosquitto-clients

3. Mosquitto MQTT Broker Test
Publisher --"hello world"--> Broker(192.168.0.1; /root/Downloads) --"hello world"--> Subscriber

Subscriber 向 Mosquitto MQTT Broker 訂閱 /root/Downloads 的 Topic
# mosquitto_sub -h 192.168.0.1 -t /root/Downloads

Publisher 產生 Topic 為 /root/Downloads 的 "hello world" 訊息
# mosquitto_pub -h 192.168.0.1 -t /root/Downloads -m "hello world"
```
---
