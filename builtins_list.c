#include "shell.h"

/**
 * builtin_executes - Search for a match and execute the associated builtin.
 * @data: Pointer to the program's data struct.
 *
 * Return: The return value of the executed function if there is a match,
 * otherwise returns -1.
 */
int builtin_executes(data_of_program *data)
{
	int iterator;
	BuiltinPair options[] = {
		{"exit", builtin_exit},
		{(int)"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	/* Iterate through the builtin options */
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		/* Check for a match between the given command and a builtin */
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
			/* Execute the associated function and return its return value */
			return (options[iterator].function(data));
		}
	}

	/* If there is no match, return -1 */
	return (-1);
}
