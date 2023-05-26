#include "shell.h"

/**
 * get_input_line - Read one line from the prompt.
 * @data: Pointer to the program's data struct.
 *
 * Return: Number of bytes read.
 */
int get_input_line(data_of_program *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *command_array[10] = {NULL};
	static char operator_array[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	/* Check if there are no more commands in the array */
	/* and check the logical operators */
	if (!command_array[0] || (operator_array[0] == '&' && errno != 0) ||
		(operator_array[0] == '|' && errno == 0))
	{
		/* Free the memory allocated in the array if it exists */
		for (i = 0; command_array[i]; i++)
		{
			free(command_array[i]);
			command_array[i] = NULL;
		}

		/* Read from the file descriptor into buffer */
		bytes_read = read(data->file_descriptor, buffer, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* Split lines on '\n' or ';' */
		i = 0;
		do {
			command_array[i] = str_duplicate(_strtok(i ? NULL : buffer, "\n;"));
			/* Check and split for '&&' and '||' operators */
			i = check_logical_operators(command_array, i, operator_array);
		} while (command_array[i++]);
	}

	/* Obtain the next command (command 0) and remove it from the array */
	data->input_line = command_array[0];
	for (i = 0; command_array[i]; i++)
	{
		command_array[i] = command_array[i + 1];
		operator_array[i] = operator_array[i + 1];
	}

	return (str_length(data->input_line));
}

/**
 * check_logical_operators - Check and split for '&&' and '||' operators.
 * @commands: Array of commands.
 * @index: Index of the command to be checked.
 * @operators: Array of logical operators corresponding to each command.
 *
 * Return: Index of the last command in the array.
 */
int check_logical_operators(char *commands[], int index, char operators[])
{
	char *temp = NULL;
	int i;

	/* Check for the '&' and '|' characters in the command line */
	for (i = 0; commands[index] != NULL && commands[index][i]; i++)
	{
		if (commands[index][i] == '&' && commands[index][i + 1] == '&')
		{
			/* Split the line when '&&' is found */
			temp = commands[index];
			commands[index][i] = '\0';
			commands[index] = str_duplicate(commands[index]);
			commands[index + 1] = str_duplicate(temp + i + 2);
			index++;
			operators[index] = '&';
			free(temp);
			i = 0;
		}
		else if (commands[index][i] == '|' && commands[index][i + 1] == '|')
		{
			/* Split the line when '||' is found */
			temp = commands[index];
			commands[index][i] = '\0';
			commands[index] = str_duplicate(commands[index]);
			commands[index + 1] = str_duplicate(temp + i + 2);
			index++;
			operators[index] = '|';
			free(temp);
			i = 0;
		}
	}
	return (index);
}
