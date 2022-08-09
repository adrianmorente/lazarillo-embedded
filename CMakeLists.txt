cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(ProjectSetup)

set(COMPILE_MODE d)
lzr_set_compile_mode()
lzr_set_compilation_flags()

project("lazarillo_sw")
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
message("\tPROJECT: ${PROJECT_NAME}")

set(module_list
  lazarillo-hmi
  messages-definition
  service-base
  web-gateway
)

foreach (target ${module_list})
  message("Adding module: ${target}")
  add_subdirectory(${target})
endforeach()

# configure installation scripts
# generate package
