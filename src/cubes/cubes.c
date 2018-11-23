#include "cubes.h"

// Check if the cube is valid, meaning not having an element 00 //
int check_cube_validity(char *cube, int length)
{
	int i;

	for (i = 0; i < length; i+=2)
	{
		if ((cube[i] == '0') && (cube[i + 1] == '0'))
		{
			return RETURN_FAILURE;
		}
	}

	return RETURN_SUCCESS;
}

// Check if the string of the cube is legal. //
// The legality of the cube is checked by its length, its content and if it is valid. //
int check_cube(char *cube, int length)
{
	int i;

	// Length check //
	if ((length % 2) != 0)
	{
		printf(RED"Cube %s representation is wrong! Cubes must be represented with even columns!\n"NRM, cube);
		return RETURN_FAILURE;
	}

	// Content check //
	for (i = 0; i < length; i++)
	{
		if ((cube[i] != '0') && (cube[i] != '1'))
		{
			printf(RED"Cube %s representation is wrong! Cubes must be represented only with '0' and '1'!\n"NRM, cube);
			return RETURN_FAILURE;
		}
	}

	// Validity check //
	if (check_cube_validity(cube, length) == RETURN_FAILURE)
	{
		printf(RED"Cube %s is invalid!\n"NRM, cube);
		return RETURN_FAILURE;
	}

	return RETURN_SUCCESS;
}

// Chech if the cube already exists into the list. //
int check_duplicate_cube(char *cube, char **list, int listLength)
{
	int i;

	// Run through the list. //
	for (i = 0; i < listLength; i++)
	{
		// If the cube exists, terminate the search. // 
		if (strcmp(list[i], cube) == 0)
		{
			return RETURN_SUCCESS;
		}
	}

	return RETURN_FAILURE;
}

