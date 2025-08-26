# libs/system/CMakeLists.txt
add_library(TonbBase)
add_library(Tonb::Base ALIAS TonbBase)

# My library target
set_target_properties(TonbBase PROPERTIES
        VERSION ${TONB_SEMVER_CORE}         # e.g. 0.18.0 -> libTonbBase.so.0.18.0
        SOVERSION ${TONB_SEMVER_MAJOR}      # e.g. 0      -> libTonbBase.so.0
)

target_sources(TonbBase
        PRIVATE
        src/tools.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/base/module.hxx
        include/tonb/base/index_tag.hxx
        include/tonb/base/precision.hxx
        include/tonb/base/index_types.hxx
        include/tonb/base/range.hxx
        include/tonb/base/range_i.hxx
        include/tonb/base/tools.hxx
)

if (TNB_WITH_CEREAL)
    find_package(cereal CONFIG REQUIRED)  # header-only
    target_link_libraries(TonbBase PUBLIC cereal::cereal)
else ()
    if (POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif ()
    find_package(Boost CONFIG REQUIRED COMPONENTS serialization)  # add components you need
    target_link_libraries(TonbBase PUBLIC Boost::serialization)
    if (MSVC)
        target_compile_definitions(TonbBase PUBLIC BOOST_ALL_NO_LIB)
    endif ()
endif ()

target_include_directories(TonbBase PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(TonbBase
        PUBLIC Tonb::System     # headers depend on system
)

set_target_properties(TonbBase PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO)

target_compile_features(TonbBase PUBLIC cxx_std_20)

# When building the shared lib, this flag marks we are *producing* the symbols
target_compile_definitions(TonbBase PRIVATE TNBBASE_EXPORTS)

# If you flip to static build, make exports no-ops for consumers
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbGeometry PUBLIC TNBBASE_STATIC_MODULE)
endif ()