project(serialization VERSION 1.0.0 LANGUAGES CXX)

set(_include_dir inc/serialization)

set(PROJECT_SOURCES
    ${_include_dir}/deserializer.h
    ${_include_dir}/serializable.h
    ${_include_dir}/serializer.h
    src/deserializer.cpp
    src/serializer.cpp
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

lzr_link_json(${PROJECT_NAME})
lzr_link_qt(${PROJECT_NAME})
lzr_link_redis(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PUBLIC
    lazarillo-utils
)
