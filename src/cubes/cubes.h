#ifndef CUBES
#define CUBES 

#include <stdio.h>
#include <stdlib.h>

#include "../main.h"

int check_cube(char *cube, int length);
char *find_intersect_2(char *cube1, char *cube2, int length);
char *find_supercube_2(char *cube1, char *cube2, int length);
int find_distance(char *intersection, int length);
int find_cube_cover_2(char *cube1, char *cube2, int length);
char *get_sharped_cube(char *cube1, char *cube2, int length, int k);
char **find_sharp_2_set(char *cube1, char *cube2, int length, int *listLength);
void print_sharp_2_set(char *cube1, char *cube2, char **list, int length);
void free_sharp_2_set(char **list, int length);

#endif