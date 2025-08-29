# libs/cad/CMakeLists.txt
add_library(TonbCAD)
add_library(Tonb::CAD ALIAS TonbCAD)

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
    foreach (lib TKGeomBase TKGeomAlgo TKernel TKG2d TKG3d TKMath TKBRep TKTopAlgo TKPrim)
        if (TARGET OpenCASCADE::${lib})
            list(APPEND OCCT_LIBS OpenCASCADE::${lib})
        elseif(TARGET ${lib})
            list(APPEND OCCT_LIBS ${lib})
        else ()
            message(FATAL_ERROR "OCCT toolkit target not found: ${lib}")
        endif ()
    endforeach ()
    target_link_libraries(TonbCAD PRIVATE ${OCCT_LIBS})
    add_library(TonbCADOcctAdapters INTERFACE)
    add_library(Tonb::CADOcctAdapters ALIAS TonbCADOcctAdapters)
    target_link_libraries(TonbCADOcctAdapters INTERFACE Tonb::CAD OpenCASCADE::FoundationClasses)
    target_compile_definitions(TonbCADOcctAdapters INTERFACE TONB_HAS_OCCT_ADAPTERS=1)

    # Install the interface target
    install(TARGETS TonbCADOcctAdapters EXPORT TonbTargets)

    # Install the adapter header only when ON
#    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/tonb/geometry/occt/adapters.hxx
#            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tonb/geometry/occt
#    )
endif ()

# My library target
set_target_properties(TonbCAD PROPERTIES
        VERSION ${TONB_SEMVER_CORE}         # e.g. 0.18.0 -> libTonbCAD.so.0.18.0
        SOVERSION ${TONB_SEMVER_MAJOR}      # e.g. 0      -> libTonbCAD.so.0
)

target_sources(TonbCAD
        PRIVATE
        src/occt/body.cxx
        src/tools.cxx
        src/occt/impl.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/cad/occt/body.hxx
        include/tonb/cad/occt/edge.hxx
        include/tonb/cad/occt/face.hxx
        include/tonb/cad/occt/location.hxx
        include/tonb/cad/occt/tools.hxx
        include/tonb/cad/point.hxx
        include/tonb/cad/vector.hxx
        include/tonb/cad/bbox.hxx
        include/tonb/cad/bbox_fwd.hxx
        include/tonb/cad/curve.hxx
        include/tonb/cad/curve_fwd.hxx
        include/tonb/cad/edge.hxx
        include/tonb/cad/edge_fwd.hxx
        include/tonb/cad/surface.hxx
        include/tonb/cad/surface_fwd.hxx
        include/tonb/cad/location.hxx
        include/tonb/cad/face.hxx
        include/tonb/cad/face_fwd.hxx
        include/tonb/cad/body.hxx
        include/tonb/cad/body_fwd.hxx
        include/tonb/cad/tools.hxx
        include/tonb/cad/module.hxx
        include/tonb/cad/axis.hxx
        include/tonb/cad/axis_fwd.hxx
)

# Backend-specific sources
target_sources(TonbCAD PRIVATE
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/body.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/body.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/edge.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/edge.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/face.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/face.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/location.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/location.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/tools.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/tools.cxx>
)

if (TNB_WITH_CEREAL)
    find_package(cereal CONFIG REQUIRED)  # header-only
    target_link_libraries(TonbCAD PUBLIC cereal::cereal)
else ()
    if (POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif ()
    find_package(Boost CONFIG REQUIRED COMPONENTS serialization)  # add components you need
    target_link_libraries(TonbCAD PUBLIC Boost::serialization)
    if (MSVC)
        target_compile_definitions(TonbCAD PUBLIC BOOST_ALL_NO_LIB)
    endif ()
endif ()

target_include_directories(TonbCAD PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(TonbCAD
        PUBLIC Tonb::Geometry
        PUBLIC Tonb::Base
        PUBLIC Tonb::System
)

set_target_properties(TonbCAD PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO)

target_compile_features(TonbCAD PUBLIC cxx_std_20)

# When building the shared lib, this flag marks we are *producing* the symbols
target_compile_definitions(TonbCAD PRIVATE TNBCAD_EXPORTS)

# If you flip to static build, make exports no-ops for consumers
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbCAD PUBLIC TNBCAD_STATIC_MODULE)
endif ()