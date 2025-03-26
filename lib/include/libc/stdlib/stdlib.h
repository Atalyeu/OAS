#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t new_size);
void* calloc(size_t num, size_t size);

int atoi(const char* str);
char* itoa(int value, char* str, int base);

#ifdef __cplusplus
}
#endif

#endif // STDLIB_H
