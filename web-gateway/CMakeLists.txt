project(web-gateway VERSION 0.1 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core WebSockets REQUIRED)

set(PROJECT_SOURCES
  inc/websocket_client.h
  src/main.cpp
  src/websocket_client.cpp
  ${TS_FILES}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<OR:$<CONFIG:Debug>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  messages-definition
  service-base
  Qt5::Core
  Qt5::WebSockets
)
