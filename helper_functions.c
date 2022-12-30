#include <unistd.h>
/**
 * file_exists - checks if a file exists and what permissions are granted.
 * @fname: The filename.
 *
 * Description: Checks if a file exists and what permissions are granted.
 *
 * Return: 0 if it exists, -1 otherwise
 */
int file_exists(const char *fname)
{
	return access(fname, F_OK) == 0;
}
