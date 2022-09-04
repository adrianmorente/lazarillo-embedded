cmake_minimum_required(VERSION 3.16)

project(lazarillo-hmi VERSION 0.1 LANGUAGES CXX)

# set(TS_FILES i18n/lazarillo-hmi_es_ES.ts)

set(_include_dir inc/lazarillo-hmi)

set(PROJECT_SOURCES
  ${_include_dir}/utils/style.h
  ${_include_dir}/service.h
  src/message_receivers/event_reboot_receiver.cpp
  src/message_receivers/event_reboot_receiver.h  
  src/utils/style.cpp
  src/main.cpp
  src/service.cpp
  gui/qml.qrc
  gui/img.qrc
  # ${TS_FILES}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

lzr_link_qt(${PROJECT_NAME})
lzr_link_systemd(${PROJECT_NAME})

# qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
  messages-definition
  messaging-broker
  serialization
  service-base
)
