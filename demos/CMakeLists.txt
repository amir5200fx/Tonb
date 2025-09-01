cmake_minimum_required(VERSION 3.23)

# Toggle to build or skip all demos
option(BUILD_TONB_DEMOS "Build Tonb demo applications" ON)
if (NOT BUILD_TONB_DEMOS)
    return()
endif ()

# Add more demo group here later (e.g. cad/, geometry/, ...)
add_subdirectory(system)
add_subdirectory(io)
add_subdirectory(geometry)