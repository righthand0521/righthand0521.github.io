﻿# [BIND 9](https://www.isc.org/bind/)

## Install

- apt install bind9 -y
- vim /etc/bind/named.conf.local

```bash
// ===================================================
// Add Domain Name as "dns.yc.org"
// ==================================================
zone "dns.yc.org" IN {
    type master;
    file "/etc/bind/db.dns.yc.org";
};
```

- vim /etc/bind/db.dns.yc.org

```bash
$TTL 600
$ORIGIN dns.yc.org.
@           IN  SOA     dns.yc.org. root.dns.yc.org. (
                        2023111100  3H  15M 1W  1D  )
            IN  NS      dns.yc.org.
dns.yc.org. IN  A       127.0.0.1

smb         IN  A       192.168.0.111
smb         IN  AAAA    fe80::fefc:48ff:fe20:111
```

- systemctl restart named

## Check

```bash
netstat -antup | grep 53
```

```bash
dig @127.0.0.1 -p 53 dns.yc.org
dig @127.0.0.1 -p 53 smb.dns.yc.org Any

dig @fe80::fefc:48ff:fe20:100%ens37 -p 53 smb.dns.yc.org Any
```

```bash
systemctl stop systemd-resolved
systemctl start systemd-resolved
```

## Reference

- [DNS 伺服器 bind9 的 zone file 設定](https://blueskyson.github.io/2021/05/24/bind9-setup/)
