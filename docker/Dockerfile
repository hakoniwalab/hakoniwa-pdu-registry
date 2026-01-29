FROM ros:foxy AS hakoniwa-pdu-registry-dev

ARG DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# ---- base deps (one-shot apt) ----
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    build-essential \
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
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# ---- python deps ----
RUN pip3 --no-cache-dir install --upgrade pip setuptools wheel \
 && pip3 --no-cache-dir install jinja2 yq

# ---- Node.js (for npm / codex) ----
# Choose Node LTS. (18 or 20 are typical; pick one and stick to it)
ARG NODE_MAJOR=20
RUN curl -fsSL https://deb.nodesource.com/setup_${NODE_MAJOR}.x | bash - \
 && apt-get update && apt-get install -y --no-install-recommends nodejs \
 && npm --version && node --version \
 && apt-get clean && rm -rf /var/lib/apt/lists/*

# ---- MAVROS (optional) ----
RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-foxy-mavros \
    ros-foxy-mavros-extras \
    geographiclib-tools \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# Workspace
RUN mkdir -p /root/workspace
WORKDIR /root/workspace
