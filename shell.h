#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <stdlib.h>
#include <unistd.h> /* for fork, execve*/
#include <stddef.h>
#include <string.h> /* for strtok*/
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <errno.h> /* for errno and perror */
#include <fcntl.h> /* for open files*/
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <stdbool.h>

/************* MACROS **************/

#include "macros.h" /* for message help and prompt */

/************* STRUCTURES **************/

/**
 * struct program_info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @tokens: pointer to array of tokenized input
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 *
 * Description: contains information on various struct members
 */
typedef struct program_info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtin_func - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 * Description: builtin function for the stuct
 */
typedef struct builtin_func
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;

typedef struct BuiltinPair
{
	char *builtin;
	int (*function)(data_of_program *);
} BuiltinPair;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Initialize the struct with the info of the program */
void data_init(data_of_program *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void prompt_loop(char *prompt, data_of_program *data);

/* Prints the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read one line of the stdin*/
int get_input_line(data_of_program *data);

/* Split the line for logical operators if they exist */
int check_logical_operators(char *commands[], int index, char operators[]);

/*======== shell_utils.c ========*/

/* check if a string represents a valid integer */
bool is_number(const char *str);

/*  check if a string contains a specific character. */
bool has_character(const char *str, char c);

/* check if a file exists at the given path. */
/* bool check_file(const char *file_path); */


/*======== expansions.c ========*/

/* expand variables */
void expand_var(data_of_program *data);

/* expand aliases */
void expand_alias(data_of_program *data);

/* append a string to the end of the buffer*/
int buffer_append(char *buffer, char *str);


/*======== str_tok.c ========*/

/* Separate the string in tokens  - uses designed delimiter */
void tokenize(data_of_program *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(data_of_program *data);


/*======== builtins_list.c ========*/

/* If a match is found for a built-in, executes it */
int builtin_executes(data_of_program *data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Search for a program in the PATH directories */
int search_prog_in_path(data_of_program *data);

/* check if a file exists and is executable. */
int check_file(char *full_path); 


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for array of pointers  */
void free_array_of_pointers(char **arr);

/* Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* show help information */
int builtin_help(data_of_program *data);

/* set, unset and show aliases */
int builtin_alias(data_of_program *data);


/*======== builtins_env.c ========*/

/* Description: Shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* create or override a variable of env */
int builtin_set_env(data_of_program *data);

/* delete a variable of env */
int builtin_unset_env(data_of_program *data);

int builtins_list(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the env */
int env_remove_key(char *key, data_of_program *data);

/* print the current environment */
void print_env(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int print_string(char *str);

/* Prints a string in the stderr */
int print_error_str(char *str);

/* Prints an error message based on the error code */
int print_err(int err_code, data_of_program *data);


/************** HELPERS FOR STRING MGT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Convert a long number to a string */
void long_to_string(long num, char *str, int base);

/* convert a string to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_character_occurences(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(data_of_program *data, char *alias_name);

/* get the alias name */
char *get_alias(data_of_program *data, char *name);

/* set the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif /* SHELL_H */
