# libs/io/CMakeLists.txt
add_library(TonbIO)
add_library(Tonb::IO ALIAS TonbIO)

if (TONB_WITH_OCCT)
    # Prefer the config package (vcpkg, official builds)
    find_package(OpenCASCADE CONFIG REQUIRED)
    if (NOT OpenCASCADE_FOUND)
        find_package(OpenCASCADE QUIET)  # provides OpenCASCADE_LIBRARIES/INCLUDE_DIR
    endif ()

    if (NOT OpenCASCADE_FOUND)
        message(FATAL_ERROR "OpenCASCADE not found. Install with:
        - vcpkg: vcpkg install opencascade
        - Ubuntu: sudo apt-get install libocct-dev
        - Windows: vcpkg install opencascade:x64-windows"
        )
    endif ()

    set(OCCT_LIBS)
    foreach (lib TKGeomAlgo TKernel TKG2d TKG3d TKMath)
        if (TARGET OpenCASCADE::${lib})
            list(APPEND OCCT_LIBS OpenCASCADE::${lib})
        elseif(TARGET ${lib})
            list(APPEND OCCT_LIBS ${lib})
        else ()
            message(FATAL_ERROR "OCCT toolkit target not found: ${lib}")
        endif ()
    endforeach ()
    target_link_libraries(TonbIO PRIVATE ${OCCT_LIBS})
    add_library(TonbIOOcctAdapters INTERFACE)
    add_library(Tonb::IOOcctAdapters ALIAS TonbIOOcctAdapters)
    target_link_libraries(TonbIOOcctAdapters INTERFACE Tonb::IO OpenCASCADE::FoundationClasses)
    target_compile_definitions(TonbIOOcctAdapters INTERFACE TONB_HAS_OCCT_ADAPTERS=1)

    # Install the interface target
    install(TARGETS TonbIOOcctAdapters EXPORT TonbTargets)

    # Install the adapter header only when ON
#    install(FILES include/tonb/io/occt/core/adapters.hxx
#            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tonb/io/occt
#    )
endif ()

# My library target
set_target_properties(TonbIO PROPERTIES
        VERSION ${TONB_SEMVER_CORE}         # e.g. 0.18.0 -> libTonbIO.so.0.18.0
        SOVERSION ${TONB_SEMVER_MAJOR}      # e.g. 0      -> libTonbIO.so.0
)

target_sources(TonbIO
        PRIVATE
        src/vtk/mesh_writer.cxx
        src/vtk/mesh_reader.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/io/module.hxx
        include/tonb/io/vtk/mesh_writer.hxx
        include/tonb/io/vtk/mesh_reader.hxx
)

# Backend-specific sources
#target_sources(TonbIO PRIVATE
#        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/bbox.cxx>
#        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/bbox.cxx>
#)

if (TNB_WITH_CEREAL)
    find_package(cereal CONFIG REQUIRED)  # header-only
    target_link_libraries(TonbIO PUBLIC cereal::cereal)
else ()
    if (POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif ()
    find_package(Boost CONFIG REQUIRED COMPONENTS serialization)  # add components you need
    target_link_libraries(TonbIO PUBLIC Boost::serialization)
    if (MSVC)
        target_compile_definitions(TonbIO PUBLIC BOOST_ALL_NO_LIB)
    endif ()
endif ()

# ---- VTK ------------------
# ---- VTK (works with 8.2 and 9.x) ---------------------------------
# First, probe VTK without components to learn its version
find_package(VTK QUIET)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found")
endif()

# Surface major version for optional source guards
if (DEFINED VTK_MAJOR_VERSION)
    set(TONB_VTK_MAJOR ${VTK_MAJOR_VERSION})
elseif (DEFINED VTK_VERSION)
    string(REGEX MATCH "^[0-9]+" TONB_VTK_MAJOR "${VTK_VERSION}")
endif()
if (TONB_VTK_MAJOR)
    target_compile_definitions(TonbIO PUBLIC TONB_VTK_MAJOR=${TONB_VTK_MAJOR})
endif()

if (VTK_VERSION VERSION_LESS "8.90.0")
    # ----- Legacy VTK 8.x style (Windows: 8.2) -----
    message(STATUS "Configuring for legacy VTK ${VTK_VERSION}")
    # Re-run REQUIRED without components (VTK 8.x component names differ)
    find_package(VTK REQUIRED)
    include(${VTK_USE_FILE})
    target_link_libraries(TonbIO PRIVATE ${VTK_LIBRARIES})
else()
    # ----- Modern VTK 9.x style (Linux: 9.5) -----
    message(STATUS "Configuring for modern VTK ${VTK_VERSION}")
    # Now we can safely request the exact modules we use
    find_package(VTK REQUIRED COMPONENTS
            CommonCore
            CommonDataModel
            FiltersCore
            IOXML
    )
    target_link_libraries(TonbIO PUBLIC
            VTK::CommonCore
            VTK::CommonDataModel
            VTK::FiltersCore
            VTK::IOXML
    )
    if (COMMAND vtk_module_autoinit)
        vtk_module_autoinit(TARGETS TonbIO MODULES ${VTK_LIBRARIES})
    endif()
endif()

#[[find_package(VTK 9.0 CONFIG REQUIRED COMPONENTS
        CommonCore
        CommonDataModel
        FiltersCore
        IOXML
)

target_link_libraries(TonbIO
        PRIVATE
        VTK::CommonCore
        VTK::CommonDataModel
        VTK::FiltersCore
        VTK::IOXML
)]]

target_include_directories(TonbIO PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(TonbIO
        PUBLIC Tonb::Base
)

set_target_properties(TonbIO PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO)

target_compile_features(TonbIO PUBLIC cxx_std_20)

# When building the shared lib, this flag marks we are *producing* the symbols
target_compile_definitions(TonbIO PRIVATE TNBIO_EXPORTS)

# If you flip to static build, make exports no-ops for consumers
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbIO PUBLIC TNBIO_STATIC_MODULE)
endif ()