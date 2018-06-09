#ifndef PLACEMENT
#define PLACEMENT

#define MAX_RANDOM_TRIES 100

extern int placed;

extern char *RandomT;
extern unsigned int randomT_x;
extern unsigned int randomT_y;

void create_random_array();
int random_place_components();
void take_coordinates(int p, double *x, double *y);
void change_coordinates(int p, double x, double y);
void swap_coordinates(int p1, int p2);
double calculate_WL();
void timberwolf(int N);


#endif