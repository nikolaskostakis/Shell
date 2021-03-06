#ifndef CUBES
#define CUBES 

#include <stdio.h>
#include <stdlib.h>

#include "../main.h"

int check_cube_validity(char *cube, int length);
int check_cube(char *cube, int length);
int check_duplicate_cube(char *cube, char **list, int listLength);
char *find_intersect_2(char *cube1, char *cube2, int length);
char *find_supercube_2(char *cube1, char *cube2, int length);
int find_distance(char *intersection, int length);
int find_cube_cover_2(char *cube1, char *cube2, int length);
char *get_sharped_cube(char *cube1, char *cube2, int length, int k);
char **find_sharp_2_set(char *cube1, char *cube2, int length, int *listLength);
char **find_sharp_set(char ***sharpSets, int *sharpSetsLength, int sharpSetsNumber, int cubeLength, int *listLength);
void print_sharp_2_set(char *cube1, char *cube2, char **list, int length);
void free_sharp_set(char **list, int length);
char *create_universe(int length);
char *divide_cubes(char *dividend, char *divisor, int length);
char **weak_div(char **dividend, char **divisor, int dividendLength, int divisorLength, int length, int *resultLength);
char **weak_div_remainder(char **dividend, char **divisor, char **quotient, int dividendLength, int divisorLength, int quotientLength, int length, int *resultLength);

#endif