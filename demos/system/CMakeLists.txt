cmake_minimum_required(VERSION 3.23)

# Find the tonb::system target from the workspace; if not present, try a package.
if (NOT TARGET tonb::system)
    if (TARGET TnbSystem) # alias in your libs/system/CMake
        add_library(tonb::system ALIAS TnbSystem)
    else ()
        find_package(tonb CONFIG REQUIRED) # in case you're building demos against an installed Tonb
    endif ()
endif ()

# Collect all demo sources in this folder (ok for demos; avoids hand-editing)
file(GLOB DEMO_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

if (DEMO_SOURCES STREQUAL "")
    message(WARNING "No demo sources found in ${CMAKE_CURRENT_SOURCE_DIR} (expected *.cpp / *.cxx).")
endif ()

# For each source, create an executable with the file stem as the target name
foreach (src IN LISTS DEMO_SOURCES)
    get_filename_component(name "${src}" NAME_WE)
    add_executable(${name} "${src}")

    # If you consume headers directly from the repo (not installed), make sure the include path is visible.
    # (Comment this out if TnbSystem already publishes include dirs PUBLIC.)
    #target_include_directories(${name} PRIVATE "${CMAKE_SOURCE_DIR}/libs/system/include")

    target_link_libraries(${name} PRIVATE tonb::system)

    # Standard, warnings, and threads
    target_compile_features(${name} PRIVATE cxx_std_20)
    if (MSVC)
        target_compile_options(${name} PRIVATE /w4 /permissive-)
    else ()
        target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic)
    endif ()

    find_package(Threads REQUIRED)
    target_link_libraries(${name} PRIVATE Threads::Threads)

    # Optional: if you enabled the SPDLOG sink in tonb::system and want to demo to toggle ti too:
    #target_compile_definitions(${name} PRIVATE TONB_WITH_SPDLOG)
endforeach ()