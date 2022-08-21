cmake_minimum_required(VERSION 3.16)

project(lazarillo-hmi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Qml LinguistTools REQUIRED)

set(TS_FILES lazarillo-hmi_es_ES.ts)

set(_include_dir inc/lazarillo-hmi)

set(PROJECT_SOURCES
  ${_include_dir}/service.h
  src/utils/style.cpp
  src/utils/style.h
  src/main.cpp
  src/service.cpp
  gui/qml.qrc
  gui/img.qrc
  ${TS_FILES}
)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<OR:$<CONFIG:Debug>,
  $<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt5::Core
  Qt5::Quick
  Qt5::QuickControls2
  Qt5::Qml
  service-base
)
