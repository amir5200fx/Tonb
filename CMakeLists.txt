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
        VERSION 0.18.0
        DESCRIPTION "TONB multi-library workspace"
        LANGUAGES CXX)

# --- Git describe (full build id) + numeric SemVer core -----------------------
find_package(Git QUIET)

# Combine SemVer from project() with the Git description (if available)
set(TONB_GIT_DESC "")
set(TONB_SEMVER_CORE "${PROJECT_VERSION}") # fallback to project() version if set
if (Git_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --always
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE TONB_GIT_DESC
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
    )

    if (TONB_GIT_DESC)
        # Strip leading 'v' and grab the first N.N.N group for SONAME
        string(REGEX REPLACE "^v" "" _desc "${TONB_GIT_DESC}")
        string(REGEX MATCH "^[0-9]+\\.[0-9]+\\.[0-9]+" TONB_SEMVER_CORE "${_desc}")
    endif ()
endif ()

if (NOT TONB_SEMVER_CORE)
    set(TONB_SEMVER_CORE "0.0.0")
endif ()

# Split core into major/minor/patch
string(REPLACE "." ";" _vparts "${TONB_SEMVER_CORE}")
list(GET _vparts 0 TONB_SEMVER_MAJOR)
list(GET _vparts 1 TONB_SEMVER_MINOR)
list(GET _vparts 2 TONB_SEMVER_PATCH)

message(STATUS "Tonb git: ${TONB_GIT_DESC}")
message(STATUS "Tonb so: VERSION=${TONB_SEMVER_CORE}  SOVERSION=${TONB_SEMVER_MAJOR}")

# Combine SemVer from project() with the Git description (if available)
if (TONB_GIT_DESC)
    set(TONB_FULL_VERSION "${PROJECT_VERSION} (${TONB_GIT_DESC})")
else ()
    set(TONB_FULL_VERSION "${PROJECT_VERSION}")
endif ()

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

#include(CTest)

# subprojects
add_subdirectory(libs/system)
add_subdirectory(demos)

if (BUILD_TESTING)
#    add_subdirectory(tests)
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


