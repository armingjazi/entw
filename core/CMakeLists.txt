set(entw_core_src
        src/Bare.cpp inc/Bare.h)

add_library(entw_core ${entw_core_src})

target_include_directories(entw_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc)