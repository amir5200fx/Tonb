# This file lives in tests/system/

add_executable(system_task_tests
        test_task.cxx
)

target_link_libraries(system_task_tests PRIVATE
        TonbSystem
        GTest::gtest_main
        Threads::Threads
)

# If test sources need to include headers from the repo root (already done above),
# you can add extra include dirs here as well if needed:
# target_include_directories(system_task_tests PRIVATE ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(system_task_tests)
