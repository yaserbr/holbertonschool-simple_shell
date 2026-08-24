#include "shell.h"

/**
 * count_words - counts space/tab separated words in a string
 * @line: the string to scan
 *
 * Return: the number of words found
 */
size_t count_words(const char *line)
{
	size_t count = 0;
	int in_word = 0;

	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		line++;
	}

	return (count);
}

/**
 * split_line - splits a line into an array of word tokens
 * @line: the line to split, modified in place by strtok
 *
 * Description: tokens in the returned array point into @line itself,
 * so the array must be freed by the caller, but its strings must not.
 *
 * Return: a NULL-terminated array of tokens, or NULL on malloc failure
 */
char **split_line(char *line)
{
	char **argv;
	size_t i = 0;
	char *token;

	argv = malloc(sizeof(char *) * (count_words(line) + 1));
	if (argv == NULL)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}
