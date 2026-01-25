# libs/cad/CMakeLists.txt
add_library(TonbCAD)
add_library(Tonb::CAD ALIAS TonbCAD)

if (TONB_WITH_OCCT)

#    # 1) Prefer official CONFIG package with components
#    #    (vcpkg, upstream installs, some distros)
#    find_package(OpenCASCADE CONFIG QUIET
#            COMPONENTS FoundationClasses ModelingData ModelingAlgorithms Visualization DataExchange)
#
#    if (NOT OpenCASCADE_FOUND)
#        # 2) Fallback to legacy find-module that populates *_LIBRARIES / *_INCLUDE_DIR
#        find_package(OpenCASCADE QUIET)
#    endif()
#
#    set(OCCT_LIBS "")
#
#    if (TARGET OpenCASCADE::FoundationClasses
#            AND TARGET OpenCASCADE::ModelingData
#            AND TARGET OpenCASCADE::ModelingAlgorithms
#            AND TARGET OpenCASCADE::Visualization
#            AND TARGET OpenCASCADE::DataExchange)
#
#        # Aggregate high-level targets (Debian/Ubuntu or modern exports)
#        list(APPEND OCCT_LIBS
#                OpenCASCADE::FoundationClasses
#                OpenCASCADE::ModelingData
#                OpenCASCADE::ModelingAlgorithms
#                OpenCASCADE::Visualization
#                OpenCASCADE::DataExchange)
#
#    elseif (OpenCASCADE_FOUND AND OpenCASCADE_LIBRARIES)
#        # Legacy find-module variables
#        target_include_directories(TonbCAD PUBLIC ${OpenCASCADE_INCLUDE_DIR})
#        list(APPEND OCCT_LIBS ${OpenCASCADE_LIBRARIES})
#
#    else()
#        # 3) Last resort: tolerate both naming families for per-toolkit libs
#        #    Works with Ubuntu exports (TKIGES/TKSTEP*) and newer TKDE* names.
#        set(_OCCT_CORE
#                TKernel TKG2d TKG3d TKMath TKBRep TKGeomBase TKGeomAlgo TKTopAlgo TKPrim)
#
#        set(_OCCT_XS_CANDIDATES
#                OpenCASCADE::DataExchange
#                OpenCASCADE::TKDEIGES OpenCASCADE::TKDESTEP OpenCASCADE::TKXSBase
#                OpenCASCADE::TKIGES   OpenCASCADE::TKSTEP    OpenCASCADE::TKSTEPAttr
#                OpenCASCADE::TKSTEPBase OpenCASCADE::TKSTEP209 OpenCASCADE::TKSTEPCAF
#                TKDEIGES TKDESTEP TKXSBase
#                TKIGES   TKSTEP    TKSTEPAttr TKSTEPBase TKSTEP209 TKSTEPCAF)
#
#        # Collect core
#        foreach(lib ${_OCCT_CORE})
#            if (TARGET OpenCASCADE::${lib})
#                list(APPEND OCCT_LIBS OpenCASCADE::${lib})
#            elseif (TARGET ${lib})
#                list(APPEND OCCT_LIBS ${lib})
#            endif()
#        endforeach()
#
#        # Collect at least one data-exchange lib
#        set(_found_xs FALSE)
#        foreach(lib ${_OCCT_XS_CANDIDATES})
#            if (TARGET ${lib})
#                list(APPEND OCCT_LIBS ${lib})
#                set(_found_xs TRUE)
#            endif()
#        endforeach()
#
#        if (NOT OCCT_LIBS OR NOT _found_xs)
#            message(FATAL_ERROR
#                    "OCCT data-exchange toolkits not found. Your OCCT export may use "
#                    "legacy names (TKIGES/TKSTEP*) or the aggregate OpenCASCADE::DataExchange. "
#                    "Install a build that includes Data Exchange or set OpenCASCADE_DIR.")
#        endif()
#    endif()
#
#    target_link_libraries(TonbCAD PUBLIC ${OCCT_LIBS})
#
#    # Small adapter interface target; keep robust for both CONFIG and legacy modes
#    add_library(TonbCADOcctAdapters INTERFACE)
#    add_library(Tonb::CADOcctAdapters ALIAS TonbCADOcctAdapters)
#
#    if (TARGET OpenCASCADE::FoundationClasses)
#        target_link_libraries(TonbCADOcctAdapters INTERFACE Tonb::CAD OpenCASCADE::FoundationClasses)
#    elseif (OpenCASCADE_FOUND AND OpenCASCADE_LIBRARIES)
#        target_link_libraries(TonbCADOcctAdapters INTERFACE Tonb::CAD ${OpenCASCADE_LIBRARIES})
#        target_include_directories(TonbCADOcctAdapters INTERFACE ${OpenCASCADE_INCLUDE_DIR})
#    else()
#        # Last-resort: try plain TKernel when neither of the above is available
#        if (TARGET TKernel)
#            target_link_libraries(TonbCADOcctAdapters INTERFACE Tonb::CAD TKernel)
#        else()
#            message(FATAL_ERROR "Cannot wire TonbCADOcctAdapters: no OCCT core target visible.")
#        endif()
#    endif()
#
#    target_compile_definitions(TonbCADOcctAdapters INTERFACE TONB_HAS_OCCT_ADAPTERS=1)
#
#    install(TARGETS TonbCADOcctAdapters EXPORT TonbTargets)

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

    # Prefer aggregate component targets on Debian/Ubuntu,
    # fall back to per-toolkit names if available (vcpkg, upstream builds).
    set(OCCT_LIBS)

    # Aggregate targets available on Ubuntu (24.04):
    if (TARGET OpenCASCADE::FoundationClasses
        AND TARGET OpenCASCADE::ModelingData
        AND TARGET OpenCASCADE::ModelingAlgorithms
        AND TARGET OpenCASCADE::Visualization
        AND TARGET OpenCASCADE::DataExchange)

        list(APPEND OCCT_LIBS
            OpenCASCADE::FoundationClasses
            OpenCASCADE::ModelingData
            OpenCASCADE::ModelingAlgorithms
            OpenCASCADE::Visualization
            OpenCASCADE::DataExchange)

    else ()
        # Per-toolkit targets (common with vcpkg / official builds)
        # Core toolkits
        set(OCCT_CORE
                TKGeomBase TKGeomAlgo TKernel TKG2d TKG3d TKMath TKBRep TKTopAlgo TKPrim TKXSBase)

        # Data exchange: some of these may be missing on Linux (e.g. TKDEIGES)
        set(OCCT_XS
                TKDEIGES TKDESTEP
                TKIGES TKSTEP TKSTEPAttr TKSTEPBase TKSTEP209 TKSTEPCAF)

        # Collect core toolkits
