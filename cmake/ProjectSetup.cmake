# Define needed macros

macro(lzr_set_compile_mode)
    # Compile modes:
    # r = release
    # d = debug
    if (NOT DEFINED COMPILE_MODE)
        message(FATAL_ERROR "Please specify the compile mode.")
    endif()

    if("${COMPILE_MODE}" STREQUAL "d")
        message("Build mode: Debug")
        set(CMAKE_BUILD_TYPE Debug)
    elseif("{COMPILE_MODE}" STREQUAL "r")
        message("Build mode: Release")
        set(CMAKE_BUILD_TYPE Release)
    else()
        message(FATAL_ERROR "Invalid compilation mode. Must be 'r' (release) or 'd' (debug)")
    endif()
endmacro(lzr_set_compile_mode)

macro(lzr_set_compilation_flags)
    set(CMAKE_INCLUDE_CURRENT_DIR   YES)
    set(CMAKE_AUTOUIC               YES)
    set(CMAKE_AUTOMOC               YES)
    set(CMAKE_AUTORCC               YES)
    set(CMAKE_CXX_STANDARD          17)
    set(CMAKE_CXX_STANDARD_REQUIRED YES)
    set(CMAKE_CXX_EXTENSIONS        NO)
    set(CMAKE_CXX_FLAGS             "-Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG       "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE     "-Os -s")

    if(CMAKE_BUILD_TYPE MATCHES Release)
        add_compile_definitions(NDEBUG)
    else()
        add_compile_definitions(DEBUG)
    endif()
endmacro()

# Particular installation of Qt5
macro(lzr_setup_qt)
    set(Qt5DIR                "/usr/local/Qt-5.15.5/lib/cmake/Qt5")
    set(Qt5Core_DIR           "/usr/local/Qt-5.15.5/lib/cmake/Qt5Core")
    set(Qt5Qml_DIR            "/usr/local/Qt-5.15.5/lib/cmake/Qt5Qml")
    set(Qt5Quick_DIR          "/usr/local/Qt-5.15.5/lib/cmake/Qt5Quick")
    set(Qt5QuickControls2_DIR "/usr/local/Qt-5.15.5/lib/cmake/Qt5QuickControls2")
    set(Qt5LinguistTools_DIR  "/usr/local/Qt-5.15.5/lib/cmake/Qt5LinguistTools")
    set(Qt5Mqtt_DIR           "/usr/local/Qt-5.15.5/lib/cmake/Qt5Mqtt")
    set(Qt5WebSockets_DIR     "/usr/local/Qt-5.15.5/lib/cmake/Qt5WebSockets")
    set(QT_QMAKE_EXECUTABLE   "/usr/local/Qt-5.15.5/bin/qmake")
endmacro(lzr_setup_qt)

# Link Qt5 library to specified service
function(lzr_link_qt service)
    find_package(Qt5 COMPONENTS Core Mqtt Qml Quick QuickControls2 LinguistTools WebSockets REQUIRED)

    target_include_directories(${service} PRIVATE ${QT5_INCLUDE_DIR})
    target_link_libraries(${service} PRIVATE
        Qt5::Core
        Qt5::Mqtt
        Qt5::Qml
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::WebSockets
    )
endfunction()

# Link systemd library for the requested target
function(lzr_link_systemd service)
    target_link_libraries(${service} PRIVATE systemd)
endfunction()

# Creates the service file into the target device
function(lzr_create_service service service_file)
    lzr_link_systemd(${service})

    # Install service file into systemd directory
    set(SERVICES_DIR "/lib/systemd/system/")
    install(FILES ${service_file} DESTINATION ${SERVICES_DIR})
endfunction()

macro(lzr_setup_cross)
endmacro(lzr_setup_cross)

macro(lzr_add_service)
endmacro(lzr_add_service)
