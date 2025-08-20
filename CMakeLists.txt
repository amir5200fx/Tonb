cmake_minimum_required(VERSION 3.23)

# Enable vcpkg integration
# Only set if the user didn't already pass - DCMAKE_TOOLCHAIN_FILE=...
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (DEFINED ENV{VCPKG_ROOT})
        # CMake is fine with forward slashes on all platforms
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "Vcpkg toolchain file" FORCE)
        message(STATUS "Using vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
    else ()
        message(FATAL_ERROR
            "VCPKG_ROOT is not set in the environment."
            "Set it, or pass -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.cmake")
    endif ()
endif ()

project(Tonb
        VERSION 0.1.0
        DESCRIPTION "TONB multi-library workspace"
        LANGUAGES CXX)

# NEW: standard install dirs (bin/lib/include)
include(GNUInstallDirs)

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

# --- Install the library ---

install(TARGETS TnbSystem
        EXPORT TonbTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# --- Package config files ---
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMinorVersion
)

configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/TonbConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tonb
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tonb)


