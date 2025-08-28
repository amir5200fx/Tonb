# This file lives in tests/system/

add_executable(io_vtk_tests
        test_vtk_quad_surface_mesh_io.cxx
)

target_link_libraries(io_vtk_tests PRIVATE
        TonbIO
        GTest::gtest_main
        Threads::Threads
)

# If test sources need to include headers from the repo root (already done above),
# you can add extra include dirs here as well if needed:
# target_include_directories(system_task_tests PRIVATE ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(io_vtk_tests)