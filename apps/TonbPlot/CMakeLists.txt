# src/apps/TonbPlot/CMakeLists.txt

cmake_minimum_required(VERSION 3.23)

# ---- Target name ----
set(TONBPLOT_TARGET TonbPlot)
set(CMAKE_PREFIX_PATH "/home/amir/Qt/6.9.2/gcc_64" ${CMAKE_PREFIX_PATH})

# ----- Qt / VTK -----
# Expect Qt6 and VTK to be found at the top-lever CMake (recommended).
# but we keep a fallback here for direct builds of the app.
if (NOT TARGET Qt6::Widgets)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
endif ()

if (NOT DEFINED VTK_LIBRARIES)
    # Minimal VTK set for 2D polydata rendering and Qt support
    find_package(VTK REQUIRED COMPONENTS
            CommonCore
            CommonDataModel
            FiltersCore
            RenderingCore
            RenderingOpenGL2
            InteractionStyle
            GUISupportQt
    )
endif ()

# ----- Sources -----
# Keep sources explicit (recommended). Add files as you implement them.
set(TONBPLOT_SOURCES
        #entry
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx
        ${CMAKE_CURRENT_SOURCE_DIR}/main_window.cxx

        # model (POD-style)
        ${CMAKE_CURRENT_SOURCE_DIR}/model/mesh_2d.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/model/field.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/model/data_set.hxx
)


# ---- Executable -----
qt_add_executable(${TONBPLOT_TARGET}
        MANUAL_FINALIZATION
        ${TONBPLOT_SOURCES}
)

# ---- Language / warnings -----
target_compile_features(${TONBPLOT_TARGET} PRIVATE cxx_std_20)

# Nice warnings for MSVC/GCC/Clang
if (MSVC)
    target_compile_options(${TONBPLOT_TRAGET} PRIVATE /W4 /permissive-)
else ()
    target_compile_options(${TONBPLOT_TARGET} PRIVATE -Wall -Wextra -Wpedantic)
endif ()

# ---- Include paths ------
target_include_directories(${TONBPLOT_TARGET}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/views
        ${CMAKE_CURRENT_SOURCE_DIR}/render
        ${CMAKE_CURRENT_SOURCE_DIR}/model
        ${CMAKE_CURRENT_SOURCE_DIR}/io
        ${CMAKE_CURRENT_SOURCE_DIR}/util
)

# --- Link libraries -----
target_link_libraries(${TONBPLOT_TARGET}
        PRIVATE
        Qt6::Widgets
        ${VTK_LIBRARIES}
)

# VTK requires this for static initialization of factories on some platforms
vtk_module_autoinit(
        TARGETS ${TONBPLOT_TARGET}
        MODULES ${VTK_LIBRARIES}
)

# ----- App properties ------
set_target_properties(${TONBPLOT_TARGET} PROPERTIES
        OUTPUT_NAME "TonbPlot"
)

# ---- Install (optional but handy) -----
# You can refine runtime/library destinations to match your layout.
include(GNUInstallDirs)
install(TARGETS ${TONBPLOT_TARGET}
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}
        BUNDLE DESTINATION ${CMAKE_BINARY_DIR}
)

# On Windows/macOS with Qt plugins, consider deployment tools after build/install:
# - windeployqt (Windows)
# - macdeployqt (macOS)

# ----- Finalize Qt target ----
qt_finalize_executable(${TONBPLOT_TARGET})