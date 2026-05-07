# libs/system/CMakeLists.txt
add_library(TonbSystem)
add_library(Tonb::System ALIAS TonbSystem)

# My library target
set_target_properties(TonbSystem PROPERTIES
        VERSION ${TONB_SEMVER_CORE}         # e.g. 0.18.0 -> libTonbSystem.so.0.18.0
        SOVERSION ${TONB_SEMVER_MAJOR}      # e.g. 0      -> libTonbSystem.so.0
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/tonb/system/version.hxx.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/tonb/system/version.hxx
        @ONLY
)

target_sources(TonbSystem
        PRIVATE
        src/task.cxx
        src/log.cxx
        src/log_anchors.cxx
        src/serialization/io.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/system/serialization/default_archive.hxx
        include/tonb/system/serialization/type_tag.hxx
        include/tonb/system/serialization/wire.hxx
        include/tonb/system/serialization/io.hxx
        include/tonb/system/verbosity.hxx
        include/tonb/system/module.hxx
        include/tonb/system/run_context.hxx
        include/tonb/system/task.hxx
        include/tonb/system/log.hxx
)

if (TONB_WITH_CEREAL)
    find_package(cereal CONFIG REQUIRED)  # header-only
    target_link_libraries(TonbSystem PUBLIC cereal::cereal)
else ()
    if (POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif ()
    find_package(Boost CONFIG REQUIRED COMPONENTS serialization)  # add components you need
    target_link_libraries(TonbSystem PUBLIC Boost::serialization)
    if (MSVC)
        target_compile_definitions(TonbSystem PUBLIC BOOST_ALL_NO_LIB)
    endif ()
endif ()

target_include_directories(TonbSystem PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>)

set_target_properties(TonbSystem PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO)

target_compile_features(TonbSystem PUBLIC cxx_std_20)

# When building the shared lib, this flag marks we are *producing* the symbols
target_compile_definitions(TonbSystem PRIVATE TNBSYSTEM_EXPORTS)

# If you flip to static build, make exports no-ops for consumers
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbSystem PUBLIC TNBSYSTEM_STATIC_MODULE)
endif ()