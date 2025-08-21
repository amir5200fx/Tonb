# libs/system/CMakeLists.txt
add_library(TnbSystem)
add_library(tonb::system ALIAS TnbSystem)

# My library target
set_target_properties(TnbSystem PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/tonb/system/version.hxx.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/tonb/system/version.hxx
        @ONLY
)

target_sources(TnbSystem
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
        include/tonb/system/log.hxx-backup
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>)

# Hide everything by default on GCC/Clang; only TNBSYSTEM_EXPORT is visible
set_target_properties(TnbSystem PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO)

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

# Install the generated header, too:
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/include/tonb/system/version.hxx
        DESTINATION include/tonb/system
)