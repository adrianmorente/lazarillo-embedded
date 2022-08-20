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

set(COMPILE_MODE d)
lzr_set_compile_mode()
lzr_set_compilation_flags()

# CMake path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Particular installation of Qt5
set(Qt5DIR                "/usr/local/Qt-5.15.5/lib/cmake/Qt5")
set(Qt5Core_DIR           "/usr/local/Qt-5.15.5/lib/cmake/Qt5Core")
set(Qt5Qml_DIR            "/usr/local/Qt-5.15.5/lib/cmake/Qt5Qml")
set(Qt5Quick_DIR          "/usr/local/Qt-5.15.5/lib/cmake/Qt5Quick")
set(Qt5QuickControls2_DIR "/usr/local/Qt-5.15.5/lib/cmake/Qt5QuickControls2")
set(Qt5LinguistTools_DIR  "/usr/local/Qt-5.15.5/lib/cmake/Qt5LinguistTools")
set(Qt5Mqtt_DIR           "/usr/local/Qt-5.15.5/lib/cmake/Qt5Mqtt")
set(Qt5WebSockets_DIR     "/usr/local/Qt-5.15.5/lib/cmake/Qt5WebSockets")
set(QT_QMAKE_EXECUTABLE   "/usr/local/Qt-5.15.5/bin/qmake")

set(MODULE_LIST
  lazarillo-hmi
  lazarillo-utils
  messages-definition
  serialization
  service-base
  web-gateway
)

foreach (target ${MODULE_LIST})
  message("Adding module: ${target}")
  add_subdirectory(${target})
endforeach()

# configure installation scripts
# generate package
