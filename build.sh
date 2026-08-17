#!/bin/bash

set -e

CXX_COMPILER=""

usage() {
    local script_name="${0}"
    cat << EOF
Usage:
    "${script_name}"
    "${script_name}" --compiler <path>
    "${script_name}" -c <path>
Options:
    -c, --compiler <path>    Specify C++ compiler
    -h, --help               Show this help
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        -c|--compiler)
            if [[ -z "$2" ]]; then
                echo "Error: $1 requires a compiler path."
                exit 1
            fi
            CXX_COMPILER="$2"
            shift 2
            ;;

        -h|--help)
            usage
            exit 0
            ;;

        *)
            echo "Error: Unknown option: $1"
            echo "Use './build.sh --help' for usage."
            exit 1
            ;;
    esac
done

# コンパイラが指定されていなければ g++ を使用
if [[ -z "$CXX_COMPILER" ]]; then
    CXX_COMPILER=$(command -v g++)
fi

# コンパイラの存在確認
if [[ ! -x "$CXX_COMPILER" ]]; then
    echo "Error: C++ compiler not found: $CXX_COMPILER"
    exit 1
fi

echo "C++ compiler: $CXX_COMPILER"

# buildディレクトリを削除
if [[ -d "build" ]]; then
    echo "Removing build directory..."
    rm -rf build
fi

# CMake
echo "Configuring..."
cmake -S . -B build \
    -DCMAKE_CXX_COMPILER="$CXX_COMPILER"

# Build
echo "Building..."
cmake --build build

echo "Build completed."
