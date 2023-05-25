#include "shell.h"

/**
 * is_number - Check if a string represents a valid integer.
 * @str: The string to be checked.
 *
 * Return: True if the string is a valid integer, false otherwise.
 */
bool is_number(const char *str)
{
	int i = 0;

	/* Check for negative sign */
	if (str[i] == '-')
		i++;

	/* Check if the remaining characters are digits */
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
		i++;
	}

	return true;
}

/**
 * has_character - Check if a string contains a specific character.
 * @str: The string to be checked.
 * @c: The character to be searched.
 *
 * Return: True if the character is found in the string, false otherwise.
 */
bool has_character(const char *str, char c)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
			return true;
		i++;
	}

	return false;
}

/**
 * check_file - Check if a file exists at the given path.
 * @file_path: The path of the file to be checked.
 *
 * Return: True if the file exists, false otherwise.
 */
bool check_file(const char *file_path)
{
	FILE *file;

	file = fopen(file_path, "r");
	if (file != NULL)
	{
		fclose(file);
		return true;
	}

	return false;
}
