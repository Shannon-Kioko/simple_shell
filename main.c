#include "shell.h"

/**
 * main - Entry point of the program.
 * @argc: Number of values received from the command line.
 * @argv: Values received from the command line.
 * @env: Environment variables passed to the program.
 * Return: 0 on success.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	data_init(data, argc, argv, env);
	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/* We are in the terminal, interactive mode */
		errno = 2;
		prompt = PROMPT_MSG;
	}

	errno = 0;
	prompt_loop(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - Handles the SIGINT signal (ctrl + c) by printing a new line.
 * @signal_number: Unused parameter.
 */
void handle_ctrl_c(int signal_number)
{
	if (signal_number == SIGINT)
	{
        print_string("Received SIGINT signal\n");
	}
	print_string("\n");
	print_string(PROMPT_MSG);
}

/**
 * data_init - Initializes the data_of_program struct with program information.
 * @data: Pointer to the structure of data.
 * @argc: Number of values received from the command line.
 * @argv: Array of arguments passed to the program execution.
 * @env: Environment variables passed to the program execution.
 */
void data_init(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	/* Define the file descriptor to be read */
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			print_error_str(data->program_name);
			print_error_str(": 0: Can't open ");
			print_error_str(argv[1]);
			print_error_str("\n");
			exit(127);
		}
	}
	data->tokens = NULL;

	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * prompt_loop - Infinitely prompts for user input and executes commands.
 * @prompt: Prompt to be printed.
 * @data: Pointer to the structure of data.
 */
void prompt_loop(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		print_string(prompt);

		error_code = string_len = get_input_line(data);

		if (error_code == EOF)
		{
			free_all(data);
			exit(errno); /* If EOF is the first character of the string, exit */
		}

		if (string_len >= 1)
		{
			expand_alias(data);
			expand_var(data);
			tokenize(data);

			if (data->tokens[0])
			{
				/* If text is given to the prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					print_err(error_code, data);
			}

			free_recurrent_data(data);
		}
	}
}