#        foreach(lib ${OCCT_CORE})
#            if (TARGET OpenCASCADE::${lib})
#                list(APPEND OCCT_LIBS OpenCASCADE::${lib})
#            elseif (TARGET ${lib})
#                list(APPEND OCCT_LIBS ${lib})
#            elseif (WIN32)
#                # On Windows keep behaviour strict
#                message(FATAL_ERROR "OCCT toolkit target not found: ${lib}")
#            endif()
#        endforeach()
#
#        # Collect at least one data-exchange toolkit
#        set(_found_xs FALSE)
#        foreach(lib ${OCCT_XS})
#            if (TARGET OpenCASCADE::${lib})
#                list(APPEND OCCT_LIBS OpenCASCADE::${lib})
#                set(_found_xs TRUE)
#            elseif (TARGET ${lib})
#                list(APPEND OCCT_LIBS ${lib})
#                set(_found_xs TRUE)
#            elseif (WIN32)
#                # On Windows we still want all of them present
#                message(FATAL_ERROR "OCCT toolkit target not found: ${lib}")
#            endif()
#        endforeach()
#
#        # Final sanity check (both platforms)
#        if (NOT OCCT_LIBS OR NOT _found_xs)
#            message(FATAL_ERROR
#                    "OCCT data-exchange toolkits not found. Your OCCT export may use "
#                    "different names (TKIGES/TKSTEP* or aggregate OpenCASCADE::DataExchange). "
#                    "Install a build that includes Data Exchange or set OpenCASCADE_DIR.")
#        endif()
        # Collect core toolkits
        foreach(lib ${OCCT_CORE})
            if (TARGET OpenCASCADE::${lib})
                list(APPEND OCCT_LIBS OpenCASCADE::${lib})
            elseif (TARGET ${lib})
                list(APPEND OCCT_LIBS ${lib})
            else()
                # Try to find the raw library by name (Ubuntu style)
                find_library(_occt_${lib}_LIB NAMES ${lib})
                if (_occt_${lib}_LIB)
                    list(APPEND OCCT_LIBS ${_occt_${lib}_LIB})
                endif()
            endif()
        endforeach()

        # Collect at least one data-exchange toolkit
        set(_found_xs FALSE)
        foreach(lib ${OCCT_XS})
            if (TARGET OpenCASCADE::${lib})
                list(APPEND OCCT_LIBS OpenCASCADE::${lib})
                set(_found_xs TRUE)
            elseif (TARGET ${lib})
                list(APPEND OCCT_LIBS ${lib})
                set(_found_xs TRUE)
            else()
                find_library(_occt_${lib}_LIB NAMES ${lib})
                if (_occt_${lib}_LIB)
                    list(APPEND OCCT_LIBS ${_occt_${lib}_LIB})
                    set(_found_xs TRUE)
                endif()
            endif()
        endforeach()

        if (NOT OCCT_LIBS OR NOT _found_xs)
            message(FATAL_ERROR
                    "OCCT data-exchange toolkits not found. "
                    "Checked core: ${OCCT_CORE}, XS: ${OCCT_XS}. "
                    "Make sure libocct-data-exchange-dev (or equivalent) is installed.")
        endif()
    endif ()

    target_link_libraries(TonbCAD PUBLIC ${OCCT_LIBS})
    add_library(TonbCADOcctAdapters INTERFACE)
    add_library(Tonb::CADOcctAdapters ALIAS TonbCADOcctAdapters)
    target_link_libraries(TonbCADOcctAdapters INTERFACE Tonb::CAD OpenCASCADE::FoundationClasses)
    target_compile_definitions(TonbCADOcctAdapters INTERFACE TONB_HAS_OCCT_ADAPTERS=1)

    # Install the interface target
    install(TARGETS TonbCADOcctAdapters EXPORT TonbTargets)

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