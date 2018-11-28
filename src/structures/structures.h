#ifndef STRUCTURES
#define STRUCTURES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"

#define CELL_WIDTH    1.260
#define CELL_HEIGHT   0.576

// Data structures //

enum struct_type {nothing = 0, io, component};

struct row
{
	char *name;
	char *type;
	// Starting Point of the Row
	double location_x;
	double location_y;
	// Size
	double width;
	double height;
};

struct io
{
	char *name;
	// Location
	double x;
	double y;
};

struct component
{
	char *name;

	// Location (Top Left)
	double x;
	double y;
};

// P2P Net
struct net
{
	enum struct_type edge_type_one;
	enum struct_type edge_type_two;
	unsigned int edge_pointer_one;
	unsigned int edge_pointer_two;
	char *edge_name_one;
	char *edge_name_two;
};

struct edge;

// Graph Node //
struct node
{
	char *name;             // Node's name //

	// Edges //
	unsigned int noofEdges; // Number of edges //
	unsigned int *edges;    // Array of indexes to edges //
};

struct edge
{
	unsigned int source;      // Node where the edge starts //
	unsigned int destination; // Node where the edge ends //
	double weight;            // Edge's weight //
};

// Externals //

extern char *design_name;
extern double core_utilisation;

// Core dimentions //
extern double core_width;
extern double core_height;
extern double aspect_ratio;
extern double core_X_offset;
extern double core_Y_offset;

// Row Table //
extern struct row *RowT;
extern unsigned int rowT_size;

// IO Table //
extern struct io *IOT;
extern unsigned int ioT_size;

// Component Table //
extern struct component *ComponentT;
extern unsigned int componentT_size;

// Net Table //
extern struct net *NetT;
extern unsigned int netT_size;

extern int show_nets;

// Node Table //
struct node *NodeT;
unsigned int nodeTSize;

// Edges Table //
struct edge *EdgeT;
unsigned int edgeTSize;

// Function Prototypes //

void insert_row(char *name, char *type, double location_x, double location_y, double width, double height);
void print_rows();
void free_row_table();

void insert_io(char *name, double x, double y);
int search_io(char *name, unsigned int *location);
void print_ios();
void free_io_table();

void insert_component(char *name);
int search_component(char *name, unsigned int *location);
void print_components();
void free_component_table();

int check_if_net_exists(char *edge1, char *edge2);
void insert_net(char *edge1, char *edge2);
void insert_io_net(char *io_edge, char *edge2);
void print_nets();
void free_net_table();

void connect_net_edges();

void insert_node(char *name, unsigned int *location);
int search_node(char *name, unsigned int *location);

void insert_edge(unsigned int source, unsigned int destination, double weight);

#endif