#ifndef TIME_H
#define TIME_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long time_t;

time_t time(time_t* t);
void sleep(unsigned int seconds);
void usleep(unsigned int microseconds);

#ifdef __cplusplus
}
#endif

#endif // TIME_H
