FROM alpine:latest

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
    # Servers
    mysql-server \
    # Misc
    nano \
    && apt clean

# Setup entrypoint. Initial configuration needed for startup
COPY entrypoint.sh /opt/entrypoint.sh
ENTRYPOINT [ "/opt/entrypoint.sh" ]

USER user
WORKDIR /home/user/lzr
