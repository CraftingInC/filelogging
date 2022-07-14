# File Logging Demonstration in C

#### COMPILE WITH GCC TESTED

    gcc -m64 -Os -static main.c -o test -s

#### NOTES

This file logging demonstration works on both Linux and Windows 10.

It might work on windows 7 and 8, however you would need to remove most of whats in the main.c file that relates to ANSI graphics. 

This code is using the modern Virtual Terminal Sequences do to the fact that the older functions for ANSI are deprecated.
