cmake_minimum_required(VERSION 3.16)

project(messaging-broker VERSION 1.0.0 LANGUAGES CXX)

set(_include_dir inc/messaging-broker)

set(PROJECT_SOURCES
    ${_include_dir}/broker.h
    ${_include_dir}/msg_publisher.h
    ${_include_dir}/i_msg_receiver.h
    src/broker.cpp
    src/msg_publisher.cpp
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

lzr_link_mqtt(${PROJECT_NAME})
lzr_link_qt(${PROJECT_NAME})
lzr_link_systemd(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
    messages-definition
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
