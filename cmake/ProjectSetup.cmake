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

macro(lzr_set_plog_definitions)
endmacro(lzr_set_plog_definitions)

macro(lzr_setup_qt)
endmacro(lzr_setup_qt)

macro(lzr_setup_cross)
endmacro(lzr_setup_cross)

macro(lzr_add_service)
endmacro(lzr_add_service)
