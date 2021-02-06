#!/bin/bash
PARENTDIR=$(dirname $(pwd))
BUILDDIR=/build

build_docker_image(){
        echo "Building docker compiler image..."
        if docker build -t stonksos-kernel-build . > /dev/null 2>&1; then
                echo "Built stonksos-kernel-build docker image!"
        else
                echo "Docker image build failed."
        fi
}

docker_compile(){
        echo "Building StonksOS from docker..."
        if docker run -it --rm -v $PARENTDIR:$BUILDDIR stonksos-kernel-build; then
                echo "Build complete!"
        else
                echo "Build failed."
        fi
}

if docker image inspect stonksos-kernel-build > /dev/null 2>&1
        then
                echo "Docker image already exists."
                docker_compile
        else
                echo "Couldn't find local docker image."
                build_docker_image
                docker_compile
fi
