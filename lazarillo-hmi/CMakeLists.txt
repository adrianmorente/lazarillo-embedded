project(lazarillo-hmi VERSION 0.1 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Qml LinguistTools REQUIRED)

set(TS_FILES lazarillo-hmi_es_ES.ts)

set(PROJECT_SOURCES
  src/utils/style.cpp
  src/utils/style.h
  src/main.cpp
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
)
