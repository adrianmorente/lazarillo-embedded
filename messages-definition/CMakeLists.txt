cmake_minimum_required(VERSION 3.16)

project(messages-definition VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Widgets)

set(_include_dir inc)

set(PROJECT_SOURCES
    ${_include_dir}/messages-definition/base_message.h
    ${_include_dir}/messages-definition/event_connection_status.h
    ${_include_dir}/messages-definition/event_reboot.h
    ${_include_dir}/messages-definition/message_header.h
    ${_include_dir}/models/connection_status.h
    src/base_message.cpp
    src/message_header.cpp
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)

target_link_libraries(${PROJECT_NAME} PUBLIC serialization)
