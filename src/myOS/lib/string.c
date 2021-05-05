#include "type.h"

void *memcpy(void *dest, const void *src, unsigned int count){
    const uint8_t *sp = (const uint8_t *)src;
    uint8_t *dp = (uint8_t *)dest;

    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}


void *memsetw(void *dest, uint16_t val, unsigned int count){
    uint16_t *temp = (uint16_t *)dest;

    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strnlen(const char *s, int maxlen)
{
	const char *es = s;
	while (*es && maxlen) {
		es++;
		maxlen--;
	}

	return (es - s);
}
int strcmp(const char *str1, const char *str2) {
    while (*str1||*str2){
        if (*str1 == *str2){
            str1++;
            str2++;
        }
        else return *str1 - *str2;
    }
    return 0;
}

