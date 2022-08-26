FROM alpine:latest

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    mosquitto \
    nano \
    && apt clean

USER user
WORKDIR /home/user/wbx
