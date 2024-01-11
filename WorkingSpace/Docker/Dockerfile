# docker build --tag test .
# docker run test
# docker run --rm -it test bash

# FROM alpine
# FROM ubuntu:20.04
FROM ubuntu:22.04

# FROM python:3.10
# FROM python:3.10-alpine
FROM python:3.10-slim

# RUN apt update -y && apt install build-essential libc6 libc6-dev -y
# RUN pip install pyinstaller
# RUN pip install pyinstaller==3.6

# COPY . /
COPY . /usr/bin/

# RUN chmod 755 /usr/bin/test

# RUN sed -i -e 's|#force_color_prompt=yes|force_color_prompt=yes|' .bashrc

# ENTRYPOINT ["echo"]

# CMD echo hello world
# CMD ["test"]
