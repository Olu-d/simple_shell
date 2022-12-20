#include"main.h"

/**
 * printenv - Function prints the environment variables.
 * @env: Pointer to the array containing the environment variables.
 *
 * Description: Function prints the environment variables.
 *
 * Return: Nothing.
 */
void printenv(char **env)
{
	int len;

	len = 0;
	while (env[len] != NULL)
	{
		dprintf(STDOUT_FILENO, "%s\n", env[len]);
		len++;
	}
}
