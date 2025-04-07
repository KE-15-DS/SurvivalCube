#!/bin/bash

set -e
NAME=$(basename $(pwd))

make
desmume-glade --arm9gdb=4444 $NAME.nds &
kdbg -r:4444 $NAME.elf
