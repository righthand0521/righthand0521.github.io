### Local
# docker build --tag samba .
# docker build --tag samba -f Dockerfile .
# docker run --network host --rm -it samba
#
### Docker Hub
# docker build --tag righthand0521/samba .
# docker build --tag righthand0521/samba -f Dockerfile .
# docker push righthand0521/samba:latest
# docker run --network host --rm -it righthand0521/samba
#
### tar
# docker images samba
# docker save samba > samba.tgz
# docker load < samba.tgz


###
# FROM ubuntu:22.04
FROM ubuntu:24.04

###
LABEL authors="Yu-Chuan Cheng"
LABEL version="1.0.1"
LABEL description="This is testing tool. The network environment is inherited host settings."

###
RUN apt update -y
RUN apt install wget curl -y
RUN apt install net-tools -y
RUN apt install vim -y
RUN apt install tree -y
#
RUN apt install samba samba-common -y
RUN apt install inotify-tools -y

###
# admin / password
RUN (echo password; echo password; echo; echo; echo; echo; echo; echo) | adduser admin
RUN mkdir -p /home/admin/folder1/folder2/folder3/folder4
RUN dd if=/dev/zero bs=1K count=1K >> /home/admin/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/admin/folder1/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/admin/folder1/folder2/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/admin/folder1/folder2/folder3/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/admin/folder1/folder2/folder3/folder4/1MB
RUN chown -R admin:admin /home/admin
# user12345678 / 1234567890
RUN (echo 1234567890; echo 1234567890; echo; echo; echo; echo; echo; echo) | adduser user12345678
RUN mkdir -p /home/user12345678/10000000_TestData/11000000_TestData/11100000_TestData/11110000_TestData
RUN dd if=/dev/zero bs=1K count=1K >> /home/user12345678/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/user12345678/10000000_TestData/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/user12345678/10000000_TestData/11000000_TestData/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/user12345678/10000000_TestData/11000000_TestData/11100000_TestData/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/user12345678/10000000_TestData/11000000_TestData/11100000_TestData/11110000_TestData/1MB
RUN chown -R user12345678:user12345678 /home/user12345678
# pi314159265358979323846264338327 / Aa@314
RUN (echo Aa@314; echo Aa@314; echo; echo; echo; echo; echo; echo) | adduser pi314159265358979323846264338327
RUN mkdir -p /home/pi314159265358979323846264338327/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz
RUN dd if=/dev/zero bs=1K count=1K >> /home/pi314159265358979323846264338327/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/pi314159265358979323846264338327/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/pi314159265358979323846264338327/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/pi314159265358979323846264338327/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/pi314159265358979323846264338327/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdefghijklmnopqrstuvwxyz/1MB
RUN chown -R pi314159265358979323846264338327:pi314159265358979323846264338327 /home/pi314159265358979323846264338327
#
RUN mkdir -p /home/public/share/10000000/11000000/11100000/11110000
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/share/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/share/10000000/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/share/10000000/11000000/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/share/10000000/11000000/11100000/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/share/10000000/11000000/11100000/11110000/1MB
#
RUN mkdir -p /home/public/admin/a_314159/ab_314159/abc_314159/abcd_314159
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/admin/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/admin/a_314159/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/admin/a_314159/ab_314159/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/admin/a_314159/ab_314159/abc_314159/1MB
RUN dd if=/dev/zero bs=1K count=1K >> /home/public/admin/a_314159/ab_314159/abc_314159/abcd_314159/1MB
RUN chmod -R 777 /home/public

###
#
COPY smbv1.conf /etc/samba/smbv1.conf
COPY smbv2.conf /etc/samba/smbv2.conf
COPY smbv3.conf /etc/samba/smbv3.conf
#
RUN (echo password; echo password) | smbpasswd -a admin
RUN (echo 1234567890; echo 1234567890) | smbpasswd -a user12345678
RUN (echo Aa@314; echo Aa@314) | smbpasswd -a pi314159265358979323846264338327
#
# RUN service nmbd start
# RUN service smbd start

###
COPY run.sh /usr/local/sbin/run
RUN chmod 755 /usr/local/sbin/run

###
RUN ln -sf /bin/bash /bin/sh

###
WORKDIR /root
# ENTRYPOINT ["bash"]
ENTRYPOINT ["run"]
