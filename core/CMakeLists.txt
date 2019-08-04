add_library(entw_core src/TestCase.cpp inc/Expect.h inc/Test.h)

target_include_directories(entw_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc)