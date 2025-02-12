### Local
# docker build --tag squid .
# docker build --tag squid -f Dockerfile .
# docker run --network host --rm -it squid
# docker run --network host --rm -it squid <http|httpAuth|https|httpsAuth>
#
### Docker Hub
# docker build --tag righthand0521/squid .
# docker build --tag righthand0521/squid -f Dockerfile .
# docker push righthand0521/squid:latest
# docker run --network host --rm -it righthand0521/squid
# docker run --network host --rm -it righthand0521/squid <http|httpAuth|https|httpsAuth>
#
### tar
# docker images squid
# docker save squid > squid.tgz
# docker load < squid.tgz


###
# FROM ubuntu:22.04
FROM ubuntu:24.04

###
LABEL authors="Yu-Chuan Cheng"
LABEL version="1.0.1"
LABEL description="This is testing usage Squid Cache. The network environment is inherited host settings."

###
RUN apt update -y
RUN apt install net-tools -y
RUN apt install wget curl -y
RUN apt install vim -y

###
# Squid Cache: Version 5.2
# Squid Cache: Version 6.1
###
RUN apt install squid -y
RUN apt install squid-openssl -y
RUN apt install squidclient -y
#
COPY squid52.tgz /
RUN tar -zxvf squid52.tgz -C /
RUN rm squid52.tgz
#
COPY run.sh /usr/local/sbin/run
RUN chmod 755 /usr/local/sbin/run

###
RUN ln -sf /bin/bash /bin/sh

###
WORKDIR /
# ENTRYPOINT ["bash"]
ENTRYPOINT ["run"]
