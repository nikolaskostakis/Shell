#include "placement.h"

int placed = 0;

char *RandomT = NULL;
unsigned int randomT_x = 0;
unsigned int randomT_y = 0;

void create_random_array()
{
	unsigned long i;
	unsigned int j;

	if (RandomT != NULL)
	{
		for (i = 0; i < (randomT_x * randomT_y); i++)
			RandomT[i] = 0;
		for (j = 0; j < componentT_size; j++)
		{
			ComponentT[j].x = 0;
			ComponentT[j].y = 0;
		}
	}

	// 
	randomT_y = rowT_size;
	randomT_x = floor(core_width / CELL_WIDTH);

	RandomT = (char *) malloc((randomT_x * randomT_y) * sizeof(char));
	if (RandomT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
	}

	for (i = 0; i < (randomT_x * randomT_y); i++)
		RandomT[i] = -1;
}


int random_place_components()
{
	char found;
	unsigned int i, j;
	unsigned int x, y;

	srand(time(NULL));

	for (i = 0; i < componentT_size; i++)
	{
		found = 0;
		for (j = 1; j <= MAX_RANDOM_TRIES; j++)
		{
			x = rand() % randomT_x;
			y = rand() % randomT_y;

			if (RandomT[x + (y * randomT_x)] == -1)
			{
				found = 1;
				break;
			}
		}

		if (found == 0)
			return RETURN_FAILURE;

		RandomT[x + (y * randomT_x)] = i;
		
		ComponentT[i].x = (x * CELL_WIDTH) + core_X_offset;
		ComponentT[i].y = (y * CELL_HEIGHT) + core_Y_offset;
	}


	placed = 1;
	return RETURN_SUCCESS;
}

// Take the coordinates of a component from the input variables
void take_coordinates(int p, double *x, double *y)
{
	*x = ComponentT[p].x;
	*y = ComponentT[p].y;
}

// Change the coordinates of a component
void change_coordinates(int p, double x, double y)
{
	ComponentT[p].x = x;
	ComponentT[p].y = y;
}

// Swap the coordinates of thwo components
void swap_coordinates(int p1, int p2)
{
	double temp_x, temp_y;

	temp_x = ComponentT[p1].x;
	temp_y = ComponentT[p1].y;

	ComponentT[p1].x = ComponentT[p2].x;
	ComponentT[p1].y = ComponentT[p2].y;

	ComponentT[p2].x = temp_x;
	ComponentT[p2].y = temp_y;
}

// Half perimeter wire length
double calculate_WL()
{
	unsigned int i;
	double result = 0;
	double point_one_x, point_one_y;
	double point_two_x, point_two_y;

	for (i = 0; i < netT_size; i++)
	{
		if (NetT[i].edge_type_one == io)
		{
			point_one_x = IOT[NetT[i].edge_pointer_one].x;
			point_one_y = IOT[NetT[i].edge_pointer_one].y;
		}
		else  // Component
		{
			// From the middle of the cell
			point_one_x = ComponentT[NetT[i].edge_pointer_one].x + (CELL_WIDTH / 2);
			point_one_y = ComponentT[NetT[i].edge_pointer_one].y + (CELL_HEIGHT / 2);
		}
		
		if (NetT[i].edge_type_two == io)
		{
			point_two_x = IOT[NetT[i].edge_pointer_two].x;
			point_two_y = IOT[NetT[i].edge_pointer_two].y;
		}
		else // Component
		{
			// From the middle of the cell
			point_two_x = ComponentT[NetT[i].edge_pointer_two].x + (CELL_WIDTH / 2);
			point_two_y = ComponentT[NetT[i].edge_pointer_two].y + (CELL_HEIGHT / 2);
		}

		result += fabs(point_two_x - point_one_x) + fabs(point_two_y - point_one_y);
	}

	return result;
}

void timberwolf(int N)
{
	unsigned int i, j, k, l, n;
	unsigned int new_i, new_j, temp;
	int position_changed;
	double old_wl = 0;
	double new_wl = 0;
	double old_x, old_y;
	double new_x, new_y;

	// Initial WL
	old_wl =  calculate_WL();

	printf("Initial WL: %lf\n", old_wl);

	// Iterations loop
	for (n = 0; n < N; n++)
	{
		// Moves
		// Outer loop, lines
		for (j = 0; j < randomT_y; j++)
		{
			// Mid loop, run for each component of the line
			for (i = 0; i < randomT_x; i++)
			{
				// If there is no component on this position, continue
				if (RandomT[i + (j * randomT_x)] == -1)
					continue;

				take_coordinates(RandomT[i + (j * randomT_x)], &old_x, &old_y);

				position_changed = 0;
				// Inner loop, search for new position inside the line
				for (k = 0; k < randomT_x; k++)
				{
					// If field is not empty, continue
					if (RandomT[k + (j * randomT_x)] != -1)
						continue;

					new_x = (k * CELL_WIDTH) + core_X_offset;

					// Temporary change the coordinates
					change_coordinates(RandomT[i + (j * randomT_x)], new_x, old_y);
					// Calculate the temp WL
					new_wl = calculate_WL();

					// If the new Wl is less than the old
					if (new_wl < old_wl)
					{
						// Mark the position as to be changed
						position_changed = 1;
						// Keep new coordinates
						old_x = new_x;
						old_wl = new_wl;
						new_i = k;
					}
				}

				// If there was a better WL
				if (position_changed){
					// Change the Array
					RandomT[new_i + (j * randomT_x)] = RandomT[i + (j * randomT_x)];
					RandomT[i + (j * randomT_x)] = -1;
				}
				else
				{
					new_i = i;
				}

				// Change the component's coordinates
				change_coordinates(RandomT[new_i + (j * randomT_x)], old_x, old_y);
			}
		}

		// Swaps
		// Outer loop of the elements
		for (j = 0; j < randomT_y; j++)
		{
			// Inner loop of the elements
			for (i = 0; i < randomT_x; i++)
			{
				old_x = i;
				old_y = j;

				position_changed = 0;
				// Outer loop of swaps
				for (l = 0; l < randomT_y; l++)
				{
					for (k = 0; k < randomT_x; k++)
					{
						// Continue if its the swapable cell
						if ((j = l) && (i = k))
							continue;

						// Swap coordinates to calculate the WL
						swap_coordinates(RandomT[i + (j * randomT_x)], RandomT[k + (l * randomT_x)]);
						new_wl = calculate_WL();

						if (new_wl < old_wl)
						{
							position_changed = 1;
							old_wl = new_wl;
							new_i = k;
							new_j = l;
						}
						// Revert to original coordinates for now
						swap_coordinates(RandomT[i + (j * randomT_x)], RandomT[k + (l * randomT_x)]);
						temp = RandomT[i + (j * randomT_x)];
						RandomT[i + (j * randomT_x)] = RandomT[new_i + (new_j * randomT_x)];
						RandomT[new_i + (new_j * randomT_x)] = temp;
					}
				}

				// If there was change to the WL after the loop
				if (position_changed)
				{
					// Swap the cells
					swap_coordinates(RandomT[i + (j * randomT_x)], RandomT[new_i + (new_j * randomT_x)]);

				}
				// Move to the next cell
			}
		}
	}

	printf("New WL: %lf\n", old_wl);
}