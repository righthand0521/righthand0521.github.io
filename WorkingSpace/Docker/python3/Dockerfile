### Local
# docker build --tag python3 .
# docker build --tag python3 -f Dockerfile .
# docker run --network host --rm -it python3
#
### Docker Hub
# docker build --tag righthand0521/python3 .
# docker build --tag righthand0521/python3 -f Dockerfile .
# docker push righthand0521/python3:latest
# docker run --network host --rm -it righthand0521/python3
#
### tar
# docker images python3
# docker save python3 > python3.tgz
# docker load < python3.tgz


###
FROM ubuntu:24.04
FROM python:3.12-slim

###
LABEL authors="Yu-Chuan Cheng"
LABEL version="1.0.1"
LABEL description="This is testing tool using python3. The network environment is inherited host settings."

###
RUN apt update -y
RUN apt install build-essential libc6 libc6-dev -y
RUN apt install net-tools -y
RUN apt install wget curl -y
RUN apt install vim -y
#
RUN python -m pip install --upgrade pip
RUN pip install pyinstaller==6.3

###
COPY server.py /root/server.py
COPY client.py /root/client.py
#
WORKDIR /root
RUN pyinstaller -F /root/server.py
RUN pyinstaller -F /root/client.py
#
RUN cp /root/dist/server /usr/local/sbin/server
RUN chmod 755 /usr/local/sbin/server
RUN cp /root/dist/client /usr/local/sbin/client
RUN chmod 755 /usr/local/sbin/client
#
RUN rm -rf /root/build /root/dist
RUN rm -f /root/server.spec /root/client.spec

###
RUN ln -sf /bin/bash /bin/sh

###
WORKDIR /root
ENTRYPOINT ["bash"]
