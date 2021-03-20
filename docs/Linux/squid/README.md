Squid
===
### [squid(8) - proxy caching server](https://linux.die.net/man/8/squid)
```
# apt install squid -y
# service --status-all
# update-rc.d squid enable

# service squid start
# service squid restart
# service squid stop
# service squid reload

# squid -v
# squid -z

# vim /etc/squid/squid.conf
# cat /var/log/squid/access.log
# cat /var/log/squid/cache.log
```
### Adding a new user and password for configure Proxy Authentication
```
# touch /etc/squid/passwd
# chown proxy: /etc/squid/passwd
# ls -l /etc/squid/passwd
# cat /etc/squid/passwd
# htpasswd -D /etc/squid/passwd <user name>
# htpasswd /etc/squid/passwd admin
admin:$apr1$4WhoC/Of$6nAJXW0wpLjb6xMue2QR30    # admin:password
# cat /etc/squid/passwd

# grep -vnE '^$|^#' /etc/squid/squid.conf
# vim /etc/squid/squid.conf
auth_param basic program /usr/lib/squid/basic_ncsa_auth /etc/squid/passwd
auth_param basic children 5
auth_param basic realm Squid Basic Authentication
auth_param basic credentialsttl 2 hours
acl auth_users proxy_auth REQUIRED
http_access allow auth_users

# squid -k parse
```
### HTTPS Proxy
```
# vim /etc/squid/squid.conf

http_port 3128 ssl-bump cert=/etc/squid/squidCA.pem generate-host-certificates=on dynamic_cert_mem_cache_size=16MB
https_port 3129 cert=/etc/squid/squidCA.pem generate-host-certificates=on dynamic_cert_mem_cache_size=32MB
```
### Enable FTP on Squid Proxy
```
# vim /etc/squid/squid.conf

#  TAG: acl
acl SSL_ports port 443 21
#  TAG: always_direct
acl FTP proto FTP
always_direct allow FTP
```
### make build
```
# apt update
# apt install build-essential openssl libssl-dev pkg-config -y
# mkdir /downloads
# cd /downloads
# wget http://www.squid-cache.org/Versions/v4/squid-4.5.tar.gz
# tar -zxvf squid-4.5.tar.gz
# cd squid-4.5
# ./configure --with-default-user=proxy --with-openssl --enable-ssl-crtd
# make
# make install
```
### [Squid 4.13 Repo for Ubuntu 18](https://github.com/diladele/squid-ubuntu)
```
# wget -qO - http://packages.diladele.com/diladele_pub.asc | sudo apt-key add -
# echo "deb http://squid413.diladele.com/ubuntu/ bionic main" > /etc/apt/sources.list.d/squid413.diladele.com.list
# apt update
# apt install squid-common -y
# apt install squid -y
# apt install squidclient -y
```
### Verify
```
# curl -s --proxy-insecure -x http://192.168.0.1:3128 -k https://tools.ietf.org/html/rfc1 -o /dev/null
# curl -s --proxy-insecure -x http://admin:password@192.168.0.1:3128 -k https://tools.ietf.org/html/rfc1 -o /dev/null
# curl -s --proxy-insecure -x https://192.168.0.1:3129 -k https://tools.ietf.org/html/rfc1 -o /dev/null
# curl -s --proxy-insecure -x https://admin:password@192.168.0.1:3129 -k https://tools.ietf.org/html/rfc1 -o /dev/null

# tail -n1 /etc/squid/access.log
```
---
