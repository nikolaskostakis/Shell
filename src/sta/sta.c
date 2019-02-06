#include "sta.h"

// Fill the queue with all the nodes that have no predecessors //
void init_node_queue_with_roots()
{
    unsigned int i;
    
    for(i = 0; i < nodeTSize; i++)
    {
		if (NodeT[i].noofIncomeEdges == 0)
		{
            queue_graphNode(i);
        }
    }
}

double find_longest_distance()
{
	int i;
	double maxDistance = 0;
	unsigned int qElementIndex = 0;
	struct graphNode qElement;
	struct edge elementEdge;

	qElementIndex = dequeue_graphNode();
	// While the queue is not empty //
	while(qElementIndex != -1)
	{
		qElement = NodeT[qElementIndex];
	//printf("xa %u %u\n",qElement, qElementIndex);
		for (i = 0; i < qElement.noofOutcomeEdges; i++)
		{
			elementEdge = EdgeT[qElement.edges[i]];

			if (NodeT[elementEdge.destination].distance < (qElement.distance + elementEdge.weight))
			{
				NodeT[elementEdge.destination].distance = qElement.distance + elementEdge.weight;
				NodeT[elementEdge.destination].predecessor = qElementIndex;
			}

			printf("%lf, %lf, %lf\n", NodeT[elementEdge.destination].distance, qElement.distance, elementEdge.weight);

			maxDistance = fmax(maxDistance, NodeT[elementEdge.destination].distance);

			NodeT[elementEdge.destination].noofIncomeEdges--;
			if (NodeT[elementEdge.destination].noofIncomeEdges == 0)
			{
				queue_graphNode(elementEdge.destination);
			}
		}

		qElementIndex = dequeue_graphNode();
	}

	return maxDistance;
}

// Run throug the Nodes's table and find a Node with the longest distance. //
unsigned int select_longest_distance_node(double maxDistance)
{
	unsigned int i;

	for (i=0; i < nodeTSize; i++)
	{
		if (NodeT[i].distance == maxDistance)
		{
			return i;
		}
	}
}

void init_slack_values(unsigned int maxDistanceNode, double maxDistance, double rSlack)
{
	unsigned int i;

	for (i = 0; i < nodeTSize; i++)
	{
		if (i == maxDistance)
		{
			NodeT[i].slack = rSlack;
		}
		else
		{
			NodeT[i].slack = maxDistance;
		}
	}
}

unsigned int *back_trace(unsigned int maxDistanceNode, double maxDistance, double RAT, unsigned int *pathSize)
{
	unsigned int *criticalPath = NULL;
	unsigned int criticalPathSize = 0;
	unsigned int qElementIndex = 0;
	unsigned int i;
	double rSlack = 0;
	struct graphNode qElement;
	struct edge elementEdge;

	// Calculate the required slack //
	rSlack = RAT - maxDistance;

	// Add initial slack values //
	init_slack_values(maxDistanceNode, maxDistance, rSlack);

	// Add node with max distance to the queue //
	queue_graphNode(maxDistanceNode);

	// Add the max distance node to the critical path
	criticalPath = (unsigned int *) realloc(criticalPath, ((criticalPathSize + 1) * sizeof(unsigned int)));
	if (criticalPath == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}
	criticalPath[criticalPathSize] = maxDistanceNode;
	criticalPathSize++;

	qElementIndex = dequeue_graphNode();
	printf("xaxa %u\n", qElementIndex);
	while(qElementIndex != -1)
	{
		qElement = NodeT[qElementIndex];

		for (i = 0; i < qElement.noofIncomeEdges; i++)
		{
			elementEdge = EdgeT[qElement.incomeEdges[i]];

			NodeT[elementEdge.source].slack = qElement.slack + (qElement.distance - (NodeT[elementEdge.destination].distance + elementEdge.weight));
			printf("%lf %lf\n", rSlack, NodeT[elementEdge.destination].slack);
			if (NodeT[elementEdge.source].slack == rSlack)
			{
				// Add node to queue //
				queue_graphNode(elementEdge.source);

				// Add node to critical path //
				criticalPath = (unsigned int *) realloc(criticalPath, ((criticalPathSize + 1) * sizeof(unsigned int)));
				if (criticalPath == NULL)
				{
					printf(RED"Error! Unable to allocate memory\n"NRM);
					exit(1);
				}
				criticalPath[criticalPathSize] = elementEdge.source;
				criticalPathSize++;				
			}
		}

		qElementIndex = dequeue_graphNode();
	}

	*pathSize = criticalPathSize;
	return criticalPath;
}

void print_spaces_for_longest_path_prints(unsigned int spaces)
{
	unsigned int i;
	
	for (i = 0; i < spaces; i++)
	{
		printf("    "); // 4 spaces //
	}
}

void print_longest_path(unsigned int *path, unsigned int pathSize, int slackEnable)
{
	unsigned int i;

	if (slackEnable == 1)
	{
		printf("Node: %s, slack:%lf\n", NodeT[path[0]].name, NodeT[path[0]].slack);
	}
	else
	{
		printf("Node: %s\n", NodeT[path[0]].name);
	}

	if (pathSize > 1)
	{
		for (i = 1; i < pathSize; i++)
		{
			print_spaces_for_longest_path_prints(i);
			printf("|\n");
			print_spaces_for_longest_path_prints(i);
			printf("+-> ");

			if (slackEnable == 1)
			{
				printf("Node: %s, slack:%lf\n", NodeT[path[i]].name, NodeT[path[i]].slack);
			}
			else
			{
				printf("Node: %s\n", NodeT[path[i]].name);
			}	
		}
	}
}

void longest_path(int slackEnable)
{
	unsigned int nodePos;
	unsigned int pathSize = 0;
	unsigned int *path = NULL;
	double maxDistance;

	if (nodeTSize == 0)
	{
		printf(YEL"There is no graph loaded!\n"NRM);
		return;
	}

	// Initialize the queue //
	init_node_queue_with_roots();

	// Find the distances of the node and the max distance //
	maxDistance = find_longest_distance();
	printf("\t"RED"Debug Print:"NRM" maxd %lf\n", maxDistance);
	// Finde the first node with max distance //
	nodePos = select_longest_distance_node(maxDistance);

	// Back trace and find longest path //
	// path = back_trace(nodePos, maxDistance, 0, &pathSize);

	// Print the longst path //
	// print_longest_path(path, pathSize, slackEnable);

	// free the critical path //
	free(path);
}