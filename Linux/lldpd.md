# [lldpd](https://github.com/lldpd/lldpd)

```bash
apt install lldpd -y

service --status-all
update-rc.d lldpd enable

service lldpd status
service lldpd start
service lldpd restart
```

```bash
# vim /etc/lldpd.d/README.conf

configure system hostname 'Hello, hostname.'
configure system description 'Hello, description.'
```

## [lldpcli](http://manpages.ubuntu.com/manpages/trusty/man8/lldpcli.8.html)

```bash
lldpcli show neighbors
lldpcli show chassis
lldpcli show configuration
lldpcli show running-configuration
```
