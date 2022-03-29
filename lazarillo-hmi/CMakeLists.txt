cmake_minimum_required(VERSION 3.6)

project(lazarillo-hmi VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Network Qml Quick QuickControls2 REQUIRED)
find_package(Qt5LinguistTools)

set(include_dir ${PROJECT_NAME}/include)
set(sources
    src/main.cpp
)

qt5_add_resources(QT_RESOURCES
    gui/qml.qrc
    lang.qrc
)

set(libraries
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${libraries})

# TODO: install service file
