# libs/numerics/CMakeLists.txt
add_library(TonbNumerics)
add_library(Tonb::Numerics ALIAS TonbNumerics)

set_target_properties(TonbNumerics PROPERTIES
        VERSION ${TONB_SEMVER_CORE}
        SOVERSION ${TONB_SEMVER_MAJOR}
)

target_sources(TonbNumerics
        PRIVATE
        src/tmp.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/numerics/bisection.hxx
        include/tonb/numerics/integration.hxx
        include/tonb/numerics/newton.hxx
)

target_link_libraries(TonbNumerics
        PUBLIC Tonb::Base
)