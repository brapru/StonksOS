FROM ubuntu:20.04

MAINTAINER brapru

RUN apt-get update && apt-get install -y gcc-aarch64-linux-gnu g++-aarch64-linux-gnu build-essential

ENV BUILD_FOLDER /build

WORKDIR ${BUILD_FOLDER}

CMD ["/bin/bash", "-c", "make", "-f", "${BUILD_FOLDER}/Makefile"]
