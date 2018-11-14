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
int check_cube(char *cube, int length)
{
	int i;

	if ((length % 2) != 0)
	{
		printf(RED"Cube %s representation is wrong! Cubes must be represented with even columns!\n"NRM, cube);
		return RETURN_FAILURE;
	}

	for (i = 0; i < length; i++)
	{
		if ((cube[i] != '0') && (cube[i] != '1'))
		{
			printf(RED"Cube %s representation is wrong! Cubes must be represented only with '0' and '1'!\n"NRM, cube);
			return RETURN_FAILURE;
		}
	}

	if (check_cube_validity(cube, length) == RETURN_FAILURE)
	{
		printf(RED"Cube %s is invalid!\n"NRM, cube);
		return RETURN_FAILURE;
	}

	return RETURN_SUCCESS;
}

int check_duplicate_cube(char *cube, char **list, int listLength)
{
	int i;

	for (i = 0; i < listLength; i++)
	{
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

	for (i = 0; i < length; i+=2)
	{
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

	for (i = 0; i < length; i+=2)
	{
		if (i != k)
		{
			result[i] = cube1[i];
			result[i + 1] = cube1[i + 1];
			continue;
		}

		// Check validity of cube's element // 
		product[0] = ((cube1[i] - '0') & (!(cube2[i] - '0'))) + '0';
		product[1] = ((cube1[i + 1] - '0') & (!(cube2[i + 1] - '0'))) + '0';

		if ((product[0] == '0') && (product[1] == '0'))
		{
			free(result);
			result = NULL;
			break;
		}

		result[i] = product[0];
		result[i + 1] = product[1];
	}

	return result;
}

char **find_sharp_2_set(char *cube1, char *cube2, int length, int *listLength)
{
	int i, j;
	char **result = NULL;
	char *temp = NULL;

	for (i = 0, j = 0; i < length; i+=2)
	{
		temp = get_sharped_cube(cube1, cube2, length, i);

		if (temp == NULL)
		{
			continue;
		}

		result = (char **) realloc(result, ((j + 1) * sizeof(char *)));
		if (result == NULL)
		{
			printf(RED"Error! Unable to allocate memory\n"NRM);
			exit(1);
		}
		result[j] = temp;
		j++;
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
					continue;
				}

				// If the result is valid and not a duplicate, then it to the set //
				result = (char **) realloc(result, (resultLength + 1) * sizeof(char *));
				if (result == NULL)
				{
					printf(RED"Error! Unable to allocate memory\n"NRM);
					exit(1);
				}

				if (check_duplicate_cube(interResult, result, resultLength) == RETURN_FAILURE)
				{
					result[resultLength] = interResult;
					resultLength++;
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