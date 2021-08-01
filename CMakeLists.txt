cmake_minimum_required(VERSION 3.10)

project(entw VERSION "0.1")

set(CMAKE_CXX_STANDARD 14)

add_library(entw INTERFACE)

target_include_directories(entw INTERFACE include/)

add_subdirectory(test)

target_sources(entw INTERFACE "$<BUILD_INTERFACE:${detail_header_files};${header_files}>")