#include"main.h"

/**
 * create_child - Function forks a child process and executes command fed via
 * argv.
 * @argv: Pointer to array containing strings of commands.
 * @env: Pointer to array containing the system's environmnetal variables.
 * @prog_name: The name of the calling program.
 * Description: Function forks a child process and executes command fed via
 * argv.
 * Return: Nothing.
 */
void create_child(char **argv, char **env, char *prog_name)
{
	pid_t child, stat;
	int status, exec_status;

	child = fork();
	if (child < 0)
	{
		dprintf(STDOUT_FILENO, "Error: Unable to create child process\n");
		exit(99);
	}
	else if (child == 0)
	{
		exec_status = execvp(*argv, argv);
		if (exec_status == -1)
		{
			dprintf(STDOUT_FILENO, "%s: No such file or directory\n", prog_name);
			exit(100);
		}
	}
	else
	{
		while (stat != child)
			stat = wait(&status);

	}
}

