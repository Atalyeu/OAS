#include "string.h"

#undef memcpy
#undef memset
#undef memcmp

void* memcpy(void* restrict dest, const void* restrict src, size_t count) {
    if (!dest || !src) return NULL; // Safety check

    __asm__ volatile (
        "cmp $16, %2         \n\t" // If count < 16, jump to tail copy
        "jb 1f               \n\t"

        "movq %0, %%rdi      \n\t" // dest in RDI
        "movq %1, %%rsi      \n\t" // src in RSI
        "movq %2, %%rcx      \n\t" // count in RCX
        "shr $4, %%rcx       \n\t" // count /= 16 (number of 16-byte chunks)

        "rep movdqu          \n\t" // Copy 16 bytes per iteration
        "1:                  \n\t"

        "movq %2, %%rcx      \n\t" // Restore count
        "and $15, %%rcx      \n\t" // count % 16 (remaining bytes)
        "rep movsb           \n\t" // Copy remaining bytes
        :
        : "r"(dest), "r"(src), "r"(count)
        : "rdi", "rsi", "rcx", "memory"
    );

    return dest;
}

void* memset(void* dest, int val, size_t count) {
    if (!dest) return NULL; // Safety check

    uint64_t v64 = (uint64_t)(unsigned char)val * 0x0101010101010101ULL;

    __asm__ volatile (
        "cmp $16, %2         \n\t" // If count < 16, jump to tail set
        "jb 1f               \n\t"

        "movq %0, %%rdi      \n\t" // dest in RDI
        "movq %2, %%rcx      \n\t" // count in RCX
        "shr $4, %%rcx       \n\t" // count /= 16

        "movdqu %1, %%xmm0   \n\t" // Load value into SSE register
        "rep stosq           \n\t" // Set 16 bytes per iteration
        "1:                  \n\t"

        "movq %2, %%rcx      \n\t" // Restore count
        "and $15, %%rcx      \n\t" // count % 16
        "rep stosb           \n\t" // Set remaining bytes
        :
        : "r"(dest), "r"(v64), "r"(count)
        : "rdi", "rcx", "xmm0", "memory"
    );

    return dest;
}

void* memmove(void* dest, const void* src, size_t count) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    if (d < s) {
        while (count--) {
            *d++ = *s++;
        }
    } else {
        d += count;
        s += count;
        while (count--) {
            *--d = *--s;
        }
    }
    return dest;
}

int memcmp(const void* a, const void* b, size_t count) {
    const unsigned char* s1 = (const unsigned char*)a;
    const unsigned char* s2 = (const unsigned char*)b;
    while (count--) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
}

/* String manipulation */
size_t strlen(const char* str) {
    const char* s = str;
    while (*s) {
        s++;
    }
    return s - str;
}

int strcmp(const char* a, const char* b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

int strncmp(const char* a, const char* b, size_t n) {
    while (n-- && *a && (*a == *b)) {
        a++;
        b++;
    }
    if (n == (size_t)-1) return 0;
    return (unsigned char)*a - (unsigned char)*b;
}

char* strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++));
    return dest;
}

char* strncpy(char* dest, const char* src, size_t n) {
    char* d = dest;
    while (n && (*d = *src)) {
        d++;
        src++;
        n--;
    }
    while (n--) {
        *d++ = '\0';
    }
    return dest;
}

char* strcat(char* dest, const char* src) {
    char* d = dest;
    while (*d) { 
        d++;
    }
    while ((*d++ = *src++));
    return dest;
}
