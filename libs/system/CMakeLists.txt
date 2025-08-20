# libs/system/CMakeLists.txt
add_library(TnbSystem)
add_library(tonb::system ALIAS TnbSystem)

target_sources(TnbSystem
        PRIVATE
        src/task.cxx
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

if (TNB_WITH_CEREAL)
    find_package(cereal CONFIG REQUIRED)  # header-only
    target_link_libraries(TnbSystem PUBLIC cereal::cereal)
else ()
    if (POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif ()
    find_package(Boost REQUIRED COMPONENTS serialization)
    target_link_libraries(TnbSystem PUBLIC Boost::serialization)
    if (MSVC)
        target_compile_definitions(TnbSystem PUBLIC BOOST_ALL_NO_LIB)
    endif ()
endif ()

target_include_directories(TnbSystem PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

# Hide everything by default on GCC/Clang; only TNBSYSTEM_EXPORT is visible
set_target_properties(TnbSystem PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

target_compile_features(TnbSystem PUBLIC cxx_std_20)

# When building the shared lib, this flag marks we are *producing* the symbols
target_compile_definitions(TnbSystem PRIVATE TNBSYSTEM_EXPORTS)

# If you flip to static build, make exports no-ops for consumers
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TnbSystem PUBLIC TNBSYSTEM_STATIC_MODULE)
endif ()


install(TARGETS TnbSystem
        EXPORT tonbTargets
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})