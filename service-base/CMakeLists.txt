cmake_minimum_required(VERSION 3.16)

project(service-base VERSION 1.0.0 LANGUAGES CXX)

set(_include_dir inc/service-base)

set(PROJECT_SOURCES
  ${_include_dir}/service_base.h
  src/service_base.cpp
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

lzr_link_qt(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
