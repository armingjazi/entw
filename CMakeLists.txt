cmake_minimum_required(VERSION 3.10)

project(entw VERSION "0.1")

set(CMAKE_CXX_STANDARD 14)

include(GNUInstallDirs)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE include)

add_subdirectory(test)

target_sources(${PROJECT_NAME} INTERFACE "$<BUILD_INTERFACE:${detail_header_files};${header_files}>")