# libs/mesh/CMakeLists.txt
add_library(TonbMesh)
add_library(Tonb::Mesh ALIAS TonbMesh)

set_target_properties(TonbMesh PROPERTIES
        VERSION ${TONB_SEMVER_CORE}
        SOVERSION ${TONB_SEMVER_MAJOR}
)

target_sources(TonbMesh
        PRIVATE
        src/tmp.cxx
        src/mesh/aft2d/topology.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/mesh/core/handles.hxx
        include/tonb/mesh/topology3d/volume_mesh.hxx
        include/tonb/mesh/topology3d/private/volume_mesh_imp.hxx
        include/tonb/mesh/aft2d/topology.hxx
)

target_link_libraries(TonbMesh
        PUBLIC Tonb::Base Tonb::Geometry
)

