# libs/cad2d/CMakeLists.txt
add_library(TonbCAD2d)
add_library(Tonb::CAD2d ALIAS TonbCAD2d)

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
    foreach (lib TKGeomBase TKGeomAlgo TKernel TKG2d TKG3d TKMath TKBRep TKTopAlgo)
        if (TARGET OpenCASCADE::${lib})
            list(APPEND OCCT_LIBS OpenCASCADE::${lib})
        elseif(TARGET ${lib})
            list(APPEND OCCT_LIBS ${lib})
        else ()
            message(FATAL_ERROR "OCCT toolkit target not found: ${lib}")
        endif ()
    endforeach ()
    target_link_libraries(TonbCAD2d PRIVATE ${OCCT_LIBS})
    add_library(TonbCAD2dOcctAdapters INTERFACE)
    add_library(Tonb::CAD2dOcctAdapters ALIAS TonbCAD2dOcctAdapters)
    target_link_libraries(TonbCAD2dOcctAdapters INTERFACE Tonb::CAD2d OpenCASCADE::FoundationClasses)
    target_compile_definitions(TonbCAD2dOcctAdapters INTERFACE TONB_HAS_OCCT_ADAPTERS=1)

    # Install the interface target
    install(TARGETS TonbCAD2dOcctAdapters EXPORT TonbTargets)

    # Install the adapter header only when ON
    #    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/tonb/geometry/occt/adapters.hxx
    #            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tonb/geometry/occt
    #    )
endif ()

# My library target
set_target_properties(TonbCAD2d PROPERTIES
        VERSION ${TONB_SEMVER_CORE}         # e.g. 0.18.0 -> libTonbCAD2d.so.0.18.0
        SOVERSION ${TONB_SEMVER_MAJOR}      # e.g. 0      -> libTonbCAD2d.so.0
)

target_sources(TonbCAD2d
        PRIVATE
        src/tools.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/cad2d/module.hxx
        include/tonb/cad2d/point.hxx
        include/tonb/cad2d/point_fwd.hxx
        include/tonb/cad2d/transform.hxx
        include/tonb/cad2d/transform_fwd.hxx
        include/tonb/cad2d/vector.hxx
        include/tonb/cad2d/vector_fwd.hxx
        include/tonb/cad2d/curve.hxx
        include/tonb/cad2d/curve_fwd.hxx
        include/tonb/cad2d/axis.hxx
        include/tonb/cad2d/axis_fwd.hxx
        include/tonb/cad2d/tools.hxx
)

# Backend-specific sources

if (TNB_WITH_CEREAL)
    find_package(cereal CONFIG REQUIRED)  # header-only
    target_link_libraries(TonbCAD2d PUBLIC cereal::cereal)
else ()
    if (POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif ()
    find_package(Boost CONFIG REQUIRED COMPONENTS serialization)  # add components you need
    target_link_libraries(TonbCAD2d PUBLIC Boost::serialization)
    if (MSVC)
        target_compile_definitions(TonbCAD2d PUBLIC BOOST_ALL_NO_LIB)
    endif ()
endif ()

target_include_directories(TonbCAD2d PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(TonbCAD2d
        PUBLIC Tonb::Geometry
        PUBLIC Tonb::Base
        PUBLIC Tonb::System
)

set_target_properties(TonbCAD2d PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO)

target_compile_features(TonbCAD2d PUBLIC cxx_std_20)

# When building the shared lib, this flag marks we are *producing* the symbols
target_compile_definitions(TonbCAD2d PRIVATE TNBCAD2D_EXPORTS)

# If you flip to static build, make exports no-ops for consumers
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbCAD2d PUBLIC TNBCAD2D_STATIC_MODULE)
endif ()