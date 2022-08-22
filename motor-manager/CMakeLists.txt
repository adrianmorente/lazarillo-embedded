project(motor-manager VERSION 1.0 LANGUAGES CXX)

set(PROJECT_SOURCES
    src/main.cpp
)

lzr_link_qt(${PROJECT_NAME})
lzr_link_systemd(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    messages-definition
    service-base
)
