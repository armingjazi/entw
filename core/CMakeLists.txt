add_library(entw_core src/Report.cpp src/TestCase.cpp src/Test.cpp src/Result.cpp)

target_include_directories(entw_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ifc)

target_include_directories(entw_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc)

