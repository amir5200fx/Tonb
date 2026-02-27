cmake_minimum_required(VERSION 3.23)

# Find the tonb::io target from the workspace; if not present, try a package.
if (NOT TARGET Tonb::Numerics)
    if (TARGET TonbNumerics) # alias in your libs/io/CMake
        add_library(Tonb::Numerics ALIAS Tonb::Numerics)
    else ()
        find_package(Tonb CONFIG REQUIRED) # in case you're building demos against an installed Tonb
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

# === Common runtime output directory for ALL demos ===
# Result: <build>/demos/bin/<Config> (on multi-config generators)
set(DEMOS_RUNTIME_DIR "${CMAKE_BINARY_DIR}/demos/bin")

# Helper to send an exe + its runtime DLLs to the common bin dir (Windows)
function(collect_runtime_into_common_bin target)
    # Put the exe in the shared bin dir (add <Config> suffix for MSVC/Xcode)
    set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${DEMOS_RUNTIME_DIR}/$<CONFIG>"
    )

    if (WIN32)
        # Copy all dependent DLLs next to the exe (duplicates skipped)
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "${DEMOS_RUNTIME_DIR}/$<CONFIG>"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${target}> "${DEMOS_RUNTIME_DIR}/$<CONFIG>"
                COMMAND_EXPAND_LISTS
                COMMENT "Collecting runtime DLLs for ${target} into ${DEMOS_RUNTIME_DIR}/$<CONFIG>"
        )
        # Nice QoL when launching from Visual Studio
        set_property(TARGET ${target} PROPERTY
                VS_DEBUGGER_WORKING_DIRECTORY "${DEMOS_RUNTIME_DIR}/$<CONFIG>")
    endif()
endfunction()

# For each source, create an executable with the file stem as the target name
foreach (src IN LISTS DEMO_SOURCES)
    get_filename_component(name "${src}" NAME_WE)
    add_executable(${name} "${src}")

    # If you consume headers directly from the repo (not installed), make sure the include path is visible.
    # (Comment this out if TnbIO already publishes include dirs PUBLIC.)
    #target_include_directories(${name} PRIVATE "${CMAKE_SOURCE_DIR}/libs/system/include")

    target_link_libraries(${name} PRIVATE Tonb::Numerics Threads::Threads)

    # Standard, warnings, and threads
    target_compile_features(${name} PRIVATE cxx_std_20)
    if (MSVC)
        target_compile_options(${name} PRIVATE /W4 /permissive-)
    else ()
        target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic)
    endif ()

    #    find_package(Threads REQUIRED)
    #    target_link_libraries(${name} PRIVATE Threads::Threads)

    # Optional: if you enabled the SPDLOG sink in tonb::system and want to demo to toggle ti too:
    #target_compile_definitions(${name} PRIVATE TONB_WITH_SPDLOG)

    collect_runtime_into_common_bin(${name})
endforeach ()