cmake_minimum_required(VERSION 3.23)

# Tell CMake we’re OK with the new behavior (use BoostConfig, not FindBoost)
cmake_policy(SET CMP0167 NEW)

# Enable vcpkg integration
# Only set if the user didn't already pass - DCMAKE_TOOLCHAIN_FILE=...
option(TONB_ENABLE_VCPKG "Use vcpkg toolchain" ON)
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (TONB_ENABLE_VCPKG AND DEFINED ENV{VCPKG_ROOT})
        # CMake is fine with forward slashes on all platforms
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "Vcpkg toolchain file" FORCE)
        message(STATUS "Using vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
    else ()
        message(STATUS "VCPKG_ROOT not set; building without vcpkg")
    endif ()
endif ()

project(Tonb
        VERSION 0.20.0
        DESCRIPTION "TONB multi-library workspace"
        LANGUAGES C CXX)

# --------------------------------------------------------------------
# Windows SDK targeting (to avoid ext-ms-win-* API set dependency)
# This only affects Windows + MSVC; Linux builds ignore it.
# --------------------------------------------------------------------
if (WIN32)
    # Choose a Windows SDK version that actually exists on your machine.
    # 10.0.19041.0 is a safe, common Windows 10 SDK example.
    # Make sure this version is installed in Visual Studio.
    set(CMAKE_SYSTEM_VERSION 10.0.19041)

    if (MSVC)
        # For Visual Studio generators, explicitly select the SDK
        set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION "10.0.19041.0")
    endif ()
endif ()

option(BUILD_SHARED_LIBS "Build shared libraries" ON)  # OFF => static
option(TONB_WITH_CEREAL "Use cereal instead of Boost.Serialization" OFF)
option(BUILD_TESTING "Running the tests" OFF)

option(TONB_BUILD_DOCS "Build documentation (Doxygen + Sphinx)" ON)

# ---- OCCT ----

option(TONB_WITH_OCCT "Build OCCT adaptors" ON)

# ---- CGAL ----
option(TONB_WITH_CGAL "Enable CGAL-based functions" ON)

# ---- EIGEN ----
option(TONB_WITH_EIGEN "Enable Eigen-backed implementations" ON)

# ---- VTK -----
option(TONB_WITH_VTK "Enable VTK-based functions" ON)
#if (TONB_WITH_VTK)
#    set(TONB_VTK_MAJOR "")
#endif ()

include(GNUInstallDirs)

# Generate tonb/config.hxx with 0/1 macros
set(DOXYGEN_OUT_DIR "${CMAKE_BINARY_DIR}/docs/doxygen")
configure_file(
        ${CMAKE_SOURCE_DIR}/cmake/tonb_config.hxx.in
        ${CMAKE_BINARY_DIR}/generated/tonb/config.hxx
        @ONLY
)

# ---- Doxygen ----
find_package(Doxygen QUIET)
find_program(SPHINX_BUILD sphinx-build)

#if (TONB_BUILD_DOCS AND DOXYGEN_FOUND AND SPHINX_BUILD)
#    # ... your current doxygen + sphinx targets ...
#    add_custom_target(docs DEPENDS sphinx)
#elseif(TONB_BUILD_DOCS)
#    message(STATUS "Docs disabled: Doxygen found=${DOXYGEN_FOUND}, sphinx-build found=${SPHINX_BUILD}")
#endif()

if (TONB_BUILD_DOCS AND DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
    set(DOXY_OUT_DIR ${CMAKE_BINARY_DIR}/docs/doxygen)

    file(MAKE_DIRECTORY ${DOXY_OUT_DIR})
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doxygen
            COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXY_OUT_DIR}
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            COMMENT "Generating API documentation with Doxygen")
endif()

if (TONB_BUILD_DOCS AND DOXYGEN_FOUND AND SPHINX_BUILD)
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

set(_lib_ver     "${TONB_SEMVER_CORE}")
set(_lib_sov     "${TONB_SEMVER_MAJOR}")
if(NOT _lib_ver)
    set(_lib_ver "${PROJECT_VERSION}")
endif()
if(NOT _lib_sov)
    set(_lib_sov "${PROJECT_VERSION_MAJOR}")
endif()

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
# So CLion uses compile_commands.json reliably
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)                # good for static->shared linkage



