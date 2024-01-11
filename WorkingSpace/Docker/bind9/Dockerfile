### Local
# docker build --tag bind9 .
# docker build --tag bind9 -f Dockerfile .
# docker run --network host --rm -it bind9
# docker run --network host --rm -it -v /root/bind:/tmp bind9
#
### Docker Hub
# docker build --tag righthand0521/bind9 .
# docker build --tag righthand0521/bind9 -f Dockerfile .
# docker push righthand0521/bind9:latest
# docker run --network host --rm -it righthand0521/bind9
# docker run --network host --rm -it -v /root/bind:/tmp righthand0521/bind9
#
### tar
# docker images bind9
# docker save bind9 > bind9.tgz
# docker load < bind9.tgz


###
FROM ubuntu:22.04

###
LABEL authors="Yu-Chuan Cheng"
LABEL version="1.0.0"
LABEL description="This is testing usage BIND DNS Server. The network environment is inherited host settings."

###
RUN apt update -y
RUN apt install net-tools -y
RUN apt install vim -y
RUN apt install systemctl -y

###
RUN apt install bind9 -y
RUN apt install dnsutils -y
#
COPY named.conf.local /etc/bind
COPY db.dns.yc.org /etc/bind

###
RUN ln -sf /bin/bash /bin/sh
# RUN sed -i -e 's|#force_color_prompt=yes|force_color_prompt=yes|' /root/.bashrc

###
COPY run.sh /usr/local/sbin/run
RUN chmod 755 /usr/local/sbin/run

###
WORKDIR /root
# ENTRYPOINT ["bash"]
ENTRYPOINT ["run"]
