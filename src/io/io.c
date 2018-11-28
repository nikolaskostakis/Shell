#include "io.h"

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
	const char design[] = "Design:";
	
	const char core[] = "Core";
	const char utilisation[] = "Utilisation:";
	const char width[] = "Width,";
	const char height[] = "Height:";
	const char aspect[] = "Aspect";
	const char ratio[] = "Ratio:";
	const char x[] = "X,";
	const char y[] = "Y";
	const char offsets[] = "Offsets:";

	char *token = NULL;

	// Ignore first token, '#'
	token = strtok(line, DELIMITERS);

	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}

	// Design Name
	if (!strcmp(token, design))
	{
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		design_name = strdup(token);

		token = strtok(NULL, DELIMITERS);
		if (token != NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		return;
	}

	// Comment
	if (strcmp(token, core))
		return;

	// Core
	token = strtok(NULL, DELIMITERS);

	// Core Utilisation
	if (!strcmp(token, utilisation))
	{
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		core_utilisation = atof(token);

		token = strtok(NULL, DELIMITERS);
		if (token != NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		return;
	}
	
	// Core Width, Height
	if (!strcmp(token, width))
	{
		token = strtok(NULL, DELIMITERS);
		if ((token == NULL) || (strcmp(token, height)))
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		// Width
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		core_width = atof(token);

		// Height
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		core_height = atof(token);

		token = strtok(NULL, DELIMITERS);
		if ((token == NULL) || (strcmp(token, aspect)))
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		token = strtok(NULL, DELIMITERS);
		if ((token == NULL) || (strcmp(token, ratio)))
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		aspect_ratio = atof(token);

		token = strtok(NULL, DELIMITERS);
		if (token != NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		return;
	}

	// Core X, Y Offsets
	if (!strcmp(token, x))
	{
		token = strtok(NULL, DELIMITERS);
		if ((token == NULL) || (strcmp(token, y)))
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		token = strtok(NULL, DELIMITERS);
		if ((token == NULL) || (strcmp(token, offsets)))
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		// X Offset
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		core_X_offset = atof(token);

		// Y Offset
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		core_Y_offset = atof(token);

		token = strtok(NULL, DELIMITERS);
		if (token != NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		return;
	}

	// Syntax Error
	printf(RED"Syntax Error!\n"NRM);
	exit(1);
}

void parse_row_line(char * line)
{
	const char type[] = "Type:";
	const char location[] = "Location:";
	const char wid_hei[] = "Width/Height:";

	char *token = NULL;
	char *row_name = NULL;
	char *row_type = NULL;
	double location_x = 0;
	double location_y = 0;
	double width = 0;
	double height = 0;

	// Ignore first token, "Row"
	token = strtok(line, DELIMITERS);

	// Row Name
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	row_name = strdup(token);

	// Type
	token = strtok(NULL, DELIMITERS);
	if ((token == NULL) || (strcmp(token, type)))
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}

	// Row Type
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	row_type = strdup(token);

	// Location
	token = strtok(NULL, DELIMITERS);
	if ((token == NULL) || (strcmp(token, location)))
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}

	// Location X
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	location_x = atof(token);

	// Location Y
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	location_y = atof(token);

	// Width/Height
	token = strtok(NULL, DELIMITERS);
	if ((token == NULL) || (strcmp(token, wid_hei)))
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}

	// Width
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	width = atof(token);

	// Height
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	height = atof(token);

	insert_row(row_name, row_type, location_x, location_y, width, height);
}

void parse_io_line(char *line)
{
	const char location[] = "Location:";
	const char ccs[] = "CCs:";

	char *token = NULL;
	char *name = NULL;

	double x = 0;
	double y = 0;

	// Ignore first token, "IO:"
	token = strtok(line, DELIMITERS);

	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	name = strdup(token);

	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}

	// If token is location, the its the initial definition of the IO pin
	if (!strcmp(token, location))
	{
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		x = atof(token);

		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		y = atof(token);
		
		token = strtok(NULL, DELIMITERS);
		if (token != NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		insert_io(name, x, y);
		return;
	}

	// If token is ccs, then its the connections of the IO pin
	// If not its syntax error
	if (strcmp(token, ccs))
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}

	//  Check for connections
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
		return;

	insert_io_net(strdup(name), strdup(token));

	token = strtok(NULL, DELIMITERS);
	
	// It is not a must to have a connection
	while (token != NULL)
	{
		insert_io_net(strdup(name), strdup(token));
		token = strtok(NULL, DELIMITERS);
	}
}

