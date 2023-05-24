#include "shell.h"

/**
 * builtin_exit - exit the program with the specified status.
 * @data: struct for the program's data.
 * Return: zero if success, or a non-zero number if an error occurs.
 */
int builtin_exit(data_of_program *data)
{
	int exit_status = 0;

	if (data->tokens[1] != NULL) {
		/* Check if the argument is a valid number */
		if (!is_number(data->tokens[1])) {
			errno = EINVAL;
			return 2;
		}

		exit_status = _atoi(data->tokens[1]);
	}

	free_all(data);
	exit(exit_status);
}

/**
 * builtin_cd - change the current directory.
 * @data: struct for the program's data.
 * Return: zero if success, or a non-zero number if an error occurs.
 */
int builtin_cd(data_of_program *data)
{
	char *dir_home = env_get_key("HOME", data);
	char *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1]) {
		if (str_compare(data->tokens[1], "-", 0)) {
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old) {
				error_code = set_work_directory(data, dir_old);
			}
			_print(env_get_key("PWD", data));
			_print("\n");

			return error_code;
		} else {
			return set_work_directory(data, data->tokens[1]);
		}
	} else {
		if (!dir_home) {
			dir_home = getcwd(old_dir, sizeof(old_dir));
		}

		return set_work_directory(data, dir_home);
	}

	return 0;
}

/**
 * set_work_directory - set the working directory.
 * @data: struct for the program's data.
 * @new_dir: path to be set as the working directory.
 * Return: zero if success, or a non-zero number if an error occurs.
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, sizeof(old_dir));

	if (!str_compare(old_dir, new_dir, 0)) {
		err_code = chdir(new_dir);
		if (err_code == -1) {
			errno = ENOENT;
			return 3;
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return 0;
}

/**
 * builtin_help - display help information for built-in commands.
 * @data: struct for the program's data.
 * Return: zero if success, or a non-zero number if an error occurs.
 */
int builtin_help(data_of_program *data)
{
	char *help_messages[] = {
		"Help message for the shell.",
		"Help message for the exit command.",
		"Help message for the env command.",
		"Help message for the setenv command.",
		"Help message for the unsetenv command.",
		"Help message for the cd command."
	};

	int num_messages = sizeof(help_messages) / sizeof(help_messages[0]);
	int i;

	if (data->tokens[1] == NULL) {
		_print(help_messages[0] + 6);
		return 1;
	}

	if (data->tokens[2] != NULL) {
		errno = E2BIG;
		perror(data->command_name);
		return 5;
	}

	for (i = 1; i < num_messages; i++) {
		if (str_compare(data->tokens[1], help_messages[i], 0)) {
			_print(help_messages[i] + str_length(data->tokens[1]) + 1);
			return 1;
		}
	}

	errno = EINVAL;
	perror(data->command_name);
	return 0;
}

/**
 * builtin_alias - add, remove, or show aliases.
 * @data: struct for the program's data.
 * Return: zero if success, or a non-zero number if an error occurs.
 */
int builtin_alias(data_of_program *data)
{
	int i = 0;

	if (data->tokens[1] == NULL) {
		return print_alias(data, NULL);
	}

	while (data->tokens[++i]) {
		if (has_character(data->tokens[i], '=')) {
			set_alias(data->tokens[i], data);
		} else {
			print_alias(data, data->tokens[i]);
		}
	}

	return 0;
}
