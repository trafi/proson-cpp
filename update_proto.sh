#!/usr/bin/env bash

if [ ! -f config ]; then
    echo "Config file was not found (rename config.tmp to config)!"
fi

source config

cd tests
${PROTO_BIN} --cpp_out=. dto.proto