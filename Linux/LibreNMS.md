# [LibreNMS](https://www.librenms.org/)

- [開源網路裝置服務監控系統：LibreNMS (一)](https://ithelp.ithome.com.tw/articles/10224076)
- [CentOS7 / Ubuntu 20.04 安裝 LibreNMS 程序](https://www.ichiayi.com/tech/librenms)
- [Installing LibreNMS (HowTo)](https://nsrc.org/activities/agendas/en/nmm-3-days/netmgmt/en/librenms/librenms-install.html)

## 1. 安裝所須套件

```bash
apt install software-properties-common
add-apt-repository universe
apt update
```

```bash
apt install python3-memcache python3-mysqldb -y
apt install composer -y
apt install curl -y
apt install fping -y
apt install git -y
apt install graphviz -y
apt install imagemagick -y
apt install mtr-tiny -y
apt install nmap -y
apt install rrdtool -y
apt install snmp snmpd -y
apt install whois -y
apt install acl -y
apt install nginx-full -y
```

### [MariaDB](https://mariadb.com/docs/)

```bash
cd /opt
wget https://downloads.mariadb.com/MariaDB/mariadb_repo_setup

echo "fc84b8954141ed3c59ac7a1adfc8051c93171bae7ba34d7f9aeecd3b148f1527 mariadb_repo_setup" | sha256sum -c -
chmod +x mariadb_repo_setup
./mariadb_repo_setup --mariadb-server-version="mariadb-10.5"

apt update
apt install mariadb-server -y
apt install mariadb-client -y
mysql -V
```

```bash
apt install mariadb-client mariadb-server -y
```

### [How To Install PHP 7.4 on Ubuntu 20.04/18.04/16.04](https://computingforgeeks.com/how-to-install-php-on-ubuntu/)

```bash
apt update

apt install software-properties-common -y
add-apt-repository ppa:ondrej/php
apt update

apt install php7.4 -y
php -v

apt install php7.4-cli php7.4-curl php7.4-fpm php7.4-gd php7.4-json php7.4-mbstring php7.4-mysql php7.4-snmp php7.4-xml php7.4-zip -y
```

## 2. 安裝與設定 LibreNMS

```bash
useradd librenms -d /opt/librenms -M -r
usermod -a -G librenms www-data

cd /opt
git clone https://github.com/librenms/librenms.git
chown -R librenms:librenms /opt/librenms
chmod 770 -R /opt/librenms

setfacl -d -m g::rwx /opt/librenms/rrd /opt/librenms/logs /opt/librenms/bootstrap/cache/ /opt/librenms/storage/
setfacl -R -m g::rwx /opt/librenms/rrd /opt/librenms/logs /opt/librenms/bootstrap/cache/ /opt/librenms/storage/
```

## 3. 安裝 PHP 相關套件

```bash
su - librenms
./scripts/composer_wrapper.php install --no-dev
exit
```

## 4. 資料庫與帳號建立

```bash
service mysql start

mysql -uroot -p
>> password

>> CREATE DATABASE librenms CHARACTER SET utf8 COLLATE utf8_unicode_ci;
>> CREATE DATABASE librenms CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
>> CREATE USER 'librenms'@'localhost' IDENTIFIED BY 'password';
>> GRANT ALL PRIVILEGES ON librenms.* TO 'librenms'@'localhost';
>> FLUSH PRIVILEGES;

>> exit
```

## 5. 修改 MariaDB 設定檔

```bash
# vim /etc/mysql/mariadb.conf.d/50-server.cnf

[mysqld]
innodb_file_per_table=1
lower_case_table_names=0
```

```bash
service mysql restart

cat /etc/mysql/mariadb.conf.d/50-server.cnf
cat /etc/mysql/mysql.conf.d/mysqld.cnf
```

## 6. 設定 PHP

```bash
# vim /etc/php/7.4/fpm/php.ini

date.timezone = Asia/Taipei
```

```bash
service php7.4-fpm start
service php7.4-fpm restart

cat /etc/php/7.4/fpm/php.ini
```

## 7. 設定 Nginx

```bash
# vim /etc/nginx/conf.d/librenms.conf

server {
    listen 8000;
    listen [::]:8000;
    root /opt/librenms/html;
    index index.php;

    charset utf-8;
    gzip on;
    gzip_types text/css application/javascript text/javascript application/x-javascript image/svg+xml text/plain text/xsd text/xsl text/xml image/x-icon;
    location / {
        try_files $uri $uri/ /index.php?$query_string;
    }
    location /api/v0 {
        try_files $uri $uri/ /api_v0.php?$query_string;
    }
    location ~ \.php {
        include fastcgi.conf;
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
        fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
    }
    location ~ /\.ht {
        deny all;
    }
}
```

```bash
rm /etc/nginx/sites-enabled/default
service nginx start
service nginx restart

cat /etc/nginx/conf.d/librenms.conf
```

## 8. 設定 SNMP

```bash
cp /opt/librenms/snmpd.conf.example /etc/snmp/snmpd.conf
curl -o /usr/bin/distro https://raw.githubusercontent.com/librenms/librenms-agent/master/snmp/distro
chmod +x /usr/bin/distro

service snmpd start
service snmpd restart
```

## 9. 設定排程作業

```bash
cp /opt/librenms/librenms.nonroot.cron /etc/cron.d/librenms
cp /opt/librenms/misc/librenms.logrotate /etc/logrotate.d/librenms
```

## 10. 檔案權限調整

```bash
chown -R librenms:librenms /opt/librenms

setfacl -d -m g::rwx /opt/librenms/rrd /opt/librenms/logs /opt/librenms/bootstrap/cache/ /opt/librenms/storage/
setfacl -R -m g::rwx /opt/librenms/rrd /opt/librenms/logs /opt/librenms/bootstrap/cache/ /opt/librenms/storage/

setfacl -d -m g::rwx /opt/librenms/bootstrap/cache /opt/librenms/storage /opt/librenms/logs /opt/librenms/rrd
chmod -R ug=rwX /opt/librenms/bootstrap/cache /opt/librenms/storage /opt/librenms/logs /opt/librenms/rrd
```

## 11. http://<IP Address>/install.php

```bash
[Devices] -> [Add Device]
```
