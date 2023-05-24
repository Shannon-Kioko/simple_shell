#include "shell.h"

/**
 * long_to_string - function converts a long number to a string
 * @num: number to be converted
 * @str: string to store the number as a string
 * @base: base to convert the number
 * Return: None
 */

void long_to_string(long num, char *str, int base)
{
	int index = 0, inNegative = 0;
	long convi = num;
	char letters[] = {"0123456789abcdef"};
	
	if (convi == 0)
		str[index++] = '0';

	if (str[0] == '-')
		inNegative = 1;

	for (; convi != 0; convi /= base)
	{
		if (convi < 0)
			str[index++] = letters[-(convi % base)];
		else
			str[index++] = letters[convi % base];
	}

	if (inNegative)
		str[index++] = '-';

	str[index] = '\0';
	str_reverse(str);
}

/**
 * _atoi - function converts a string to an integer
 * @s: pointer to the source string
 * Return: integer representation of the string,
 * or 0 if conversion fails
 */

int _atoi(char *s)
{
	int z = 1;
	unsigned int num = 0;

	for (; !('0' <= *s && *s <= '9') && *s != '\0'; s++)
	{
		if (*s == '-')
			z *= -1;
		if (*s == '+')
			z *= +1;
	}

	for (; '0' <= *s && *s <= '9' && *s != '\0'; s++)
	{
		num = (num * 10) + (*s - '0');
	}

	return (num * z);
}

/**
 * count_character_occurrences - function calculates the frequency of
 * a character in a string
 * @string: pointer to the source string
 * @character: string containing the characters to be counted
 * Return: integer representing the frequency of the
 * character in the string, or 0 if not found
 */

int count_character_occurrences(char *string, char *character)
{
	int i = 0, ctr = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			ctr++;
	}
	return (ctr);
}
