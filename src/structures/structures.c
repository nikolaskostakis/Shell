#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"
#include "structures.h"

char *design_name = NULL;
double core_utilisation = 0;

// Core dimentions
double core_width = 0;
double core_height = 0;
double aspect_ratio = 0;
double core_X_offset = 0;
double core_Y_offset = 0;

// Row Table
struct row *RowT = NULL;
unsigned int rowT_size = 0;

void insert_row(char *name, char *type, double location_x, double location_y, double width, double height)
{
	struct row *ptr = NULL;

	RowT = (struct row *) realloc(RowT, ((rowT_size + 1) * sizeof(struct row)));
	if (RowT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
	}

	RowT[rowT_size].name = name;
	RowT[rowT_size].type = type;
	RowT[rowT_size].location_x = location_x;
	RowT[rowT_size].location_y = location_y;
	RowT[rowT_size].width = width;
	RowT[rowT_size].height = height;

	rowT_size++;
}

void print_rows()
{
	unsigned int i;

	if (rowT_size == 0)
	{
		printf("Row Table empty!\n");
		return;
	}

	for (i = 0; i < rowT_size; i++)
	{
		printf("Row: %s\n", RowT[i].name);
		printf("\tType: %s\n", RowT[i].type);
		printf("\tLocation (X,Y): (%lf,%lf)\n", RowT[i].location_x, RowT[i].location_y);
		printf("\tSize (Width,Height): (%lf,%lf)\n", RowT[i].width, RowT[i].height);
	}
}

void free_row_table()
{
	unsigned int i;

	for (i = 0; i < rowT_size; i++)
	{
		free(RowT[i].name);
		free(RowT[i].type);
	}

	free(RowT);
	RowT = NULL;
	rowT_size = 0;
}