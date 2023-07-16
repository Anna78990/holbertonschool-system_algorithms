#include <stdio.h>


/**
 * itoa - Convert a number to a specific base
 * @val: Number to convert
 * @base: Base to convert
 *
 * Return: String with number converted
 */
char *itoa(int val, int base)
{
	static char buf[32] = {0};
	int i = 30;

	for (; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return (&buf[i + 1]);
}

void main()
{
	char *bit;

	bit = itoa(5, 2);
	printf("bit is %s\n", bit);
} 
