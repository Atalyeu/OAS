#ifndef ASSERT_H
#define ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

void __assert_fail(const char* assertion, const char* file, unsigned int line);

#define assert(expr) ((expr) ? (void)0 : __assert_fail(#expr, __FILE__, __LINE__))

#ifdef __cplusplus
}
#endif

#endif // ASSERT_H
