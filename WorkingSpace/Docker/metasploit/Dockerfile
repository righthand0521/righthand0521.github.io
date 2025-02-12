### Local
# docker build --tag metasploit .
# docker build --tag metasploit -f Dockerfile .
# docker run --network host --rm -it metasploit
# docker run --network host --rm -it metasploit <Module> <RHOSTS>
#
### Docker Hub
# docker build --tag righthand0521/metasploit .
# docker build --tag righthand0521/metasploit -f Dockerfile .
# docker push righthand0521/metasploit:latest
# docker run --network host --rm -it righthand0521/metasploit
# docker run --network host --rm -it righthand0521/metasploit <Module> <RHOSTS>
#
### tar
# docker images metasploit
# docker save metasploit > metasploit.tgz
# docker load < metasploit.tgz


###
# FROM ubuntu:22.04
FROM ubuntu:24.04

###
LABEL authors="Yu-Chuan Cheng"
LABEL version="1.0.1"
LABEL description="This is testing tool using Metasploit. The network environment is inherited host settings."

###
RUN apt update -y
RUN apt install net-tools -y
RUN apt install wget curl -y
RUN apt install gnupg2 gpg-agent -y
RUN apt install vim -y

###
WORKDIR /opt
RUN wget http://apt.metasploit.com/metasploit-framework.gpg.key
RUN gpg --no-default-keyring --keyring ./metasploit-framework_keyring.gpg --import metasploit-framework.gpg.key
RUN gpg --no-default-keyring --keyring ./metasploit-framework_keyring.gpg --export > ./metasploit-framework.gpg
RUN mv ./metasploit-framework.gpg /etc/apt/trusted.gpg.d/
RUN apt update -y
#
RUN curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall
RUN chmod 755 msfinstall
RUN ./msfinstall
#
COPY run.sh /usr/local/sbin/run
RUN chmod 755 /usr/local/sbin/run

###
RUN ln -sf /bin/bash /bin/sh

###
WORKDIR /
ENTRYPOINT ["run"]
