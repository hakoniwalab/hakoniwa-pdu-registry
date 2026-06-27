#!/bin/bash

IMAGE_NAME=`cat docker/image_name.txt`
IMAGE_TAG=`cat docker/latest_version.txt`
DOCKER_IMAGE=${IMAGE_NAME}:${IMAGE_TAG}
DOCKER_FILE=docker/Dockerfile
DEFAULT_ROS_DISTRO=`cat ROS_VERSION.txt`
ROS_DISTRO=${1:-${ROS_DISTRO:-${DEFAULT_ROS_DISTRO}}}

echo "Building ${DOCKER_IMAGE} with ROS_DISTRO=${ROS_DISTRO}"

ARCH=`arch`
OS_TYPE=`uname`

if [ ${OS_TYPE} != "Darwin" ]
then
	docker build --build-arg ROS_DISTRO=${ROS_DISTRO} -t ${DOCKER_IMAGE} -f ${DOCKER_FILE} .
else
	if [ $ARCH = "arm64" ]
	then
		docker build --platform linux/amd64 --build-arg ROS_DISTRO=${ROS_DISTRO} -t ${DOCKER_IMAGE} -f ${DOCKER_FILE} .

	else
		docker build --build-arg ROS_DISTRO=${ROS_DISTRO} -t ${DOCKER_IMAGE} -f ${DOCKER_FILE} .
	fi
fi
