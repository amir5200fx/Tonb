# This file lives in tests/
cmake_minimum_required(VERSION 3.23)

# Pull GTest from vcpkg (already installed)
find_package(GTest CONFIG REQUIRED)
find_package(Threads REQUIRED)

# Keep suites in subfolders if you like
add_subdirectory(system)
add_subdirectory(io)
add_subdirectory(cad2d)
add_subdirectory(shell)