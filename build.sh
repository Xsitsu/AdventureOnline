#!/bin/sh

build_mode="Release"

while getopts ":d" opt; do
    case $opt in
        d)
            build_mode="Debug"
            ;;
        \?)
            echo "Invalid command"
            exit 1
            ;;
    esac
done

script_dir="$(dirname -- "$(readlink -f -- "$0")")"
build_dir="$script_dir"/cmake-build

mkdir -p _dependency-cache
mkdir -p "$build_dir"

cmake -B "$build_dir" -S "$script_dir" -DCMAKE_BUILD_TYPE="$build_mode"

cmake --build "$build_dir" --target server --config "$build_mode"
cmake --build "$build_dir" --target client --config "$build_mode"
