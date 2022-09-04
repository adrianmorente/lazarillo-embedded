cmake_minimum_required(VERSION 3.16)
project(lazarillo-embedded)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CPack)
include(GNUInstallDirs)
include(ProjectSetup)

set(CPACK_PACKAGE_NAME "Lazarillo Embedded")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

# CMake path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(COMPILE_MODE d)
lzr_set_compile_mode()
lzr_set_compilation_flags()
lzr_setup_qt()

set(MODULE_LIST
  lazarillo-hmi
  lazarillo-utils
  messages-definition
  messaging-broker
  # motor-manager
  serialization
  service-base
  # web-gateway
)

foreach (target ${MODULE_LIST})
  message("Adding module: ${target}")
  add_subdirectory(${target})
endforeach()

# configure installation scripts
# generate package
