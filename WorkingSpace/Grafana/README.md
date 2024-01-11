# [Grafana](https://grafana.com/)

- [Github](https://github.com/grafana/grafana)

## [How To Install and Secure Grafana on Ubuntu 18.04](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-grafana-on-ubuntu-18-04)

```bash
wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
apt update
apt-cache policy grafana
apt install grafana
systemctl start grafana-server
systemctl status grafana-server
systemctl enable grafana-server
```

```bash
vim /etc/grafana/grafana.ini
```

```bash
http://<IP Address>:3000
init id: admin
init pw: admin
```

## [How to Install TIG Stack (Telegraf, InfluxDB, and Grafana) on Ubuntu 18.04 LTS](https://www.howtoforge.com/tutorial/how-to-install-tig-stack-telegraf-influxdb-and-grafana-on-ubuntu-1804/)

### Install InfluxDB: <http://localhost:8086/>

```bash
curl -sL https://repos.influxdata.com/influxdb.key | sudo apt-key add -
source /etc/lsb-release
echo "deb https://repos.influxdata.com/${DISTRIB_ID,,} ${DISTRIB_CODENAME} stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
apt update
apt install influxdb -y

systemctl start influxdb
systemctl enable influxdb
netstat -plntu | grep influxd
netstat -plntu | grep 8086
```

### Create InfluxDB Database and User

```bash
# influx
> create database test
> create user admin with password 'password'
> show databases
> show users
```

### influxdb-client

```bash
apt install influxdb-client
```

```bash
influx -execute "SHOW DATABASES"
influx -precision rfc3339 -execute "SHOW DATABASES"
influx -format=json -execute "SHOW DATABASES"

curl -i -XPOST http://localhost:8086/query --data-urlencode "q=SHOW DATABASES"
```

```bash
influx -execute 'CREATE DATABASE TEST_DB'

curl -i -XPOST http://localhost:8086/query --data-urlencode "q=CREATE DATABASE TEST_DB"
```

```bash
influx -execute "DROP DATABASE TEST_DB"

curl -i -XPOST http://localhost:8086/query --data-urlencode "q=DROP DATABASE TEST_DB"
```

```bash
influx -database TEST_DB -execute "SHOW MEASUREMENTS"
influx -database TEST_DB -execute "DROP MEASUREMENT <>"

influx -database TEST_DB -execute "SHOW SERIES"
influx -database TEST_DB -execute "DROP SERIES FROM <>"
influx -database TEST_DB -execute "DROP SERIES FROM key2 WHERE key1='value1'"
```

```bash
curl -i -XPOST 'http://localhost:8086/write?db=TEST_DB' --data-binary 'test,key1=value1 key2=value2'
curl -i -XPOST 'http://localhost:8086/write?db=TEST_DB' --data-binary 'test,key1=value1 key3=value3'

echo "test,key1=value1 key2=value2" >> tmp.txt
echo "test,key1=value1 key3=value3" >> tmp.txt
curl -i -XPOST 'http://localhost:8086/write?db=TEST_DB' --data-binary @tmp.txt

influx -precision rfc3339 -database TEST_DB -execute "SELECT key2 FROM test WHERE key1='value1'"
influx -precision rfc3339 -database TEST_DB -execute "SELECT key3 FROM test WHERE key1='value1'"
```

## [docker-compose-influxdb-grafana](https://github.com/jkehres/docker-compose-influxdb-grafana)

```bash
apt install docker-compose
git clone https://github.com/jkehres/docker-compose-influxdb-grafana.git
docker-compose up -d
docker-compose down

docker-compose exec influxdb influx
> SHOW DATABASES
```

### Edit Notification channels

- vim docker-compose.yml

```bash
- GF_SERVER_ROOT_URL=http://<IP Address>:3000
- GF_SMTP_ENABLED=true
- GF_SMTP_HOST=smtp.gmail.com:587
- GF_SMTP_USER=<gmail account>
- GF_SMTP_PASSWORD=<gamil password>
```
