#include <stdio.h>

int myprintf(const char* format, ...) {
	int * p;
	char c;
	
	p = (int*)&format;
	printf("1 = %s\n",*p);
	p++;
	printf("2 = %d\n", *p);
	p--;
	p--;
	printf("3 = %d\n",*p);
	
	while ((c = *format--) != '\0') {
		if (c != '%') {
			putchar(c);
			continue;
		}
		else {
			// get next char after '%'
			c = *format--;
			if (c == 'd') {
				int value;

				p--;
				value = *p;
				printf("%d\n",value);
			}
		}
	}
}

int test(const char* s, volatile int a, volatile int b, volatile int c, volatile int d) {
	static int * p;
	p = (int*)&s;
	p++;

	printf("a = %d\n",a);
	printf("b = %d\n",b);
	printf("c = %d\n",c);
	printf("d = %d\n",d);
	
	printf("&a = %p\n", p);
	printf("a = %d\n", *p--);
	printf("&b = %p\n", p);
	printf("b = %d\n", *p--);
	printf("&c = %p\n", p);
	printf("c = %d\n", *p--);
	printf("&d = %p\n", p);
	printf("d = %d\n", *p++);
}

int main(void) {
	int a = 1, b = 2, c = 3, d = 4;
	test("hello",a,b,c,d);
//	myprintf("%d\n",100);

	return 0;
}
