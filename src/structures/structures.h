#ifndef STRUCTURES
#define STRUCTURES

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

extern char *design_name;
extern double core_utilisation;

// Core dimentions
extern double core_width;
extern double core_height;
extern double aspect_ratio;
extern double core_X_offset;
extern double core_Y_offset;

// Row Table
extern struct row *RowT;
extern unsigned int rowT_size;

void insert_row(char *name, char *type, double location_x, double location_y, double width, double height);
void print_rows();
void free_row_table();

#endif