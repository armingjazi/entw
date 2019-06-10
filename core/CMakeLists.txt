add_library(entw_core src/WasRun.cpp inc/WasRun.h src/TestCase.cpp)

target_include_directories(entw_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc)