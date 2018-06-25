#!/bin/bash

message="Eins"
echo "$message"

# ? any single character
# * any number of characters
# [] range 

chmod +x ref/nja
 ./ref/nja /progs/prog[0-9]*.asm /progs/prog[0-9]*.bin
