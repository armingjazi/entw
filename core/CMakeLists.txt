add_library(entw_core src/Report.cpp src/ReportFactory src/TestCase.cpp)

target_include_directories(entw_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ifc)

target_include_directories(entw_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc)

