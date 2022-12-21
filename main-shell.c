#include <sys/wait.h>
#include <stddef.h>
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
/**
  * main - entry point of our program
  * @ac: the number of arguments of the program
  * @av: the arguments array
  * Return: 0 for success, -1 on failure;
  */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	char *line = NULL, **tokens = NULL;
	size_t size = 0;
	int val;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		getline(&line, &size, stdin);
		tokens = fillArguments(line);
		if (tokens == NULL)
			return (-1);

		pid = fork();
		if (pid == -1)
			return (-1);

		if (pid == 0)
		{
			val = execve(tokens[0], tokens, environ);
			if (val == -1)
				perror("Error");
		}
		else
		{
			wait(NULL);
		}
		free(tokens);
		free(line);
	}
	return (0);
}


/**
  * fillArguments - function to fill arguments in an array
  * @line: the buffer filled by the stdin
  * Return: the array containing the arguments
  */
char **fillArguments(char *line)
{
	int i = 0, j = 0;
	char *token, **tokens = NULL;

	tokens = malloc(strlen(line) * sizeof(char));
	if (tokens == NULL)
	{
		printf("Error, unable to allocate memory\n");
		return (NULL);
	}

	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	while (tokens[i - 1][j] != '\n')
		j++;
	tokens[i - 1][j] = '\0';
	tokens[i] = NULL;
	return (tokens);
}
