#ifndef STA
#define STA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"
#include "../structures/structures.h"

void init_node_queue_with_roots();
double find_longest_distance();
unsigned int select_longest_distance_node(double maxDistance);
void init_slack_values(unsigned int maxDistanceNode, double maxDistance, double rSlack);
unsigned int *back_trace(unsigned int maxDistanceNode, double maxDistance, double RAT, unsigned int *pathSize);
void print_spaces_for_longest_path_prints(unsigned int spaces);
void print_longest_path(unsigned int *path, unsigned int pathSize, int slackEnable);
void longest_path(int slackEnable);

#endif // STA