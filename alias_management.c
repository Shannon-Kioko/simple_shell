#include "shell.h"

/**
 * print_alias - Print aliases or a specific alias.
 * @data: Pointer to the program's data struct.
 * @alias_name: Name of the alias to be printed (optional).
 *
 * Return: 0 on success, or other number if it's declared in the arguments.
 */
int print_alias(ProgramData *data, char *alias_name)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias_name);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias_name || (str_compare(data->alias_list[i], alias_name, alias_length)
				&& data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_append(buffer, "'");
				buffer_append(buffer, data->alias_list[i] + j + 1);
				buffer_append(buffer, "'\n");
				print_string(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - Retrieve the value of an alias.
 * @data: Pointer to the program's data struct.
 * @name: Name of the requested alias.
 *
 * Return: Pointer to the value of the alias, or NULL if not found.
 */
char *get_alias(ProgramData *data, char *name)
{
	int i, alias_length;

	/* Validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		/* Iterate through the alias list and check for a match */
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			/* Return the value of the alias */
			return (data->alias_list[i] + alias_length + 1);
		}
	}

	/* Return NULL if the alias is not found */
	return (NULL);
}

/**
 * set_alias - Add or override an alias.
 * @alias_string: Alias to be set in the form "name='value'".
 * @data: Pointer to the program's data struct.
 *
 * Return: 0 on success, or other number if it's declared in the arguments.
 */
int set_alias(char *alias_string, ProgramData *data)
{
	int i, j;
	char buffer[250] = {'\0'}, *alias_value = NULL;

	/* Validate the arguments */
	if (alias_string == NULL || data->alias_list == NULL)
		return (1);

	/* Iterate through the alias string to find the '=' character */
	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			/* Check if the value of the alias is another alias */
			alias_value = get_alias(data, alias_string + i + 1);
			break;
		}
	}

	/* Iterate through the alias list and check for a match */
	for (j = 0; data->alias_list[j]; j++)
	{
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			/* If the alias already exists, free the previous value */
			free(data->alias_list[j]);
			break;
		}
	}

	/* Add or override the alias */
	if (alias_value)
	{
		/* If the alias value is another alias */
		buffer_append(buffer, "=");
		buffer_append(buffer, alias_value);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else
	{
		/* If the alias value is a regular value */
		data->alias_list[j] = str_duplicate(alias_string);
	}

	return (0);
}
