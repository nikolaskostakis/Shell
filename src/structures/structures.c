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

// IO Table
struct io *IOT = NULL;
unsigned int ioT_size = 0;

// Component Table
struct component *ComponentT = NULL;
unsigned int componentT_size = 0;

// Net Table
struct net* NetT = NULL;
unsigned int netT_size = 0;

void insert_row(char *name, char *type, double location_x, double location_y, double width, double height)
{
	RowT = (struct row *) realloc(RowT, ((rowT_size + 1) * sizeof(struct row)));
	if (RowT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
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
		printf(YEL"Row Table empty!\n"NRM);
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

void insert_io(char *name, double x, double y)
{
	IOT = (struct io *) realloc(IOT, ((ioT_size + 1) * sizeof(struct io)));
	if (IOT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	IOT[ioT_size].name = name;
	IOT[ioT_size].x = x;
	IOT[ioT_size].y = y;

	ioT_size++;
}

int search_io(char *name, unsigned int *location)
{
	unsigned int i;

	for (i = 0; i < ioT_size; i++)
	{
		if (!strcmp(IOT[i].name, name))
		{
			*location = i;
			return RETURN_SUCCESS;
		}
	}

	return RETURN_FAILURE;
}

void print_ios()
{
	unsigned int i;

	if (ioT_size == 0)
	{
		printf(YEL"IO Table empty!\n"NRM);
		return;
	}

	for (i = 0; i < ioT_size; i++)
	{
		printf("IO: %s\n", IOT[i].name);
		printf("\tLocation (X,Y): (%lf,%lf)\n", IOT[i].x, IOT[i].y);
	}
}

void free_io_table()
{
	unsigned int i;

	for (i = 0; i < ioT_size; i++)
	{
		free(IOT[i].name);
	}

	free(IOT);
	IOT = NULL;
	ioT_size = 0;
}

void insert_component(char *name)
{
	ComponentT = (struct component *) realloc(ComponentT, ((componentT_size + 1) * sizeof(struct component)));
	if (ComponentT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	ComponentT[componentT_size].name = name;
	ComponentT[componentT_size].x = 0;
	ComponentT[componentT_size].y = 0;

	componentT_size++;
}

int search_component(char *name, unsigned int *location)
{
	unsigned int i;

	for (i = 0; i < componentT_size; i++)
	{
		if (!strcmp(ComponentT[i].name, name))
		{
			*location = i;
			return RETURN_SUCCESS;
		}
	}

	return RETURN_FAILURE;
}

void print_components()
{
	unsigned int i;

	if (componentT_size == 0)
	{
		printf(YEL"Component Table empty!\n"NRM);
		return;
	}

	for (i = 0; i < componentT_size; i++)
	{
		printf("Component: %s\n", ComponentT[i].name);
		printf("\tLocation (X,Y): (%lf,%lf)\n", ComponentT[i].x, ComponentT[i].y);
	}
}

void free_component_table()
{
	unsigned int i;

	for (i = 0; i < componentT_size; i++)
	{
		free(ComponentT[i].name);
	}

	free(ComponentT);
	ComponentT = NULL;
	componentT_size = 0;
}

int check_if_net_exists(char *edge1, char *edge2)
{
	unsigned int i;

	for (i = 0; i < netT_size; i++)
	{
		if ((!strcmp(NetT[i].edge_name_one, edge1)) && (!strcmp(NetT[i].edge_name_two, edge2)))
			return RETURN_SUCCESS;
		if ((!strcmp(NetT[i].edge_name_one, edge2)) && (!strcmp(NetT[i].edge_name_two, edge1)))
			return RETURN_SUCCESS;
	}

	return RETURN_FAILURE;
}

void insert_net(char *edge1, char *edge2)
{
	if (check_if_net_exists(edge1, edge2) == RETURN_SUCCESS)
		return;

	NetT = (struct net *) realloc(NetT, ((netT_size + 1) * sizeof(struct net)));
	if (NetT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	NetT[netT_size].edge_name_one = edge1;
	NetT[netT_size].edge_type_one = nothing;
	NetT[netT_size].edge_name_two = edge2;
	NetT[netT_size].edge_type_two = nothing;

	netT_size++;
}

void insert_io_net(char *io_edge, char *edge2)
{
	unsigned int location;
	int res;

	if (check_if_net_exists(io_edge, edge2) == RETURN_SUCCESS)
		return;

	NetT = (struct net *) realloc(NetT, ((netT_size + 1) * sizeof(struct net)));
	if (NetT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	res = search_io(io_edge, &location);

	NetT[netT_size].edge_name_one = io_edge;
	NetT[netT_size].edge_type_one = io;
	NetT[netT_size].edge_pointer_one= location;
	NetT[netT_size].edge_name_two = edge2;
	NetT[netT_size].edge_type_two = nothing;

	netT_size++;
}

void print_nets()
{
	unsigned int i;

	if (netT_size == 0)
	{
		printf(YEL"Net Table empty!\n"NRM);
		return;
	}

	for (i = 0; i < netT_size; i++)
	{
		printf("Net:\n");
		printf("\tEdge ("MAG"1"NRM"): %s\n", NetT[i].edge_name_one);
		if (NetT[i].edge_type_one == io)
			printf("\t\tType: IO\n");
		else if (NetT[i].edge_type_one == component)
			printf("\t\tType: Component\n");
		printf("\tEdge ("MAG"2"NRM"): %s\n", NetT[i].edge_name_two);
		if (NetT[i].edge_type_two == io)
			printf("\t\tType: IO\n");
		else if (NetT[i].edge_type_two == component)
			printf("\t\tType: Component\n");
	}
}

void free_net_table()
{
	unsigned int i;

	for (i = 0; i < netT_size; i++)
	{
		free(NetT[i].edge_name_one);
		free(NetT[i].edge_name_two);
	}

	free(NetT);
	netT_size = 0;
}

void connect_net_edges()
{
	unsigned int i;
	unsigned int location;

	for (i = 0; i < netT_size; i++)
	{
		if (NetT[i].edge_type_one == nothing)
		{
			if (search_io(NetT[i].edge_name_one, &location) == RETURN_SUCCESS)
			{
				NetT[i].edge_type_one = io;
				NetT[i].edge_pointer_one = location;
			}
			else if (search_component(NetT[i].edge_name_one, &location) == RETURN_SUCCESS)
			{
				NetT[i].edge_type_one = component;
				NetT[i].edge_pointer_one = location;
			}
			else
			{
				printf(RED"Error! Unregister edge of net!\n"NRM);
				free_row_table();
				free_io_table();
				free_component_table();
				free_net_table();
				exit(1);
			}
		}

		if (NetT[i].edge_type_two == nothing)
		{
			if (search_io(NetT[i].edge_name_two, &location) == RETURN_SUCCESS)
			{
				NetT[i].edge_type_two = io;
				NetT[i].edge_pointer_two = location;
			}
			else if (search_component(NetT[i].edge_name_two, &location) == RETURN_SUCCESS)
			{
				NetT[i].edge_type_two = component;
				NetT[i].edge_pointer_two = location;
			}
			else
			{
				printf(RED"Error! Unregister edge of net!\n"NRM);
				free_row_table();
				free_io_table();
				free_component_table();
				free_net_table();
				exit(1);
			}
		}
	}

	printf(GRN"Nets connected successfully!\n"NRM);
}