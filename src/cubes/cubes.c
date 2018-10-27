#include "cubes.h"

// Check if the string of the cube is legal. //
int check_cube(char *cube, int length)
{
	if ((length % 2) != 0)
	{
		printf(RED"Cube %s representation is wrong! Cubes must be represented with even columns!\n"NRM, cube);
		return RETURN_FAILURE;
	}

	for (int i = 0; i < length; i++)
	{
		if ((cube[i] != '0') && (cube[i] != '1'))
		{
			printf(RED"Cube %s representation is wrong! Cubes must be represented only with '0' and '1'!\n"NRM, cube);
			return RETURN_FAILURE;
		}
	}

	return RETURN_SUCCESS;
}

// Find the intersection between two cubes. //
char *find_intersect_2(char *cube1, char *cube2, int length)
{
	char *result = NULL;
	int intesectResult;
	int i;

	result = (char *) calloc((length + 1), sizeof(char));

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
	int result = 0;

	for (int i = 0; i < length; i+=2)
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