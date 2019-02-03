add_executable(run_all_tests BareTestCase.cpp)

target_link_libraries(run_all_tests gtest gmock gtest_main)
target_link_libraries(run_all_tests entw_core)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)