# Threads (needed for std::thread and sometimes by gtest itself)
find_package(Threads REQUIRED)

include(CTest)
# subprojects
add_subdirectory(libs/system)
add_subdirectory(libs/base)
add_subdirectory(libs/io)
add_subdirectory(libs/geometry)
add_subdirectory(libs/cad2d)
add_subdirectory(libs/cad)
add_subdirectory(demos)

add_custom_target(TonbAll
        DEPENDS TonbSystem TonbBase TonbGeometry TonbCAD2d TonbCAD TonbIO
)

if (BUILD_TESTING)
    message(STATUS "Tests are going to be built")
    add_subdirectory(tests)
else ()
    message(STATUS "No test are going to be built")
endif ()
#add_subdirectory(tests)

#add_subdirectory(apps)

# Make it visible to all Tonb targets during build
# (do this once, after you've created your library targets)
target_include_directories(TonbSystem  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>)
target_include_directories(TonbIO    PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>)
target_include_directories(TonbBase    PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>)
target_include_directories(TonbGeometry PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>)
target_include_directories(TonbCAD2d PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>)
target_include_directories(TonbCAD PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>)

add_executable(Tonb main.cxx)

target_link_libraries(Tonb PRIVATE TonbSystem TonbIO TonbBase TonbGeometry TonbCAD2d TonbCAD)
# Install the generated header
install(FILES ${CMAKE_BINARY_DIR}/generated/tonb/config.hxx
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tonb)

# --- Install the library ---

set_target_properties(TonbSystem PROPERTIES
        VERSION   "${_lib_ver}"
        SOVERSION "${_lib_sov}"
)
set_target_properties(TonbBase PROPERTIES
        VERSION "${_lib_ver}"
        SOVERSION "${_lib_sov}"
)
set_target_properties(TonbIO PROPERTIES
        VERSION "${_lib_ver}"
        SOVERSION "${_lib_sov}"
)
set_target_properties(TonbGeometry PROPERTIES
        VERSION "${_lib_ver}"
        SOVERSION "${_lib_sov}"
)
set_target_properties(TonbCAD2d PROPERTIES
        VERSION "${_lib_ver}"
        SOVERSION "${_lib_sov}"
)
set_target_properties(TonbCAD PROPERTIES
        VERSION "${_lib_ver}"
        SOVERSION "${_lib_sov}"
)

# right before configure_package_config_file(...)
include(CMakePackageConfigHelpers)

# Install the library once (from the root), and attach it to export set "TonbTargets"
install(TARGETS TonbSystem TonbBase TonbIO TonbGeometry TonbCAD2d TonbCAD
        EXPORT TonbTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the export file
install(EXPORT TonbTargets
        NAMESPACE Tonb::        # creates Tonb::System, Tonb::Base, …
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Tonb
)
set_target_properties(TonbSystem PROPERTIES EXPORT_NAME System)
set_target_properties(TonbBase PROPERTIES EXPORT_NAME Base)
set_target_properties(TonbGeometry PROPERTIES EXPORT_NAME Geometry)
set_target_properties(TonbCAD2d PROPERTIES EXPORT_NAME CAD2d)
set_target_properties(TonbCAD PROPERTIES EXPORT_NAME CAD)
set_target_properties(TonbIO PROPERTIES EXPORT_NAME IO)

# Configure + install Config files in the same folder (note the capital T)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/TonbConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Tonb
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMinorVersion
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/TonbConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Tonb
)

# ---- Packing (CPack) ---
set(CPACK_PACKAGE_NAME "Tonb")
set(CPACK_PACKAGE_VENDOR "Tonb Project")
set(CPACK_PACKAGE_CONTACT "a.amirsolaymani@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Tonb core system library, headers, and demos")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES ON)

# version info comes from project()
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

# Linux .deb niceties (Pop!-OS/Ubuntu)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)  # auto-detect shared lib deps
set(CPACK_GENERATOR "TGZ;DEB")          # tar.gz and .deb; adjust as you like

include(CPack)                          # generates CPackConfig.cmake

# e.g., in demos/system/CMakeLists.txt
if (TARGET demo_logger)
    install(TARGETS demo_logger RUNTIME DESTINATION bin)
endif ()

