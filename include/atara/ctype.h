#ifndef CTYPE_H
#define CTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

int isalnum(int c);
int isalpha(int c);
int isdigit(int c);
int islower(int c);
int isupper(int c);
int isspace(int c);
int tolower(int c);
int toupper(int c);

#ifdef __cplusplus
}
#endif

#endif // CTYPE_H
