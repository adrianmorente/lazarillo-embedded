project(service-base VERSION 1.0 LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Mosquitto IMPORTED_TARGET libmosquitto REQUIRED)

set(PROJECT_SOURCES
  inc/service_base.h
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
  PkgConfig::Mosquitto
)
