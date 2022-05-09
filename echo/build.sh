#!/bin/bash

wrapped_syscalls=("malloc" "calloc" "free")

wrap=""
for w in "${wrapped_syscalls[@]}"; do
    wrap="$wrap -Wl,--wrap,$w"
done

echo "Building echo"
cmd="gcc $wrap -std=gnu99 -pthread -o prog ${@:1}"
echo "$cmd"
$cmd