add_executable(test_cad2d_validate
        validate_face_tests.cxx
        validate_halfedge_tests.cxx
        validate_shape_tests.cxx
        validate_wire_tests.cxx
        geom_curve_store_tests.cxx
        halfedge_builder_geometry_tests.cxx
        halfedge_geometry_validation_tests.cxx
        edge_builder_tests.cxx
        edge_validation_tests.cxx
        wire_length_tests.cxx
        face_area_tests.cxx
)

target_link_libraries(test_cad2d_validate PRIVATE
        Tonb::CAD2d
        GTest::gtest
        GTest::gtest_main
)

target_include_directories(test_cad2d_validate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME test_cad2d_validate COMMAND test_cad2d_validate)
