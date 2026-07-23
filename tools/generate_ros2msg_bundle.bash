#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
REGISTRY_DIR="$(cd "${SCRIPT_DIR}/.." && pwd -P)"

usage() {
    cat <<'EOF'
Usage:
  generate_ros2msg_bundle.bash <message-type> -o <output> [--search-path <dir>]...

Examples:
  bash ../hakoniwa-pdu-registry/tools/generate_ros2msg_bundle.bash \
    sensor_msgs/JointState \
    -o ./work/schemas/ros2_jazzy/sensor_msgs/msg/JointState.bundle.msg

  bash ../hakoniwa-pdu-registry/tools/generate_ros2msg_bundle.bash \
    my_msgs/msg/MyMessage \
    --search-path ../my_ros_interfaces/install/share \
    -o ./work/schemas/MyMessage.bundle.msg

The wrapper runs the pure-Python generator inside the pinned
hakoniwa-pdu-registry Docker image. No interactive shell and no ROS 2 runtime on
the host are required.
EOF
}

MESSAGE_TYPE=""
OUTPUT_PATH=""
SEARCH_PATHS=()

while [ "$#" -gt 0 ]; do
    case "$1" in
        -o|--output)
            if [ "$#" -lt 2 ]; then
                echo "error: $1 requires a path" >&2
                exit 2
            fi
            OUTPUT_PATH="$2"
            shift 2
            ;;
        --search-path)
            if [ "$#" -lt 2 ]; then
                echo "error: --search-path requires a directory" >&2
                exit 2
            fi
            SEARCH_PATHS+=("$2")
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        --)
            shift
            break
            ;;
        -*)
            echo "error: unknown option: $1" >&2
            usage >&2
            exit 2
            ;;
        *)
            if [ -n "${MESSAGE_TYPE}" ]; then
                echo "error: multiple message types specified: ${MESSAGE_TYPE} and $1" >&2
                exit 2
            fi
            MESSAGE_TYPE="$1"
            shift
            ;;
    esac
done

if [ -z "${MESSAGE_TYPE}" ] || [ -z "${OUTPUT_PATH}" ]; then
    usage >&2
    exit 2
fi

if ! command -v docker >/dev/null 2>&1; then
    echo "error: docker command not found" >&2
    exit 1
fi

if ! docker info >/dev/null 2>&1; then
    echo "error: Docker is not running or is not accessible" >&2
    exit 1
fi

IMAGE_NAME="$(cat "${REGISTRY_DIR}/docker/image_name.txt")"
IMAGE_TAG="$(cat "${REGISTRY_DIR}/docker/latest_version.txt")"
DOCKER_IMAGE="${IMAGE_NAME}:${IMAGE_TAG}"
ROS_DISTRO="$(cat "${REGISTRY_DIR}/ROS_VERSION.txt")"

OS_TYPE="$(uname)"
ARCH="$(uname -m)"
USE_AMD64_PLATFORM=false
if [ "${OS_TYPE}" = "Darwin" ] && [ "${ARCH}" = "arm64" ]; then
    USE_AMD64_PLATFORM=true
fi

if ! docker image inspect "${DOCKER_IMAGE}" >/dev/null 2>&1; then
    echo "Docker image ${DOCKER_IMAGE} is not available locally; pulling it..."
    if [ "${USE_AMD64_PLATFORM}" = true ]; then
        docker pull --platform linux/amd64 "${DOCKER_IMAGE}"
    else
        docker pull "${DOCKER_IMAGE}"
    fi
fi

OUTPUT_DIR="$(dirname "${OUTPUT_PATH}")"
OUTPUT_NAME="$(basename "${OUTPUT_PATH}")"
mkdir -p "${OUTPUT_DIR}"
OUTPUT_DIR_ABS="$(cd "${OUTPUT_DIR}" && pwd -P)"

DOCKER_ARGS=(
    run
    --rm
    --user "$(id -u):$(id -g)"
    --volume "${REGISTRY_DIR}:/hako-registry:ro"
    --volume "${OUTPUT_DIR_ABS}:/hako-output"
)

if [ "${USE_AMD64_PLATFORM}" = true ]; then
    DOCKER_ARGS+=(--platform linux/amd64)
fi

PYTHON_ARGS=(
    python3
    /hako-registry/tools/generate_ros2msg_bundle.py
    "${MESSAGE_TYPE}"
    --search-path "/opt/ros/${ROS_DISTRO}/share"
    --search-path /hako-registry/idl
    -o "/hako-output/${OUTPUT_NAME}"
)

SEARCH_INDEX=0
if [ "${#SEARCH_PATHS[@]}" -gt 0 ]; then
    for SEARCH_PATH in "${SEARCH_PATHS[@]}"; do
        if [ ! -d "${SEARCH_PATH}" ]; then
            echo "error: search path is not a directory: ${SEARCH_PATH}" >&2
            exit 2
        fi
        SEARCH_PATH_ABS="$(cd "${SEARCH_PATH}" && pwd -P)"
        CONTAINER_SEARCH_PATH="/hako-search/${SEARCH_INDEX}"
        DOCKER_ARGS+=(--volume "${SEARCH_PATH_ABS}:${CONTAINER_SEARCH_PATH}:ro")
        PYTHON_ARGS+=(--search-path "${CONTAINER_SEARCH_PATH}")
        SEARCH_INDEX=$((SEARCH_INDEX + 1))
    done
fi

printf 'Generating %s -> %s\n' "${MESSAGE_TYPE}" "${OUTPUT_DIR_ABS}/${OUTPUT_NAME}"
docker "${DOCKER_ARGS[@]}" "${DOCKER_IMAGE}" "${PYTHON_ARGS[@]}"
