#!/bin/bash

message="Eins"
echo "$message"

# ? any single character
# * any number of characters
# [] range 
# K
chmod +x ref/nja

BASEDIR=$(dirname $0)
count=$(find ./progs -maxdepth 1 -name "*.asm" | wc -l)
for ((z=1; z<=$count;z++))
do
    "$BASEDIR"/ref/nja progs/prog"$z".asm progs/prog"$z".bin
done