#!/bin/bash

HAKONIWA_TOP_DIR=`pwd`

DIR_PATH=`dirname $0`
IMAGE_NAME=`cat ${DIR_PATH}/image_name.txt`
IMAGE_TAG=`cat ${DIR_PATH}/latest_version.txt`
DOCKER_IMAGE=${IMAGE_NAME}:${IMAGE_TAG}

ARCH=`arch`
OS_TYPE=`uname`

if [ ${OS_TYPE} != "Darwin" ]
then
	docker ps > /dev/null
	if [ $? -ne 0 ]
	then
	    sudo service docker start
	    echo "waiting for docker service activation.. "
	    sleep 3
	fi
fi

IPADDR="127.0.0.1"

if [ ${OS_TYPE} != "Darwin" ]
then
	docker run -v ${HAKONIWA_TOP_DIR}:/root/workspace/hakoniwa-pdu-registry \
		-it --rm \
		--net host \
		-e CORE_IPADDR=${IPADDR} \
		-e OS_TYPE=${OS_TYPE} \
		--name hakoniwa-pdu-registry ${DOCKER_IMAGE} 
else
	if [ $ARCH = "arm64" ]
	then
		docker run -v ${HAKONIWA_TOP_DIR}:/root/workspace/hakoniwa-pdu-registry \
            --platform linux/amd64 \
			-it --rm \
			-e CORE_IPADDR=${IPADDR} \
			-e ROS_UNITY_IPADDR=${IPADDR} \
			-e OS_TYPE=${OS_TYPE} \
			--name hakoniwa-pdu-registry ${DOCKER_IMAGE} 
	else
		docker run -v ${HAKONIWA_TOP_DIR}:/root/workspace/hakoniwa-pdu-registry \
			-it --rm \
			-e CORE_IPADDR=${IPADDR} \
			-e ROS_UNITY_IPADDR=${IPADDR} \
			-e OS_TYPE=${OS_TYPE} \
			--name hakoniwa-pdu-registry ${DOCKER_IMAGE} 
	fi
fi
