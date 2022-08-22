cmake_minimum_required(VERSION 3.16)

project(lazarillo-utils VERSION 1.0.0 LANGUAGES CXX)

set(_include_dir inc/lazarillo-utils)

set(PROJECT_SOURCES
${_include_dir}/datetime.h
src/datetime.cpp
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

lzr_link_qt(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PRIVATE src)
