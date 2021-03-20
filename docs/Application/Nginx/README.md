[Nginx](https://www.nginx.com/)
===
### [How to install fcgiwrap for Nginx on Ubuntu 20.04](https://www.cyberciti.biz/faq/how-to-install-fcgiwrap-for-nginx-on-ubuntu-20-04/)
```
# apt install fcgiwrap -y
```
```
# fcgiwrap -h
# systemctl enable fcgiwrap
# systemctl start fcgiwrap
# systemctl status fcgiwrap
# ls -l /var/run/fcgiwrap.socket
# cp /usr/share/doc/fcgiwrap/examples/nginx.conf /etc/nginx/fcgiwrap.conf
```
```
# vim /etc/nginx/sites-enabled/default

# Trun on /cgi-bin/ support to run CGI apps ##
include /etc/nginx/fcgiwrap.conf;
```
```
# nginx -t
# nginx -s reload
```
```
# mkdir -vp /usr/lib/cgi-bin/
```
```
# vim /usr/lib/cgi-bin/test.cgi

#!/bin/bash

echo -ne 'Status: 200\r\n'
echo -ne 'Content-Type: text/plain\r\n'
echo -ne '\r\n'

echo -e "${LINENO}: ${QUERY_STRING}"

exit 0
```
```
# chmod +x -v /usr/lib/cgi-bin/test.cgi
```
---
