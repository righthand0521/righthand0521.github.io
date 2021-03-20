[Grafana](https://grafana.com/)
===
### Grafana
#### [How To Install and Secure Grafana on Ubuntu 18.04](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-grafana-on-ubuntu-18-04)
```
# wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
# add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
# apt update
# apt-cache policy grafana
# apt install grafana
# systemctl start grafana-server
# systemctl status grafana-server
# systemctl enable grafana-server
```
```
# vim /etc/grafana/grafana.ini
```
```
http://<IP Address>:3000
init id: admin
init pw: admin
```
---
### InfluxDB
#### [How to Install TIG Stack (Telegraf, InfluxDB, and Grafana) on Ubuntu 18.04 LTS](https://www.howtoforge.com/tutorial/how-to-install-tig-stack-telegraf-influxdb-and-grafana-on-ubuntu-1804/)
```
Install InfluxDB

# curl -sL https://repos.influxdata.com/influxdb.key | sudo apt-key add -
# source /etc/lsb-release
# echo "deb https://repos.influxdata.com/${DISTRIB_ID,,} ${DISTRIB_CODENAME} stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
# apt update
# apt install influxdb -y

# systemctl start influxdb
# systemctl enable influxdb
# netstat -plntu | grep influxd
# netstat -plntu | grep 8086
```
```
Create InfluxDB Database and User

# influx
> create database test
> create user admin with password 'password'
> show databases
> show users

# influx -precision rfc3339 -execute "SHOW DATABASES"
# influx -database TMP03YY0000206 -execute "SHOW MEASUREMENTS"
# influx -database TMP03YY0000206 -execute "SHOW SERIES"

http://localhost:8086/
# curl -s -XPOST localhost:8086/query -d "q=CREATE DATABASE test"
# curl -s -i -XPOST localhost:8086/write?db=test --data-binary @test.txt
```
---
