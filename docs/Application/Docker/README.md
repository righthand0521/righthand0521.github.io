[Docker](https://zh.wikipedia.org/wiki/Docker)
===
#### [Install Docker Engine on Ubuntu](https://docs.docker.com/engine/install/ubuntu/)
```
# apt install docker.io -y
# service --status-all
# update-rc.d docker enable
# service docker start
# service docker status
# ls -l /var/lib/docker/
```
```
# docker version
# docker info
# docker search
# docker pull
# docker images
# docker rmi
# docker ps -a
# docker stop $(docker ps -q)
# for i in $(docker ps -q -f status=exited); do docker rm -f $i; done
# docker run
```
---
### docker-compose.yml
```
# docker-compose version
# docker-compose up -d
# docker-compose down
# docker-compose ps
# docker-compose logs
```
---
### [Docker Hub](https://hub.docker.com/)
```
# docker login
```
---
### [bitnami/testlink](https://hub.docker.com/r/bitnami/testlink/)
### [bitnami-docker-testlink](https://github.com/bitnami/bitnami-docker-testlink)
```
# docker pull bitnami/testlink
# curl -sSL https://raw.githubusercontent.com/bitnami/bitnami-docker-testlink/master/docker-compose.yml > docker-compose.yml
# docker-compose up -d
# docker-compose ps
# docker-compose down
```
---
