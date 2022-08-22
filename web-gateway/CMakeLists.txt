project(web-gateway VERSION 0.1 LANGUAGES CXX)

set(_include_dir inc/web-gateway)

set(PROJECT_SOURCES
  ${_include_dir}/websocket_server.h
  src/main.cpp
  src/websocket_server.cpp
  ${TS_FILES}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

lzr_link_qt(${PROJECT_NAME})
lzr_link_systemd(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<OR:$<CONFIG:Debug>
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)

target_link_libraries(${PROJECT_NAME} PRIVATE
  messages-definition
  service-base
)