// Find the intersection between two cubes. //
char *find_intersect_2(char *cube1, char *cube2, int length)
{
	char *result = NULL;
	int intesectResult;
	int i;

	result = (char *) calloc((length + 1), sizeof(char));
	if (result == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	// To perform the and operator, the characters are transformed to //
	// numbers and their result is turned back to a character //
	for (i = 0; i < length; i++)
	{
		intesectResult = (cube1[i] - '0') & (cube2[i] - '0');
		result[i] = intesectResult + '0';
	}

	return result; 
}

// Find the supercube of the two cubes. //
char *find_supercube_2(char *cube1, char *cube2, int length)
{
	char *result = NULL;
	int supercubeResult;
	int i;

	result = (char *) calloc((length + 1), sizeof(char));
	if (result == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	// To perform the and operator, the characters are transformed to //
	// numbers and their result is turned back to a character //
	for (i = 0; i < length; i++)
	{
		supercubeResult = (cube1[i] - '0') | (cube2[i] - '0');
		result[i] = supercubeResult + '0';
	}

	return result; 
}

// Find the distance between two cubes by counting //
// the pair of "00" from their intersection.       //
int find_distance(char *intersection, int length)
{
	int i;
	int result = 0;

	// Run throug the intersection result //
	for (i = 0; i < length; i+=2)
	{
		// For every invalid element found there, increase the distance //
		if ((intersection[i] == '0') && (intersection[i + 1] == '0'))
		{
			result++;
		}
	}

	return result;
}

// Find if the first cube covers the second cube. The coverage is achieved //
// if the first cube is bitwise greater or equal than the second cube.     //
int find_cube_cover_2(char *cube1, char *cube2, int length)
{
	int i;

	for (i = 0; i < length; i++)
	{
		if ((cube1[i] - '0') < (cube2[i] - '0'))
		{
			return RETURN_FAILURE;
		}
	}

	return RETURN_SUCCESS; 
}

// Get the cube produced from sharp (#) on the kth element of the two cubes. //
char *get_sharped_cube(char *cube1, char *cube2, int length, int k)
{
	int i;
	char product[2];
	char *result = NULL;

	result = (char *) calloc((length + 1), sizeof(char));
	if (result == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	// Run through the cube. //
	for (i = 0; i < length; i+=2)
	{
		// If the element is not the kth one. //
		if (i != k)
		{
			// If it is not, copy the cube's element to the result. //
			result[i] = cube1[i];
			result[i + 1] = cube1[i + 1];
			continue;
		}

		// If it is, change the element. //
		product[0] = ((cube1[i] - '0') & (!(cube2[i] - '0'))) + '0';
		product[1] = ((cube1[i + 1] - '0') & (!(cube2[i + 1] - '0'))) + '0';

		// Check validity of cube's element. // 
		if ((product[0] == '0') && (product[1] == '0'))
		{
			free(result);
			result = NULL;
			break;
		}

		// Store the valid element. //
		result[i] = product[0];
		result[i + 1] = product[1];
	}

	return result;
}

// Return a list of sharped cubes //
char **find_sharp_2_set(char *cube1, char *cube2, int length, int *listLength)
{
	int i, j;
	char **result = NULL;
	char *temp = NULL;

	for (i = 0, j = 0; i < length; i+=2)
	{
		// Get the sharped cube for the i/2 element
		temp = get_sharped_cube(cube1, cube2, length, i);
		// If there was not produced one, continue //
		if (temp == NULL)
		{
			continue;
		}

		// If the result is not duplicate //
		if (check_duplicate_cube(temp, result, j) == RETURN_FAILURE)
		{
			// Store it //
			result = (char **) realloc(result, ((j + 1) * sizeof(char *)));
			if (result == NULL)
			{
				printf(RED"Error! Unable to allocate memory\n"NRM);
				exit(1);
			}
			result[j] = temp;
			j++;
		}
	}

	*listLength = j;
	return result;
}

char **find_sharp_set(char ***sharpSets, int *sharpSetsLength, int sharpSetsNumber, int cubeLength, int *listLength)
{
	int i, j, s;
	char *interResult = NULL;
	char **result = NULL;
	char **tempResult = NULL;
	int resultLength = 0;
	int tempResultLength = 0;

	// first is the result
	result = sharpSets[0];
	resultLength = sharpSetsLength[0];
	// Run through the rest of the sharp sets //
	for (s = 1; s < sharpSetsNumber; s++)
	{
		// Make the result temporary
		tempResult = result;
		result = NULL;
		tempResultLength = resultLength;
		resultLength = 0;

		// Run through the temp result list //
		for (i = 0; i < tempResultLength; i++)
		{
			// For each element of the temp list do intersections with the next sharp set //
			for (j = 0; j < sharpSetsLength[s]; j++)
			{
				interResult = find_intersect_2(tempResult[i], *(sharpSets[s] + j), cubeLength);

				// Check if the result of the intersect is not valid //
				if (check_cube_validity(interResult, cubeLength) == RETURN_FAILURE)
				{
					free(interResult);
					continue;
				}

				// If the result is not a duplicate //
				if (check_duplicate_cube(interResult, result, resultLength) == RETURN_FAILURE)
				{
					// Store it to the set //
					result = (char **) realloc(result, (resultLength + 1) * sizeof(char *));
					if (result == NULL)
					{
						printf(RED"Error! Unable to allocate memory\n"NRM);
						exit(1);
					}
					result[resultLength] = interResult;
					resultLength++;
				}
				else
				{
					free(interResult);
				}
			}
		}

		free_sharp_set(tempResult, tempResultLength);
		free_sharp_set(sharpSets[s], sharpSetsLength[s]);
	}

	free(sharpSets);
	free(sharpSetsLength);

	*listLength = resultLength;
	return result;
}

void print_sharp_2_set(char *cube1, char *cube2, char **list, int length)
{
	int i;

	printf("Cube %s # cube %s:\n", cube1, cube2);

	if (length == 0)
	{
		printf(MAG"\t(null)\n"NRM);
		return;
	}

	for (i = 0; i < length; i++)
	{
		printf(MAG"\t%s\n"NRM, list[i]);
	}
}

void free_sharp_set(char **list, int length)
{
	int i;

	for (int i = 0; i < length; i++)
	{
		free(list[i]);
	}

	free(list);

}

// Create a universe cube //
char *create_universe(int length)
{
	int i;
	char *result = NULL;

	result = (char *) calloc((length + 1), sizeof(char));
	if (result == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	for (i= 0; i < length; i++)
	{
		result[i] = '1';
	}

	return result;
}