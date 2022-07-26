cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(ProjectSetup)

set(COMPILE_MODE d)
lzr_set_compile_mode()
lzr_set_compilation_flags()

# Particular installation of Qt5
set(Qt5Core_DIR           "/usr/local/Qt-5.12.12/lib/cmake/Qt5Core")
set(Qt5Quick_DIR          "/usr/local/Qt-5.12.12/lib/cmake/Qt5Quick")
set(Qt5QuickControls2_DIR "/usr/local/Qt-5.12.12/lib/cmake/Qt5QuickControls2")
set(Qt5LinguistTools_DIR  "/usr/local/Qt-5.12.12/lib/cmake/Qt5LinguistTools")
set(Qt5WebSockets_DIR     "/usr/local/Qt-5.12.12/lib/cmake/Qt5WebSockets")
set(Qt5DIR                "/usr/local/Qt-5.12.12/lib/cmake/Qt5")
set(QT_QMAKE_EXECUTABLE   "/usr/local/Qt-5.12.12/bin/qmake")

project("lazarillo_sw")
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
message("\tPROJECT: ${PROJECT_NAME}")

set(module_list
  lazarillo-hmi
  web-gateway
)

foreach (target ${module_list})
  message("Adding module: ${target}")
  add_subdirectory(${target})
endforeach()

# configure installation scripts
# generate package
