#include "print.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Number {
    int number;
    uint8_t color;
};

struct Char* buffer = (struct Char*)0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | (PRINT_COLOR_BLACK << 4);

void clear_row(size_t row){
    struct Char empty = { .character = ' ', .color = color };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_newline(){
    col = 0;
    
    if(row < NUM_ROWS - 1){
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_char(char character){
    if(character == '\n'){
        print_newline();
        return;
    }

    if (col >= NUM_COLS) {
        print_newline();
        return;
    }

    buffer[col + NUM_COLS * row] = (struct Char){
        character: (uint8_t)character,
        color: color,
    };

    col++;
}

void print_str(char* string){
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t)string[i];

        if(character == '\0'){
            return;
        }

        print_char(character);
    }
}


void print_set_color(uint8_t foreground, uint8_t background){
    color = foreground + (background << 4);
}

void print_number(int number){
    char buffer[32]; // Enough to store a 32-bit integer as a string
    int index = 0;
    
    if (number < 0) {
        print_char('-');
        number = -number;
    }

    if (number == 0) {
        print_char('0');
        return;
    }

    while (number > 0) {
        buffer[index++] = '0' + (number % 10); // Convert digit to char
        number /= 10;
    }

    // Print number in correct order
    for (int i = index - 1; i >= 0; i--) {
        print_char(buffer[i]);
    }
}
