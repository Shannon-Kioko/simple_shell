#include "shell.h"

/**
 * print_error_str - Function writes to STDERR.
 *
 * @str: Pointer to an array of characters.
 *
 * Return: Number of bytes written. Otherwise, -1 is returned and errno is set
 * appropriately.
 */
int print_error_str(char *str)
{
	return (write(STDERR_FILENO, str, str_length(str)));
}

/**
 * print_string - Function writes to STDOUT.
 *
 * @str: Pointer to an array of characters.
 *
 * Return: Number of bytes written. Otherwise, -1 is returned and errno is set
 * appropriately.
 */
int print_string(char *str)
{
	return (write(STDOUT_FILENO, str, str_length(str)));
}

/**
 * print_err - Function writes to standard error.
 *
 * @err_code: Error code to print.
 * @data: Pointer to program data.
 *
 * Return: Number of bytes written. Otherwise, -1 is returned and errno is set
 * appropriately.
 */
int print_err(int err_code, data_of_program *data)
{
	char n_as_a_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_a_string, 10);

	if (err_code == 2 || err_code == 3)
	{
		print_error_str(data->program_name);
		print_error_str(": ");
		print_error_str(n_as_a_string);
		print_error_str(": ");
		print_error_str(data->tokens[0]);
		if (err_code == 2)
			print_error_str(": Invalid number: ");
		else
			print_error_str(": Unable to change directory to ");
		print_error_str(data->tokens[1]);
		print_error_str("\n");
	}
	else if (err_code == 127)
	{
		print_error_str(data->program_name);
		print_error_str(": ");
		print_error_str(n_as_a_string);
		print_error_str(": ");
		print_error_str(data->command_name);
		print_error_str(": not found\n");
	}
	else if (err_code == 126)
	{
		print_error_str(data->program_name);
		print_error_str(": ");
		print_error_str(n_as_a_string);
		print_error_str(": ");
		print_error_str(data->command_name);
		print_error_str(": Permission denied\n");
	}
	return (0);
}
