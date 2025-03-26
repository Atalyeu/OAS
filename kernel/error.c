/*
* error.c
* This file contains the implementation of the error handling functions.
* Author: Omer Attali
* void error(char* message) - prints an error message
* void warn(char* message) - prints a warning message
* void info(char* message) - prints an info message
* void panic(char* message) - prints a panic message and halts the system
*/

// * Need to be deleted and transferred to the correct file _ /libc/errno _

#include "error.h"

void error(char* message){
    print_set_color(PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
    print_str("ERROR: ");
    print_str(message);
    print_newline();
}

void warn(char* message){
    print_set_color(PRINT_COLOR_BROWN, PRINT_COLOR_BLACK);
    print_str("WARNING: ");
    print_str(message);
    print_newline();
}

void info(char* message){
    print_set_color(PRINT_COLOR_LIGHT_BLUE, PRINT_COLOR_BLACK);
    print_str("INFO: ");
    print_str(message);
    print_newline();
}

void panic(char* message){
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_RED);
    print_str("PANIC: ");
    print_str(message);
    print_newline();
    while(1);
}