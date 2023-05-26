#include "shell.h"

/**
 * builtin_env - Show the environment where the shell runs.
 * @data: Pointer to the program's data struct.
 *
 * Return: 0 on success, or other number if it's declared in the arguments.
 */
int builtin_env(data_of_program *data)
{
	int i;
	char var_name[50] = {'\0'};
	char *var_copy = NULL;

	/* If no arguments */
	if (data->tokens[1] == NULL)
		print_env(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			/* Check if '=' character exists */
			if (data->tokens[1][i] == '=')
			{
				/* Temporarily change the value of an existing variable with the same name */
				var_copy = str_duplicate(env_get_key(var_name, data));
				if (var_copy != NULL)
					env_set_key(var_name, data->tokens[1] + i + 1, data);

				print_env(data);
				if (env_get_key(var_name, data) == NULL)
				{
					print_string(data->tokens[1]);
					print_string("\n");
				}
				else
				{
					env_set_key(var_name, var_copy, data);
					free(var_copy);
				}

				return (0);
			}
			var_name[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}

	return (0);
}

/**
 * builtin_set_env - Set an environment variable.
 * @data: Pointer to the program's data struct.
 *
 * Return: 0 on success, or other number if it's declared in the arguments.
 */
int builtin_set_env(data_of_program *data)
{
	/* Validate arguments */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);

	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - Unset an environment variable.
 * @data: Pointer to the program's data struct.
 *
 * Return: 0 on success, or other number if it's declared in the arguments.
 */
int builtin_unset_env(data_of_program *data)
{
	/* Validate arguments */
	if (data->tokens[1] == NULL)
		return (0);

	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_remove_key(data->tokens[1], data);

	return (0);
}
