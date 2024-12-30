#!/bin/bash

compile_commands_path="../build/compile_commands.json"
source_files="../src ../SystemLoaders"

find $source_files -iname '*.hpp' -o -iname '*.cpp' | xargs clang-tidy -p $compile_commands_path -header-filter=.*