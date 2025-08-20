cmake_minimum_required(VERSION 3.23)

# Enable vcpkg integration
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

project(Tonb
        VERSION 0.1.0
        DESCRIPTION "TONB multi-library workspace"
        LANGUAGES CXX)

# Global policies
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# So CLion uses compile_commands.json reliably
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)  # OFF => static
set(CMAKE_POSITION_INDEPENDENT_CODE ON)                # good for static->shared linkage

option(TNB_WITH_CEREAL "Use cereal instead of Boost.Serialization" OFF)
option(BUILD_TESTING "Running the tests" ON)

# Threads (needed for std::thread and sometimes by gtest itself)
find_package(Threads REQUIRED)

include(CTest)

# subprojects
add_subdirectory(libs/system)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()


