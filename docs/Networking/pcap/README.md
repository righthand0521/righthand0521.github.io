pcap
===
### tcpdump(8) - dump traffic on a network
```
# tcpdump -C 100 -nnvvXSs 1514 -w `uname -n`_`date +"%Y%m%d%H%M%S"`.pcap
# tcpdump -G 86400 -nnvvXSs 1514 -w %Y%m%d%H%M%S.pcap

# tcpdump -r file.pcap
# tcpdump -xXr file.pcap | awk '{print $10}'

Split Pcap Size
# tcpdump -r <pcap file> -w <output pcap file> -C <Per Pcap Size>

# tcpdump -nn ether host aa:bb:cc:11:22:33
# tcpdump -nn src host 192.168.0.1
# tcpdump -nn not port 23
# tcpdump -nn udp and port 5353 and 5354
# tcpdump -nn net not 192.168.0.0/24

ARP
# tcpdump -nni eth0 arp
ICMP
# tcpdump -nni eth0 icmp
RIPv2
# tcpdump -i eth0 -v -s0 udp and port 520
RIPng
# tcpdump -i eth0 -v -s0 udp and port 521
DHCP
# tcpdump -i eth0 port 67 or port 68 -e -n
DHCPv6
# tcpdump -i eth0 port 546 or port 547 -e -n
LLDP
# tcpdump -i eth0 ether proto 0x88cc
```
---
### [Tcpreplay](https://tcpreplay.appneta.com/)
### [tcpreplay(1) - Replay network traffic stored in pcap files](https://linux.die.net/man/1/tcpreplay)
### [tcpprep(1) - Create a tcpreplay cache cache file from a pcap file.](https://linux.die.net/man/1/tcpprep)
### [tcprewrite(1) - Rewrite the packets in a pcap file.](https://linux.die.net/man/1/tcprewrite)
```
# apt install tcpreplay -y

Install - tcpreplay version: 4.3.1 (build git:v4.3.1)
# apt install build-essential libpcap-dev -y
# wget https://github.com/appneta/tcpreplay/releases/download/v4.3.1/tcpreplay-4.3.1.tar.xz
# tar -xJf tcpreplay-4.3.1.tar.xz
# cd tcpreplay-4.3.1
# ./configure
# make
# make install
# ln -s /usr/local/bin/tcpreplay
# ln -s /usr/local/bin/tcpprep
# ln -s /usr/local/bin/tcprewrite"
```
```
# tcpreplay --loop=1 --multiplier=1 --timer=gtod -2 --intf1=eth0 --intf2=eth1 test.pcap
```
```
# tcpprep --auto=client --pcap=test.pcap --cachefile=test.cache
# tcprewrite --enet-dmac=00:00:00:11:11:11,00:00:00:11:11:12 --enet-smac=ff:ff:ff:11:11:11,ff:ff:ff:11:11:12 --endpoints=192.168.0.1:192.168.1.1 --cachefile=test.cache --infile=test.pcap --outfile=testOutput.pcap
# tcpreplay --loop=1 --pps=300 --cachefile=test.cache --intf1=eth0 --intf2=eth1 testOutput.pcap
```
---
### Wireshark
```
"C:\Program Files\Wireshark\Wireshark.exe" -h
"C:\Program Files\Wireshark\Wireshark.exe" -D
"C:\Program Files\Wireshark\Wireshark.exe" -i 2 -k -b filesize:51200 -w "<File Name>.pcap"

"C:\Program Files\Wireshark\mergecap.exe" -w <outfile> <infile1> <infile2>

"C:\Program Files\Wireshark\editcap.exe" -F pcap -c <packets per file> <infile> <outfile>
"C:\Program Files\Wireshark\editcap.exe" -F pcap -t <time adjustment> <infile> <outfile>
"C:\Program Files\Wireshark\editcap.exe" -F pcap -d <inDuplicateFile> <outDuplicateFile>
# find . -type f -name '*.pcap' -print0 | while IFS= read -r -d '' f; do editcap -F libpcap "$f" "${f%.pcapng}.pcap"; rm $f; done
```
---
### pcapfix(1) - repair pcap and pcapng files
```
# apt install pcapfix -y

pcapfix-1.1.0-win32: pcapfix.exe
```
---
