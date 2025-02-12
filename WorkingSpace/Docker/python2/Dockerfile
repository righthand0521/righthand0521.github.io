### Local
# docker build --tag python2 .
# docker build --tag python2 -f Dockerfile .
# docker run --network host --rm -it python2
#
### Docker Hub
# docker build --tag righthand0521/python2 .
# docker build --tag righthand0521/python2 -f Dockerfile .
# docker push righthand0521/python2:latest
# docker run --network host --rm -it righthand0521/python2
#
### tar
# docker images python2
# docker save python2 > python2.tgz
# docker load < python2.tgz


###
FROM ubuntu:24.04
FROM python:2.7-slim

###
LABEL authors="Yu-Chuan Cheng"
LABEL version="1.0.1"
LABEL description="This is testing tool using python2. The network environment is inherited host settings."

###
RUN apt update -y
RUN apt install build-essential libc6 libc6-dev -y
RUN apt install net-tools -y
RUN apt install wget curl -y
RUN apt install vim -y
#
RUN python -m pip install --upgrade pip
RUN pip install pyinstaller==3.6

###
COPY tcpServer.py /root/tcpServer.py
COPY udpServer.py /root/udpServer.py
#
WORKDIR /root
RUN pyinstaller -F /root/tcpServer.py
RUN pyinstaller -F /root/udpServer.py
#
RUN cp /root/dist/tcpServer /usr/local/sbin/tcpServer
RUN chmod 755 /usr/local/sbin/tcpServer
RUN cp /root/dist/udpServer /usr/local/sbin/udpServer
RUN chmod 755 /usr/local/sbin/udpServer
#
RUN rm -rf /root/build /root/dist
RUN rm -f /root/tcpServer.spec /root/udpServer.spec

###
RUN ln -sf /bin/bash /bin/sh

###
WORKDIR /root
ENTRYPOINT ["bash"]
