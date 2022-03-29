#!/bin/bash

# Show help information and how-to run
print_help()
{
    echo "Build script for Lazarillo software"
    echo
    echo "Syntax: ./build.sh args"
    echo "args:"
    echo "  [--clean]                               - Removes build folder before compiling"
    echo "  [--cpack]                               - Runs cpack after building"
    echo "  [-c|--compile_mode (COMPILE_MODE|-h)]   - Compile mode (use -c -h for details)"
    echo "  [-h|--help]                             - Prints this message"
    echo "  [-j|-jJOBS|--jobs JOBS]                 - Number of parallel jobs to build"
    echo "  [-V|--verbose]                          - Prints debug info on compiling"
    echo
}

print_compile_mode_help()
{
    echo "Compile modes"
    echo
    echo "  r   - Release"
    echo "  d   - Debug"
}

print_debug()
{
    if [ -n "$DEBUG" ]; then
        echo -e "\033[0;33mDEBUG:\033[0m $*"
    fi
}

################################################################

# Start parsing the arguments
while (( "$#" )); do
    case "$1" in
        -c|--compile_mode)
            if [ -n "$2" ]; then
                
            fi
            ;;
        -h|--help)
            print_help
            exit 0
            ;;
        
    esac
done
