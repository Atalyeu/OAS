#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Memory manipulation */
void* memcpy(void* restrict dest, const void* restrict src, size_t count);
void* memset(void* dest, int val, size_t count);
void* memmove(void* dest, const void* src, size_t count);
int   memcmp(const void* a, const void* b, size_t count);

/* String manipulation */
size_t strlen(const char* str);
int    strcmp(const char* a, const char* b);
int    strncmp(const char* a, const char* b, size_t n); 
char*  strcpy(char* dest, const char* src);
char*  strncpy(char* dest, const char* src, size_t n);
char*  strcat(char* dest, const char* src);

#ifdef __cplusplus
}
#endif

#endif // STRING_H
