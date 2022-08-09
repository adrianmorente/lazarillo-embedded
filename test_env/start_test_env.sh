#!/bin/bash

# Give docker access to host's screen
xhost +local:docker

# Create directory for service's logs
PROJECT_DIR="$(cd -P "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
log_path=$(echo ${PROJECT_DIR}/log)
mkdir -p $log_path

docker run -it --rm \
    --privileged=true \
    -e DISPLAY=$DISPLAY \
    --name lazarillo_embedded_test \
    --add-host mosquitto-service:127.0.0.1 \
