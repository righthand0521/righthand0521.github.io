# [squid(8) - proxy caching server](https://linux.die.net/man/8/squid)

```bash
apt install squid -y
apt install squid-openssl -y
apt install squidclient -y

squid -v

service --status-all
update-rc.d squid enable
service squid start
service squid restart
service squid stop
service squid reload
```

```bash
curl -s --proxy-insecure -x http://192.168.0.1:3128 -k https://tools.ietf.org/html/rfc1 -o /dev/null
curl -s --proxy-insecure -x http://admin:password@192.168.0.1:3128 -k https://tools.ietf.org/html/rfc1 -o /dev/null
curl -s --proxy-insecure -x https://192.168.0.1:3129 -k https://tools.ietf.org/html/rfc1 -o /dev/null
curl -s --proxy-insecure -x https://admin:password@192.168.0.1:3129 -k https://tools.ietf.org/html/rfc1 -o /dev/null

cat /var/log/squid/access.log
cat /var/log/squid/cache.log
```

## /etc/squid/squid.conf

```bash
grep -vnE '^$|^#' /etc/squid/squid.conf

squid -k parse
```

### Adding a new user and password for configure Proxy Authentication

```bash
touch /etc/squid/passwd
chown proxy: /etc/squid/passwd
ls -l /etc/squid/passwd
cat /etc/squid/passwd
htpasswd -D /etc/squid/passwd <user name>
htpasswd /etc/squid/passwd admin
cat /etc/squid/passwd

ls -l /usr/lib/squid/security_file_certgen
ls -l /usr/lib/squid/basic_ncsa_auth

# vim /etc/squid/squid.conf
auth_param basic program /usr/lib/squid/basic_ncsa_auth /etc/squid/passwd
auth_param basic children 5
auth_param basic realm Squid Basic Authentication
auth_param basic credentialsttl 2 hours
acl auth_users proxy_auth REQUIRED
http_access allow auth_users
```

## make build

```bash
apt update
apt install build-essential openssl libssl-dev pkg-config -y
mkdir /downloads
cd /downloads
wget http://www.squid-cache.org/Versions/v4/squid-4.5.tar.gz
tar -zxvf squid-4.5.tar.gz
cd squid-4.5
./configure --with-default-user=proxy --with-openssl --enable-ssl-crtd
make
make install
```

## [Squid 4.13 Repo for Ubuntu 18](https://github.com/diladele/squid-ubuntu)

```bash
wget -qO - http://packages.diladele.com/diladele_pub.asc | sudo apt-key add -
echo "deb http://squid413.diladele.com/ubuntu/ bionic main" > /etc/apt/sources.list.d/squid413.diladele.com.list
apt update
apt install squid-common -y
apt install squid -y
apt install squidclient -y
```
