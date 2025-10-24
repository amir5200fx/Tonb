FROM ubuntu:24.04 AS builder
LABEL authors="amir"

ARG DEBIAN_FRONTEND=noninteractive

# Toggles features (match your CMAKE options)
# Turn VTK OFF if you don't need it; it makes builds large $ slow.
ARG WITH_OCCT=OFF
ARG WITH_CGAL=ON
ARG WITH_EIGEN=ON
ARG WITH_VTK=OFF
ARG BUILD_DOCS=OFF
ARG BUIL_TESTING=OFF
ARG BUILD_SHARED_LIBS=ON
ARG CMAKE_BUILD_TYPE=Release

ARG CMAKE_VERSION=4.1.2
ARG CMAKE_TAR=cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz
ARG CMAKE_DIR=/opt/cmake-${CMAKE_VERSION}-linux-x86_64



# ----- Tooling & core libs -----------
RUN apt-get update && apt-get install -y software-properties-common && \
    add-apt-repository universe && \
    apt-get update && apt-get install -y --no-install-recommends \
    git curl ca-certificates build-essential pkg-config \
    ninja-build python3 zip unzip tar \
    autoconf automake libtool m4 gettext yasm nasm \
    libssl-dev libffi-dev zlib1g-dev \
    libx11-dev libxext-dev libglu1-mesa-dev libgl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# Tools needed by vcpkg's python3 port (autoreconf toolchain)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake m4 libtool libtool-bin gettext texinfo pkg-config \
    make build-essential \
    libssl-dev libffi-dev zlib1g-dev \
  && rm -rf /var/lib/apt/lists/*


# Install CMake (prebuilt) and put it first on PATH
RUN curl -fsSL "https://github.com/Kitware/CMAKE/releases/download/v${CMAKE_VERSION}/${CMAKE_TAR}" \
    -o "/tmp/${CMAKE_TAR}" \
    && mkdir -p /opt \
    && tar -xzf "/tmp/${CMAKE_TAR}" -C /opt \
    && ln -sf ${CMAKE_DIR}/bin/* /usr/local/bin/ \
    && cmake --version

# ---- VCPKG -----
ENV VCPKG_ROOT=/opt/vcpkg
ENV VCPKG_FORCE_SYSTEM_BINARIES=1
ENV VCPKG_DEFAULT_TRIPLET=x64-linux
ENV VCPKG_BUILD_TYPE=release
ENV VCPKG_ONLY_RELEASE=1
ENV VCPKG_FEATURE_FLAGS=manifests,binarycaching,only-release
# Write cache inside the image layers (or point at an external cache)
ENV VCPKG_BINARY_SOURCES="clear;default,readwrite"

RUN git clone --depth=1 https://github.com/microsoft/vcpkg.git ${VCPKG_ROOT} \
    && ${VCPKG_ROOT}/bootstrap-vcpkg.sh -disableMetrics

# ----- Dependencies ------
# Better: standard triplet
RUN ${VCPKG_ROOT}/vcpkg install --clean-after-build \
    boost-serialization:x64-linux \
    eigen3:x64-linux


RUN if [ "$WITH_OCCT" = "ON" ]; then \
    ${VCPKG_ROOT}/vcpkg install --clean-after-build opencascade:x64-linux-release; \
    fi

RUN if [ "$WITH_CGAL" = "ON" ]; then \
    ${VCPKG_ROOT}/vcpkg install --clean-after-build cgal:x64-linux-release; \
    fi

# ----- Optional: VTK (only if requested) ----
RUN if [ "$WITH_VTK" = "ON" ]; then \
    apt-get update && apt-get install -y --no-install-recommends libvtk9-dev && \
    rm -rf /var/lib/apt/lists/* ; \
    fi

WORKDIR /src
COPY . .

# ---- Configure (Release only) ----
RUN rm -rf build CMakeCache.txt CMakeFiles
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
    -DBUILD_TESTING=${BUILD_TESTING} \
    -DTONB_BUILD_DOCS=${BUILD_DOCS} \
    -DTONB_WITH_OCCT=${WITH_OCCT} \
    -DTONB_WITH_CGAL=${WITH_CGAL} \
    -DTONB_WITH_EIGEN=${WITH_EIGEN} \
    -DTONB_WITH_VTK=${WITH_VTK}

# ----- Build -----
RUN cmake --build build -j --target Tonb && strip build/Tonb || true


# ================= runtime ===========================
FROM ubuntu:24.04 AS runtime
WORKDIR /app
COPY --from=builder /src/build/Tonb /app/Tonb
RUN useradd -m runner
USER runner

ENTRYPOINT ["/app/Tonb"]