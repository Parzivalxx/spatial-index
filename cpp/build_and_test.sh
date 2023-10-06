#!/bin/sh

# Store the current directory in a variable
ORIGINAL_DIR=$(pwd)

BUILD_DIR="./build"
mkdir -p "${BUILD_DIR}"

cmake --build "${BUILD_DIR}"

if [ "$1" = "--run" ]; then
    cd "${BUILD_DIR}/src/Debug"
    ./spatial_index.exe

    # Return to the original directory
    cd "${ORIGINAL_DIR}"
else
    cd "${BUILD_DIR}" && ctest
    # Return to the original directory
    cd "${ORIGINAL_DIR}"
fi
