#include"main.h"
/**
 * getlen - Function calculates the length of a given string.
 * @str: The string whose length we are to calculate.
 *
 * Description: Function calculates the length of a given string.
 * Return: The length of the string.
 */
size_t getlen(char str[])
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;

	return (len);
}
