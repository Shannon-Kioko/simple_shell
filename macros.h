#ifndef HELPERS_H
#define HELPERS_H

/* Prompt to be displayed */
#define PROMPT_MSG "$" /* Required for signal handling. */

/* Resume from the unused attribute */
#define UNUSED __attribute__((unused))

/* Buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRINGS FOR HELP BUILT-IN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the working directory.\n\n"\
"	If no argument is provided, the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	If the argument is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit the shell.\n\n"\
"	Exits the shell with a status of N. If N is omitted, the exit status\n"\
"	is that of the last executed command.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment variables.\n\n"\
"	The env command will print a complete list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	Initializes a new environment variable or modifies an existing one.\n"\
"	Prints an error message if the correct number of arguments is not provided.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	Deletes a variable from the environment.\n\n"\
"	Prints an error message if the correct number of arguments is not provided.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about builtin commands.\n\n"\
"	Displays brief summaries of builtin commands. If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise, the list of help topics is printed. BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
