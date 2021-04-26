/*
 * 识别格式化字符串的核心代码写在本文件中
 * 可以从网上移植代码，建议参考 sprintf vsprintf的源代码
 */
 
#include <stdarg.h>
 
char *convert(unsigned int num, int base)  {
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50]; 
	char *ptr; 
	
	ptr = &buffer[49]; 
	*ptr = '\0'; 
	
	do 
	{ 
		*--ptr = Representation[num%base]; 
		num /= base; 
	}while(num != 0); 
	
	return(ptr); 
}

int myPuts(char* buf, int max, char* data) {
	char* e = data;
	unsigned int i = 0;
	while(i < max && *e != '\0') {
		*buf++ = *e++;
		i++;
	}
	return i;
}

int myVsprintf(char *buf, int max, const char* format, va_list args) {
	char *s;
	unsigned int j;
	unsigned int i = 0;
	int size = 0;
	while(i < max && format[i] != '\0') {
		while(i < max && format[i] != '\0' && format[i] != '%' ) { 
			*buf++ = format[i++];
			size++;
		}
		
		if(i < max && format[i] != '\0') {
			switch(format[++i]) {
				case 'c' :
					j = va_arg(args,int);		//Fetch char argument				
					*buf++ = j;
					size++;
					break; 
				
				case 'd' : 
					j = va_arg(args,int); 		//Fetch Decimal/Integer argument
					if(j<0) { 
						j = -j;
						*buf++ = '-';
					}
					j = myPuts(buf, max-i, convert(j,10));
					buf+=j;
					size+=j;
					break; 
						
				case 'o': 
					j = va_arg(args,unsigned int); //Fetch Octal representation
					j = myPuts(buf, max-i, convert(j,8));
					buf+=j;
					size+=j;
					break; 
				
				case 's': 
					s = va_arg(args,char *); 		//Fetch string
					j = myPuts(buf, max-i, s);					
					buf+=j;
					size+=j;
					break; 
						
				case 'x': 
					j = va_arg(args,unsigned int); //Fetch Hexadecimal representation
					j = myPuts(buf, max-i, convert(j,16));
					buf += j;
					size +=j;
					break;
			}
			i++;
		}
	}
	return size;	
}
