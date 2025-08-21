# Getting Started

## Build
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Install (local prefix)
```bash
cmake --install build --prefix "$PWD/install"
```

## Run demo (build tree)
```bash
# If lib is shared
LD_LIBRARY_PATH="$PWD/build/libs/system:$LD_LIBRARY_PATH" ./build/demos/system/demo_logger
```
