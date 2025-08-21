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

option(TONB_BUILD_DOCS "Build documentation (Doxygen + Sphinx)" ON)

# ---- Doxygen ----
find_package(Doxygen QUIET)
find_program(SPHINX_BUILD sphinx-build)

if (DOXYGEN_FOUND)
    add_custom_target(doxygen
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/docs/doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            COMMENT "Generating API documentation with Doxygen")
endif()

if (DOXYGEN_FOUND AND SPHINX_BUILD)
    add_custom_target(sphinx
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/docs/sphinx/html
            COMMAND ${CMAKE_COMMAND} -E env
            DOXYGEN_XML_DIR=${CMAKE_BINARY_DIR}/docs/doxygen/xml
            ${SPHINX_BUILD} -b html
            -c ${CMAKE_SOURCE_DIR}/docs/sphinx
            ${CMAKE_SOURCE_DIR}/docs
            ${CMAKE_BINARY_DIR}/docs/sphinx/html
            DEPENDS doxygen
            COMMENT "Building Sphinx docs with Sphinx")
    add_custom_target(docs ALL DEPENDS sphinx)
endif()

#find_package(Doxygen QUIET)
#if (TONB_BUILD_DOCS AND DOXYGEN_FOUND)
#    set(DOXYGEN_IN   ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
#    set(DOXYGEN_OUT  ${CMAKE_BINARY_DIR}/Doxyfile)
#    set(DOXY_OUT_DIR ${CMAKE_BINARY_DIR}/docs/doxygen)
#
#    file(MAKE_DIRECTORY ${DOXY_OUT_DIR})
#    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#
#    add_custom_target(doxygen
#            COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXY_OUT_DIR}
#            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#            COMMENT "Generating API documentation with Doxygen" VERBATIM)
#endif()
#
## ---- Sphinx ----
#find_program(SPHINX_BUILD sphinx-build)
#if (TONB_BUILD_DOCS AND DOXYGEN_FOUND AND SPHINX_BUILD)
#    set(SPHINX_SRC_DIR   ${CMAKE_SOURCE_DIR}/docs/sphinx)           # where index.rst lives
#    set(SPHINX_CONF_DIR  ${CMAKE_BINARY_DIR}/docs/sphinx)           # generated conf.py lives here
#    set(SPHINX_HTML_DIR  ${CMAKE_BINARY_DIR}/docs/sphinx/html)
#
#    file(MAKE_DIRECTORY ${SPHINX_CONF_DIR} ${SPHINX_HTML_DIR})
#    configure_file(${SPHINX_SRC_DIR}/conf.py.in ${SPHINX_CONF_DIR}/conf.py @ONLY)
#
#    add_custom_target(sphinx
#            COMMAND ${CMAKE_COMMAND} -E make_directory ${SPHINX_HTML_DIR}
#            COMMAND ${SPHINX_BUILD} -b html -c ${SPHINX_CONF_DIR} ${SPHINX_SRC_DIR} ${SPHINX_HTML_DIR}
#            DEPENDS doxygen
#            COMMENT "Building Sphinx docs" VERBATIM)
#
#    add_custom_target(docs ALL DEPENDS doxygen sphinx)
#endif()

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


# ---- Packing (CPack) ---
set(CPACK_PACKAGE_NAME "tonb")
set(CPACK_PACKAGE_VENDOR "Tonb Project")
set(CPACK_PACKAGE_CONTACT "a.amirsolaymani@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Tonb core system library, headers, and demos")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

# version info comes from project()
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

# Linux .deb niceties (Pop!-OS/Ubuntu)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)  # auto-detect shared lib deps
set(CPACK_GENERATOR "TGZ;DEB")          # tar.gz and .deb; adjust as you like

include(CPack)                          # generates CPackConfig.cmake

# e.g., in demos/system/CMakeLists.txt
install(TARGETS demo_logger RUNTIME DESTINATION bin)

