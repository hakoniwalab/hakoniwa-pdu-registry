ARG ROS_DISTRO=jazzy
FROM ros:${ROS_DISTRO}-ros-base AS hakoniwa-pdu-registry-dev

ARG ROS_DISTRO
ARG DEBIAN_FRONTEND=noninteractive
ARG NODE_MAJOR=20
ARG HAKO_INSTALL_NODE=ON
ARG HAKO_INSTALL_MAVROS_MSGS=ON

ENV ROS_DISTRO=${ROS_DISTRO}
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# ---- base deps (one-shot apt) ----
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    build-essential \
    cmake \
    gcc \
    g++ \
    vim \
    make \
    autoconf \
    automake \
    pkg-config \
    curl \
    ca-certificates \
    jq \
    libssl-dev \
    libffi-dev \
    python3-dev \
    python3-jinja2 \
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# ---- ROS message definitions used by config/ros_msgs.txt ----
RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-${ROS_DISTRO}-common-interfaces \
    ros-${ROS_DISTRO}-tf2-msgs \
    && if [ "${HAKO_INSTALL_MAVROS_MSGS}" = "ON" ]; then \
        apt-get install -y --no-install-recommends ros-${ROS_DISTRO}-mavros-msgs; \
    fi \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# ---- Node.js (for npm / codex) ----
RUN if [ "${HAKO_INSTALL_NODE}" = "ON" ]; then \
      curl -fsSL https://deb.nodesource.com/setup_${NODE_MAJOR}.x | bash - \
      && apt-get update \
      && apt-get install -y --no-install-recommends nodejs \
      && npm --version \
      && node --version; \
    fi \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Workspace
RUN mkdir -p /root/workspace
WORKDIR /root/workspace