void parse_comp_line(char *line)
{
	const char ccs[] = "CCs:";

	char *token = NULL;
	char *name = NULL;

	// Ignore first token, "Component:"
	token = strtok(line, DELIMITERS);

	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}
	name = strdup(token);
	insert_component(name);

	token = strtok(NULL, DELIMITERS);
	if ((token == NULL) || (strcmp(token, ccs)))
	{
		printf(RED"Syntax Error!\n"NRM);
		exit(1);
	}

	//  Check for connections
	token = strtok(NULL, DELIMITERS);
	if (token == NULL)
		return;

	insert_net(strdup(name), strdup(token));

	token = strtok(NULL, DELIMITERS);
	while (token != NULL)
	{
		insert_net(strdup(name), strdup(token));
		token = strtok(NULL, DELIMITERS);
	}
}

// Parse the design file. Depending on the first token of the line, //
// the corresponding function will be called to handle the line.    //
void parse_design_file(FILE *fp)
{
	char *line = NULL;
	char *copy_line = NULL;
	char *token = NULL;
	size_t length = 0;
	int first_token = 0;

	while((getline(&line, &length, fp)) != -1)
	{
		copy_line = strdup(line);
		token = strtok(copy_line, DELIMITERS);
		first_token = check_first_token(token);
		free(copy_line);
		switch (first_token)
		{
			case IS_BORDERLINE:
				continue;
			case IS_HASH:
				parse_hash_line(line);
				continue;
			case IS_ROW:
				parse_row_line(line);
				continue;
			case IS_IO:
				parse_io_line(line);
				continue;
			case IS_COMPONENT:
				parse_comp_line(line);
				continue;
			case IS_SYNTAX_ERRROR:
			default:
				printf(RED"Syntax Error!\n");
				printf("Parsing has stopped!\n"NRM);
				fclose(fp);
				return;
		}
	}
	
	fclose(fp);
	free(line);

	printf(GRN"File parsed successfully!\n"NRM);
}

void parse_graph_file(FILE *fp)
{	
	char *line = NULL;
	char *token = NULL;
	char *sourceNode = NULL;
	char *destNode = NULL;
	size_t length = 0;
	double edgeWeight = 0;
	unsigned int sourceNodeLocation = 0;
	unsigned int destNodeLocation = 0;

	while((getline(&line, &length, fp)) != -1)
	{
		// First token: source node //
		token = strtok(line, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		sourceNode = strdup(token);

		// Second token: arrow //
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		if (strcmp(token, ARROW) != 0)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		// Third token: destination node //
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		destNode = strdup(token);

		// Fourth token: weight //
		token = strtok(NULL, DELIMITERS);
		if (token == NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}
		edgeWeight = atof(token);

		// If there are more tokens following, error //
		token = strtok(NULL, DELIMITERS);
		if (token != NULL)
		{
			printf(RED"Syntax Error!\n"NRM);
			exit(1);
		}

		// Insert nodes //
		if (search_node(sourceNode, &sourceNodeLocation) == RETURN_FAILURE)
		{
			insert_node(sourceNode, &sourceNodeLocation);
		}
		if (search_node(destNode, &destNodeLocation) == RETURN_FAILURE)
		{
			insert_node(destNode, &destNodeLocation);
		}

		insert_edge(sourceNodeLocation, destNodeLocation, edgeWeight);
	}

	free(line);
}

void write_graph_file(FILE *fp)
{
	unsigned int i;

	for(i = 0; i < edgeTSize; i++)
	{
		fprintf(fp, "%s -> %s %lf\n", NodeT[EdgeT[i].source].name, NodeT[EdgeT[i].destination].name, EdgeT[i].weight);
	}
	
}
