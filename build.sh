#!/bin/bash

# Stop compilation after error
set -e

CWD=`pwd`

# Show help information and how-to run
print_help()
{
    echo "Build script for Lazarillo Embedded software"
    echo
    echo "Syntax: ./build.sh args"
    echo "args:"
    echo "  [--clean]                               - Removes build folder before compiling"
    echo "  [--cpack]                               - Runs cpack after building"
    echo "  [-c|--compile_mode (COMPILE_MODE|-h)]   - Compile mode (use -c -h for details)"
    echo "  [-h|--help]                             - Prints this message"
    echo "  [-j|-jJOBS|--jobs JOBS]                 - Number of parallel jobs to build"
    echo
}

print_compile_mode_help()
{
    echo "Compile modes"
    echo
    echo "  r   - Release"
    echo "  d   - Debug"
}

# Prints the command received as parameter
print_debug()
{
    if [ -n "$DEBUG" ]; then
        echo -e "\033[0;33mDEBUG:\033[0m $*" >&2
    fi
}

# Shows the command about to be run and runs it
print_exe()
{
    print_debug $*
    $*
}

################################################################

CMAKE_ARGUMENTS=""
PARAMS=""

# Start parsing the arguments
while (( "$#" )); do
    case "$1" in
        -h|--help)
            print_help
            exit 0
            ;;
        --clean)
            CLEAN_BEFORE_BUILDING="TRUE"
            shift 1
            ;;
        --cpack)
            CPACK="TRUE"
            shift 1
            ;;
        -c|--compile_mode)
            if [ -n "$2" ]; then
                if [ "${2:0:1}" != "-" ]; then
                    COMPILE_MODE="${2,,}"
                elif [[ "$2" =~ (-h)|(--help) ]]; then
                    print_compile_mode_help
                    exit 1
                else
                    echo "Error: Argument for $1 is missing" >&2
                    print_compile_mode_help
                    exit 1
                fi
            else
                echo "Error: Argument for $1 is missing" >&2
                print_compile_mode_help
                exit 1
            fi
            ;;
        -j|--jobs)
            if [ -n "$2" ] && [ "${2:0:1}" != "-" ]; then
                # If the number of jobs is greater than 0, use that number
                if [[ "$2" =~ ^[0-9]+$ ]] && [ "$2" -gt 0 ]; then
                    JOBS="$2"
                # Otherwise, set the number of jobs to 1
                else
                    JOBS="1"
                fi
                shift 2
            # If the number of jobs is not specified, try to get the number of available compute units
            elif command -v nproc &> /dev/null; then
                JOBS=`nproc`
                shift 1
            # Otherwise, fallback to use 1 job
            else
                JOBS="1"
                shift 1
            fi
            ;;
        -j[0-9]*)
            if [[ "${1:2}" =~ ^[0-9]+$ ]]; then
                # If the number of jobs is greater than 0, use that number
                if [ "${1:2}" -gt 0 ]; then
                    JOBS="${1:2}"
                # Otherwise, set the number of jobs to 1
                else
                    JOBS="1"
                fi
                shift 1
            else
                echo "Error: Argument for -jN is incorrect" >&2
                exit 1
            fi
            ;;
    esac
done

# Set positional arguments into their proper place
eval set -- "$PARAMS"

# Set the compile mode
if [[ "$COMPILE_MODE" =~ ^[^rd]$ ]]; then
    echo "Error: compile mode \"$COMPILE_MODE\" not recognized" >&2
    print_compile_mode_help
    exit 1
fi
CMAKE_ARGUMENTS="$CMAKE_ARGUMENTS -DCOMPILE_MODE=$COMPILE_MODE"

# Append positional parameters
if [ -n "$PARAMS" ]; then
    if [ -z "$CMAKE_BUILD_ARGUMENTS" ]; then
        CMAKE_BUILD_ARGUMENTS="$PARAMS"
    else
        CMAKE_BUILD_ARGUMENTS="$CMAKE_BUILD_ARGUMENTS $PARAMS"
    fi
fi

# If there's a number of jobs, pass it as parameter
if [ -z "$JOBS" ]; then
    # If it's not set, read available cores
    if command -v nproc &> /dev/null; then
        JOBS=`nproc`
    else
        JOBS=1
    fi
fi

# Append number of jobs to build arguments
if [ -z "$CMAKE_BUILD_ARGUMENTS" ]; then
    CMAKE_BUILD_ARGUMENTS="-j$JOBS"
else
    CMAKE_BUILD_ARGUMENTS="$CMAKE_BUILD_ARGUMENTS -j$JOBS"
fi

# Set build folder is not set
if [ -z "$BUILD_FOLDER" ]; then
    BUILD_FOLDER="build"

    if [[ "$COMPILE_MODE" == "d" ]]; then
        BUILD_FOLDER="${BUILD_FOLDER}_debug"
    elif [[ "$COMPILE_MODE" == "r" ]]; then
        BUILD_FOLDER="${BUILD_FOLDER}_release"
    fi
fi

# Clean build folder if --clean
if [ -n "$CLEAN_BEFORE_BUILDING" ]; then
    if [ -d "$BUILD_FOLDER" ]; then
        print_exe rm -rf "$BUILD_FOLDER"
    fi
fi

# Build code
print_exe mkdir -p "$BUILD_FOLDER"
print_exe cd "$BUILD_FOLDER"

# Run cmake with parameters
if [ -n "$CLEAN_BEFORE_BUILDING" ] || [ -z "$(ls -A .)" ]; then
    if [ -n "$CMAKE_ARGUMENTS" ]; then
        print_exe cmake "$CMAKE_ARGUMENTS" "$CWD"
    else
        print_exe cmake "$CWD"
    fi
else
    print_debug "Skipped cmake configuration. To avoid this, use --clean flag"
fi

print_exe cmake --build . -- "$CMAKE_BUILD_ARGUMENTS"

# Generate deb if request
if [ -n "$CPACK" ]; then
    print_exe cpack
    status=$?
    if [[ $status -eq 0 ]]; then
        if [ -n "$DEB" ]; then
            DEB_FOLDER="../deb"
            print_exe mkdir -p "$DEB_FOLDER"
            print_exe mv *.deb "$DEB_FOLDER/"
        fi
    else
        echo "Error generating deb: CPack command failed."
        exit 1
    fi
fi

print_exe cd "$CWD"
