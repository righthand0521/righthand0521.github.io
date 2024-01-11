# [mosquitto](https://oranwind.org/-edge-zai-ubuntu-an-zhuang-mosquitto-mqtt-broker-part-2/)

## Install Mosquitto MQTT Broker

```bash
apt install mosquitto -y

service --status-all
update-rc.d mosquitto enable
systemctl enable mosquitto
```

## Install Mosquitto Client

```bash
apt install mosquitto-clients -y
```

## Mosquitto MQTT Broker Test

```text
+-----------+                   +--------------------------------------+                   +------------+
| Publisher | --"hello world"-> | Broker(192.168.0.1; /root/Downloads) | --"hello world"-> | Subscriber |
+-----------+                   +--------------------------------------+                   +------------+
```

- Subscriber 向 Mosquitto MQTT Broker 訂閱 /root/Downloads 的 Topic

```bash
mosquitto_sub -h 192.168.0.1 -t /root/Downloads
```

- Publisher 產生 Topic 為 /root/Downloads 的 "hello world" 訊息

```bash
mosquitto_pub -h 192.168.0.1 -t /root/Downloads -m "hello world"
```
