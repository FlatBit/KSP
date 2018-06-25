#!/bin/bash

message="Eins"
echo "$message"

# ? any single character
# * any number of characters
# [] range 

chmod +x ref/nja

for file in /progs/*.asm
do
    ./ref/nja $file $file.bin
done
