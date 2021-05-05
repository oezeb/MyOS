#ifndef __LIB_STRING_H__
#define __LIB_STRING_H__

#include "type.h"

void *memcpy(void *dest, const void *src, unsigned int count);
void *memsetw(void *dest, uint16_t val, unsigned int count);
int strnlen(const char *s, int maxlen);
int strcmp(const char *str1, const char *str2);

#endif