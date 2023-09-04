#!/bin/sh

BUILD_DIR="./build"
mkdir -p "${BUILD_DIR}"

cmake --build "${BUILD_DIR}"
cd "${BUILD_DIR}" && ctest
