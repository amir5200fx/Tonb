add_executable(test_shell_cad2d_validate
        shell_session_tests.cxx
)

target_link_libraries(test_shell_cad2d_validate PRIVATE
        Tonb::CAD2dShell
        GTest::gtest
        GTest::gtest_main
)

target_include_directories(test_shell_cad2d_validate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME test_shell_cad2d_validate COMMAND test_shell_cad2d_validate)
