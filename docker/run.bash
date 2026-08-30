#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HAKONIWA_TOP_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
CONTAINER_ROOT="/root/workspace/hakoniwa-pdu-registry"
IMAGE_NAME="$(<"${SCRIPT_DIR}/image_name.txt")"
IMAGE_TAG="$(<"${SCRIPT_DIR}/latest_version.txt")"
DOCKER_IMAGE="${IMAGE_NAME}:${IMAGE_TAG}"

ARCH="$(arch)"
OS_TYPE="$(uname)"
IPADDR="127.0.0.1"

if [[ "${OS_TYPE}" != "Darwin" ]] && ! docker ps >/dev/null 2>&1; then
    sudo service docker start
    echo "waiting for docker service activation.."
    sleep 3
fi

docker_args=(
    --rm
    --name hakoniwa-pdu-registry
    --volume "${HAKONIWA_TOP_DIR}:${CONTAINER_ROOT}"
    --workdir "${CONTAINER_ROOT}"
    --env "CORE_IPADDR=${IPADDR}"
    --env "OS_TYPE=${OS_TYPE}"
)

if [[ "${OS_TYPE}" == "Darwin" ]]; then
    docker_args+=(--env "ROS_UNITY_IPADDR=${IPADDR}")
    if [[ "${ARCH}" == "arm64" ]]; then
        docker_args+=(--platform linux/amd64)
    fi
else
    docker_args+=(--net host)
fi

# Preserve the original interactive shell when no command is supplied. When a
# command is supplied, run non-interactively for host-side tools and CI.
if (( $# == 0 )); then
    docker_args+=(-it)
fi

exec docker run "${docker_args[@]}" "${DOCKER_IMAGE}" "$@"
