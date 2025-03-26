#include "print.h"
#include "error.h"


void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
    print_str("Welcome to the kernel!\n");

    int x = 5;
    print_number(x);
    print_newline();

    if(x != 4){
        error("Number isnt 4");
        info("Number isnt 4");
        warn("Number isnt 4");
        panic("Number isnt 4");
    }
}