cmake_minimum_required(VERSION 3.16)

project(service-base VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Widgets)

set(_include_dir inc/service-base)

set(PROJECT_SOURCES
  ${_include_dir}/service_base.h
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PRIVATE inc)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
