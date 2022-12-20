#include"main.h"

void get_commands(char [], char **);
void create_child(char **argv, char *envp[], char *prog_name);
size_t getlen(char []);
void printenv(char **);
/**
 * main - Function creates a simple interactive shell.
 * @argc: Variable holding the number of args passed to the main function.
 * @argv: A pointer to an array of strings(the arguments passed to the
 * function.
 * @env: Pointer to array holding system's environment variables.
 *
 * Description: Function creates a simple interactive shell.
 *
 * Return: 0 if successful.
 */
int main(__attribute__ ((unused)) int argc, char *argv[], char *env[])
{
	size_t size;
	int line, same, _env;
	static char *prog_name;
	char *lineptr;

	prog_name = argv[0];
	size = 0;
	lineptr = NULL;
	while (1)
	{
		dprintf(STDOUT_FILENO, "%s", "#cisfun$");
		line = getline(&lineptr, &size, stdin);
		if (line != -1)
		{
			get_commands(lineptr, argv);
			same = strcmp(argv[0], "exit");
			_env = strcmp(argv[0], "env");
			if (same == 0)
				exit(0);
			if (_env == 0)
			{
				printenv(env);
				continue;
			}
			create_child(argv, env, prog_name);
		}
	}
	return (0);
}

