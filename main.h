#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void get_commands(char [], char **);
void create_child(char **argv, char *envp[], char *prog_name);
size_t getlen(char []);
void printenv(char **);


#endif /*ifndef SHELL_H*/
