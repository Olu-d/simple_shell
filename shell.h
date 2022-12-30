#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
char *get_commands(char [], char **);
int create_child(char **argv, char *envp[], char *prog_name);
size_t getlen(char []);
void printenv(char **);
int file_exists(const char *);
int non_interactive(char **, char **);
int interactive(char **, char **);
#endif
