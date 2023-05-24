#include "shell.h"

/**
 * _strtok - Function that separates strings using delimiters
 *
 * @line: Pointer to  input string
 * @delim: Delimiter character used for tokenizing
 *
 * Return: Pointer to the created token
 */

char *_strtok(char *line, char *delim)
{
	int i;
	static char *current_string;
	char *copy_string;

	if (line != NULL)
		current_string = line;

	for (; *current_string != '\0'; current_string++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*current_string == delim[i])
				break;
		}
		if (delim[i] == '\0')
			break;
	}

	copy_string = current_string;
	if (*copy_string == '\0')
		return (NULL);

	for (; *current_string != '\0'; current_string++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*current_string == delim[i])
			{
				*current_string = '\0';
				current_string++;
				return (copy_string);
			}
		}
	}

	return (copy_string);
}
