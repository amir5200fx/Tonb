# libs/geometry/CMakeLists.txt
add_library(TonbGeometry)
add_library(Tonb::Geometry ALIAS TonbGeometry)

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
    add_library(TonbOcctAdapters INTERFACE)
    add_library(Tonb::OcctAdapters ALIAS TonbOcctAdapters)
    target_link_libraries(TonbGeometry PRIVATE ${OCCT_LIBS})
    target_link_libraries(TonbOcctAdapters INTERFACE Tonb::Geometry)
    target_compile_definitions(TonbOcctAdapters INTERFACE TONB_HAS_OCCT_ADAPTERS=1)

    # Install the interface target
    install(TARGETS TonbOcctAdapters EXPORT TonbTargets)

    # Install the adapter header only when ON
    install(FILES include/tonb/geometry/occt/core/adapters.hxx
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tonb/geometry/occt
    )
endif ()

# My library target
set_target_properties(TonbGeometry PROPERTIES
        VERSION ${TONB_SEMVER_CORE}         # e.g. 0.18.0 -> libTonbGeometry.so.0.18.0
        SOVERSION ${TONB_SEMVER_MAJOR}      # e.g. 0      -> libTonbGeometry.so.0
)

target_sources(TonbGeometry
        PRIVATE
        src/pnt_2d.cxx
        src/pnt_3d.cxx
        src/meta/box2d.cxx
        src/meta/box3d.cxx
        src/meta/connectivity.cxx
        src/meta/quad_mesh_3d.cxx
        src/meta/meta_impl.cxx
        src/occt/impl.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/geometry/module.hxx
        include/tonb/geometry/cartesian_direction.hxx
        include/tonb/geometry/pnt_2d.hxx
        include/tonb/geometry/pnt_3d.hxx
        include/tonb/geometry/meta/box.hxx
        include/tonb/geometry/meta/box_i.hxx
        include/tonb/geometry/meta/box_2d.hxx
        include/tonb/geometry/meta/box_2d_fwd.hxx
        include/tonb/geometry/meta/box_3d.hxx
        include/tonb/geometry/meta/box_3d_fwd.hxx
        include/tonb/geometry/meta/geometry_set.hxx
        include/tonb/geometry/meta/connectivity.hxx
        include/tonb/geometry/meta/connectivity_i.hxx
        include/tonb/geometry/meta/triangulation_2d.hxx
        include/tonb/geometry/meta/triangulation_2d_fwd.hxx
        include/tonb/geometry/meta/triangulation_3d.hxx
        include/tonb/geometry/meta/triangulation_3d_fwd.hxx
        include/tonb/geometry/meta/quad_mesh_2d.hxx
        include/tonb/geometry/meta/quad_mesh_2d_fwd.hxx
        include/tonb/geometry/meta/quad_mesh_3d.hxx
        include/tonb/geometry/meta/quad_mesh_3d_fwd.hxx
        include/tonb/geometry/occt/occt.hxx
        include/tonb/geometry/occt/bbox.hxx
        include/tonb/geometry/occt/curve.hxx
        include/tonb/geometry/occt/curve_2d.hxx
        include/tonb/geometry/occt/surface.hxx
        include/tonb/geometry/occt/tools.hxx
        include/tonb/geometry/occt/point.hxx
        include/tonb/geometry/occt/point_2d.hxx
        include/tonb/geometry/occt/vector.hxx
        include/tonb/geometry/occt/vector_2d.hxx
        include/tonb/geometry/occt/axis.hxx
        include/tonb/geometry/occt/axis_2d.hxx
        include/tonb/geometry/occt/transform.hxx
        include/tonb/geometry/occt/transform_2d.hxx
        #include/tonb/geometry/occt/adapters.hxx
)

# Backend-specific sources
target_sources(TonbGeometry PRIVATE
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/bbox.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/bbox.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/curve.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/curve.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/curve_2d.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/curve_2d.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/surface.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/surface.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/tools.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/tools.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/transform.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/transform.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/transform_2d.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/transform_2d.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/point.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/point.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/point_2d.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/point_2d.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/vector.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/vector.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/vector_2d.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/vector_2d.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/axis.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/axis.cxx>
        $<$<BOOL:${TONB_WITH_OCCT}>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/axis_2d.cxx>
        $<$<NOT:$<BOOL:${TONB_WITH_OCCT}>>:${CMAKE_CURRENT_SOURCE_DIR}/src/occt/null/axis_2d.cxx>
)

if (TNB_WITH_CEREAL)
    find_package(cereal CONFIG REQUIRED)  # header-only
    target_link_libraries(TonbGeometry PUBLIC cereal::cereal)
else ()
    if (POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif ()
    find_package(Boost CONFIG REQUIRED COMPONENTS serialization)  # add components you need
    target_link_libraries(TonbGeometry PUBLIC Boost::serialization)
    if (MSVC)
        target_compile_definitions(TonbGeometry PUBLIC BOOST_ALL_NO_LIB)
    endif ()
endif ()

target_include_directories(TonbGeometry PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(TonbGeometry
        PUBLIC
        Tonb::Base
        Tonb::IO
)

set_target_properties(TonbGeometry PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO)

target_compile_features(TonbGeometry PUBLIC cxx_std_20)

# When building the shared lib, this flag marks we are *producing* the symbols
target_compile_definitions(TonbGeometry PRIVATE TNBGEOM_EXPORTS)

# If you flip to static build, make exports no-ops for consumers
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbGeometry PUBLIC TNBGEOM_STATIC_MODULE)
endif ()