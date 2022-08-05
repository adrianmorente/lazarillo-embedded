cmake_minimum_required(VERSION 3.16)

project(messages-definition VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(PROJECT_SOURCES
    inc/base_message.h
    inc/event_reboot.h
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
