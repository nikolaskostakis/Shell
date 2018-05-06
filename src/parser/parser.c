#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"
#include "parser.h"

int check_first_token(char *string)
{
	const char hash = '#';
	size_t length = 0;
	int i;

	length = strlen(string);

	// Check if the string is the size of one character
	if (length == 1)
	{
		if (string[0] == hash) // If the character is equal to the hash 
			return IS_HASH;  // Return IS_HASH
		else // If it is not
			return IS_SYNTAX_ERRROR;  // Return Syntax Error
	}

	// Check if string is ROW
	if (!strcmp(string, ROW))
		return IS_ROW;
	// Check if string is IO
	if (!strcmp(string, IO))
		return IS_IO;
	// Check if string is COMPONENT
	if (!strcmp(string, COMPONENT))
		return IS_COMPONENT;

	// Check each character of the string if it equal to the hash
	for (i = 0; i < length; i++)
	{
		if (string[i] != hash)// If it is not equal to hash
			return IS_SYNTAX_ERRROR;  // Return Syntax Error
	}

	// IF each character is hash, then string is borderline
	return IS_BORDERLINE;
}

void parse_hash_line(char * line)
{
	const char design[] = "Design";
	const char core[] = "Core";
	char *token = NULL;

	// Ignore first token, '#'
	token = strtok(line, DELIMITERS);

	token = strtok(NULL, DELIMITERS);
}

void parse_file(char *filename)
{
	FILE *fp = NULL;
	char *line = NULL;
	char *token = NULL;
	size_t length = 0;
	int first_token = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("fopen");
		exit(1);
	}

	while((getline(&line, &length, fp)) != -1)
	{
		token = strtok(line, DELIMITERS);

		first_token = check_first_token(token);
		switch (first_token)
		{
			case IS_BORDERLINE:
				free(line);
				continue;
			case IS_SYNTAX_ERRROR:
			default:
				printf(RED"Syntax Error!\n");
				printf("Parsing has stopped!\n"NRM);
				fclose(fp);
				free(line);
				return;
		}

		free(line);
	}
	
	fclose(fp);
	free(line);
}