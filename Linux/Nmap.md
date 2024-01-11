# [nmap(1) - Network exploration tool and security / port scanner](https://nmap.org/)

```bash
nmap <IP>/<Mask> -n -sP | awk '/Nmap scan report for/ {printf $5} /MAC Address:/ {print " => "$0}'
nmap -A <IP> -d --max-rate 0.1 --max-parallelism 1 --packet-trace
nmap -sS -sU -PN -p 1-65535 -v <IP> --packet-trace
nmap -sU -p 1-65535 -v <IP> --packet-trace
```

## [Nmap Scripting Engine](https://nmap.org/book/man-nse.html)

- [Redpoint](https://github.com/digitalbond/Redpoint)

```bash
ls -l /usr/share/nmap/scripts

nmap --script-updatedb
```

```bash
ls -l /usr/share/nmap/nselib/data/usernames.list
ls -l /usr/share/nmap/nselib/data/passwords.list

nmap -p 23 --script telnet-brute \
--script-args userdb=/usr/share/nmap/nselib/data/usernames.list,passdb=/usr/share/nmap/nselib/data/passwords.list <IP>

nmap -p 21 --script ftp-brute \
--script-args userdb=/usr/share/nmap/nselib/data/usernames.list,passdb=/usr/share/nmap/nselib/data/passwords.list <IP>

nmap -p 80 --script http-brute <IP>

nmap -p 22 --script ssh2-enum-algos <IP> -sV
```

```bash
nmap --script smb-os-discovery.nse
nmap -p 102 --script s7-enumerate <IP> -sV
```

## [Install Nmap Version](https://nmap.org/dist)

```bash
nmap -V
apt-get purge --auto-remove nmap -y

wget https://nmap.org/dist/nmap-7.60.tgz
tar -zxvf nmap-7.60.tgz
cd nmap-7.60/
./configure
make
make install
cd /usr/bin; ln -s /usr/local/bin/nmap; cd -
```
