project(motor-manager VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core)

set(PROJECT_SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
)
