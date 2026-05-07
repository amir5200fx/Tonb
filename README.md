# Tonb

Tonb is a C++20 system library that provides:

- **Structured logging** (`tonb::system::Logger`) with console/JSON/buffered sinks, contexts, rate limiting, and task integration.
- **Task utilities** (`Task`, progress, cancellation).
- **Serialization helpers** (wire header, optional type tags, peek helpers).
- A clean **CMake** build + install, with demos.

> The previous Visual Studio–only code is kept under **`Legacy/`** and still runs unchanged.

---

## Features

- **Logger**
  - `ConsoleSink`, `JsonFileSink` (NDJSON), `BufferedTextSink` (flush/rewind).
  - `withContext`, levels (`info/debug/warn/error`), structured fields.
  - Scope timing and simple rate limiting.
- **Task**
  - Progress, cancellation, logging hooks.
- **Serialization**
  - Wire header + optional **type tags** for self-describing files.
  - `peek_file_type()` without loading the whole payload.
- **CMake friendly**
  - `find_package(tonb CONFIG REQUIRED)` → `tonb::system`.
  - Installs headers, library, and CMake package files.

---

## Getting Started

### Requirements
- C++20 compiler (GCC/Clang/MSVC)
- CMake ≥ 3.23
- (Optional) **vcpkg** for extras (e.g., `spdlog`, `gtest`)

### Build (Linux / Pop!_OS)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

### Run demos from the build tree
```bash
# If your library is shared:
LD_LIBRARY_PATH="$PWD/build/libs/system:$LD_LIBRARY_PATH" ./build/demos/system/demo_logger
```

### Install (local prefix)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$PWD/install"
cmake --build build -j
cmake --install build
./install/bin/demo_logger   # RPATH is set so it finds install/lib
```

### System install (Ubuntu/Pop!_OS)
```bash
sudo cmake --install build
sudo ldconfig
demo_logger
```

---

## Use Tonb from another CMake project

```cmake
find_package(tonb CONFIG REQUIRED)
add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE tonb::system)
```

---

## Quick Log Example

```cpp
#include <tonb/system/log.hxx>
#include <tonb/system/version.hxx>
using namespace tonb::system;

int main() {
  auto root = std::make_shared<Logger>(LogLevel::Info, "App");
  root->addSink(std::make_shared<ConsoleSink>(true, true));
  root->addSink(std::make_shared<JsonFileSink>("logs.ndjson"));

  auto log = root->withContext("Startup");
  log->info("Tonb ready", {{"semver", std::string(version_semver())},
                           {"build",  std::string(version_full())}});
}
```

---

## Demos

- **logger_demo** — shows sinks, contexts, scope timing, flush/rewind, and task logging.
  - Build: `cmake --build build --target logger_demo`
  - Run (build tree): `./build/demos/system/logger_demo`  
    (Set `LD_LIBRARY_PATH` if using shared libs, see above.)

---

## Versioning

- Releases follow **Semantic Versioning** (MAJOR.MINOR.PATCH).
- The shared library’s ELF names use the **numeric** SemVer core (e.g., `libTnbSystem.so.0.19.0` with `SOVERSION=0`).
- `tonb/system/version.hxx` exposes:
  - `version_semver()` → `0.19.0`
  - `version_full()` → `git describe` string (e.g., `v0.19.0-12-gabc1234`)

See **[CHANGELOG.md](./CHANGELOG.md)** for what changed.

---

## Legacy Code

The previous Visual Studio–based codebase lives under **`Legacy/`** and can still be built/run independently if needed.

---

## License

Licensed under the **MIT License**. See [LICENSE](./LICENSE) for details.

---

## Contributing

- Keep commits focused and well-described (we use Conventional Commits).
- Add/update tests for fixes and features.
- For bugs, include repro steps or a minimal snippet.
