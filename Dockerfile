# --------------------- Tonb Docker (Ubuntu 24.04) -------------------
# Multi-stage: builder has all toolchains; runtime is slim.
# Toggle features via --build-arg (defaults match the CMake options).

ARG UBUNTU_VER=24.04
FROM ubuntu:${UBUNTU_VER} AS builder
LABEL maintainder="Amir"

ARG DEBIAN_FRONTEND=noninteractive

# ---- Feature toggles (match CMake options) ----
ARG WITH_OCCT=ON
ARG WITH_CGAL=ON
ARG WITH_EIGEN=ON
ARG WITH_VTK=ON
ARG BUILD_DOCS=OFF
ARG BUILD_TESTING=OFF
ARG BUILD_SHARED_LIBS=ON
ARG CMAKE_BUILD_TYPE=Release

# ---- Base tools ----
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    git \
    ninja-build \
    pkg-config \
    curl \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install CMake 4.x from kitware
ARG CMAKE_VER=4.1.2
RUN curl -fsSL https://github.com/Kitware/CMake/releases/download/v${CMAKE_VER}/cmake-${CMAKE_VER}-linux-x86_64.sh \
      -o /tmp/cmake-${CMAKE_VER}-linux-x86_64.sh \
    && chmod +x /tmp/cmake-${CMAKE_VER}-linux-x86_64.sh \
    && /tmp/cmake-${CMAKE_VER}-linux-x86_64.sh --skip-license --prefix=/usr/local \
    && rm /tmp/cmake-${CMAKE_VER}-linux-x86_64.sh

# ---- Libraries (installed conditionally to keep image lean) ----
# Eigen (header-only)
RUN if [ "$WITH_EIGEN" = "ON" ]; then \
    apt-get update && apt-get install -y --no-install-recommends libeigen3-dev && \
    rm -rf /var/lib/apt/list/* ; \
fi

# Boost (needed unless TONB_WITH_CEREAL=ON) \
RUN apt-get update && apt-get install -y --no-install-recommends libboost-all-dev && \
    rm -rf /var/lib/apt/lists/*

# CGAL (pulls GMP/MPFR and recommends TBB) \
RUN if [ "$WITH_CGAL" = "ON" ]; then \
    apt-get update && apt-get install -y --no-install-recommends \
    libcgal-dev \
    libcgal-demo && \
    rm -rf /var/lib/apt/lists/* ; \
fi

# VTK (9.x on Ubuntu 24.04). Turn ON only if you need VTK-based features. \
RUN if [ "$WITH_VTK" = "ON" ]; then \
    apt-get update && apt-get install -y --no-install-recommends libvtk9-dev && \
    rm -rf /var/lib/apt/lists/* ; \
fi

# OpenCASCADE (OCCT) dev meta-packages (split by module in Ubuntu). \
RUN if [ "$WITH_OCCT" = "ON" ]; then \
    apt-get update && apt-get install -y --no-install-recommends \
    xfonts-scalable \
    libocct-data-exchange-dev \
    libocct-draw-dev \
    libocct-modeling-algorithms-dev \
    libocct-modeling-data-dev \
    libocct-ocaf-dev \
    libocct-visualization-dev \
    libocct-foundation-dev && \
    rm -rf /var/lib/apt/lists/* ; \
fi

# Docs (optional) \

# ---- Source ----
WORKDIR /src/tonb
# Copy only metadata first for better build caching
COPY CMakeLists.txt ./
COPY cmake ./cmake
# Copy the rest
COPY . .

# ---- Configure ----
# Note: Defaults to system packages. If you want vcpkg, set VCPKG_ROOT at build time and add:
#   -DTONB_ENABLE_VCPKG=ON (CMakeLists enables toolchain if VCPKG_ROOT is set)
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
    -DTONB_WITH_OCCT=${WITH_OCCT} \
    -DTONB_WITH_CGAL=${WITH_CGAL} \
    -DTONB_WITH_EIGEN=${WITH_EIGEN} \
    -DTONB_WITH_VTK=${WITH_VTK} \
    -DTONB_BUILD_DOCS=${BUILD_DOCS} \
    -DBUILD_TESTING=${BUILD_TESTING}

# ---- Build ---- \
RUN cmake --build build -j && \
    (strip build/Tonb || true)

# ---- install artifacts ---- \
RUN cmake --install build