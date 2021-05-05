#ifndef __VSPRINTF_H__
#define __VSPRINTF_H__

#include <stdarg.h>

static inline int isdigit(int ch)
{
	return (ch >= '0') && (ch <= '9');
}

static char *number(char *str, long num, int base, int size, int precision, int type);
int vsprintf(char* dst, const char* format, va_list args);
int sprintf(char *buf, const char *fmt, ...);

#endif