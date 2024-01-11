# [iptables](https://zh.wikipedia.org/wiki/Iptables)

## iptables/ip6tables(8) — administration tool for IPv4/IPv6 packet filtering and NAT

```bash
lsmod | grep ip_tables
```

```bash
iptables -t filter -S
iptables -t nat -S
iptables -t mangle -S

iptables -t filter -F
iptables -t nat -F
iptables -t mangle -F

iptables -t filter -nL -v --line-number
iptables -t nat -nL -v --line-number
iptables -t mangle -nL -v --line-number
```

```bash
iptables-save > /etc/iptables_rules
/sbin/iptables-restore < /etc/iptables_rules
cat /etc/iptables_rules
```

<details><summary>Forwarding Network Traffic</summary>

```bash
cat /proc/sys/net/ipv4/ip_forward
echo 1 > /proc/sys/net/ipv4/ip_forward
```

```bash
sysctl -n net.ipv4.ip_forward
sysctl net.ipv4.ip_forward=1
```

```bash
# vim /etc/sysctl.conf

net.ipv4.ip_forward=1
```

</details>

<details><summary>Port Forwarding</summary>

```bash
iptables -t mangle -A PREROUTING -d 10.0.0.253 -p tcp --dport 10022 -j MARK --set-mark 10022 -i eth1
iptables -t nat -A PREROUTING -p tcp -m mark --mark 10022 -j DNAT --to-destination 192.168.0.1:22 -i eth1
iptables -t nat -A POSTROUTING -m mark --mark 10022 -j SNAT --to-source 192.168.0.253 -o eth0
iptables -A FORWARD -m mark --mark 10022 -j ACCEPT -o eth0
```

</details>

<details><summary>Forwarding Between Two Interface</summary>

```bash
iptables -A FORWARD -i eth1 -o eth0 -j ACCEPT
iptables -A FORWARD -i eth0 -o eth1 -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
```

</details>

## [iptables-vis – visualise iptables chains](https://github.com/Nudin/iptable_vis)

```bash
apt install python-blockdiag -y
```

```bash
iptables -v -L > iptables.txt
awk -f iptables-vis.awk < iptables.txt > iptables.dia
blockdiag iptables.dia -T svg -o iptables.svg
```
