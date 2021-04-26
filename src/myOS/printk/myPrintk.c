/*
 * 实现myPrint功能 先学习C语言的可变参数内容
 * 需要调用到格式化输出的function（vsprintf）
 */ 

#include <stdarg.h>

extern void append2screen(char *str,int color);
extern void uart_put_chars(char *str);
extern void uart_put_char(unsigned char c);
extern int myVsprintf(char *buf, int max, const char* format, va_list args);

char kBuf[400];
int myPrintk(int color,const char *format, ...){
   va_list args;
   int size;
   
   va_start (args, format);
   size = myVsprintf (&kBuf[0], 400, format, args);
   va_end (args);
   
   kBuf[size]='\0';
   append2screen(kBuf,color);
   uart_put_chars(kBuf);
   return size;
}

char uBuf[400];
int myPrintf(int color,const char *format, ...){
   va_list args;
   int size;
   
   va_start (args, format);
   size = myVsprintf (&uBuf[0], 400, format, args);
   va_end (args);
   
   uBuf[size]='\0';
   append2screen(uBuf,color);
   uart_put_chars(uBuf);
   return size;
}
