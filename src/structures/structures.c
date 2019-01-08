#include "structures.h"

// Design Globals //

// Desing characteristics //
char *design_name = NULL;
double core_utilisation = 0;

// Core dimentions //
double core_width = 0;
double core_height = 0;
double aspect_ratio = 0;
double core_X_offset = 0;
double core_Y_offset = 0;

// Row Table //
struct row *RowT = NULL;
unsigned int rowT_size = 0;

// IO Table //
struct io *IOT = NULL;
unsigned int ioT_size = 0;

// Component Table //
struct component *ComponentT = NULL;
unsigned int componentT_size = 0;

// Net Table //
struct net *NetT = NULL;
unsigned int netT_size = 0;

// Node Table //
struct graphNode *NodeT = NULL;
unsigned int nodeTSize = 0;

// Edges Table //
struct edge *EdgeT = NULL;
unsigned int edgeTSize = 0;

// Node Queue //
struct graph_node_queue *startNodeQueue = NULL;
struct graph_node_queue *endNodeQueue = NULL;
unsigned int nodeQueueSize = 0;

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

void insert_node(char *name, unsigned int *location)
{
	NodeT = (struct graphNode *) realloc(NodeT, ((nodeTSize + 1) * sizeof(struct graphNode)));
	if (NodeT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	// Initialization //
	NodeT[nodeTSize].name = name;
	NodeT[nodeTSize].distance = 0;
	NodeT[nodeTSize].slack = 0;	
	NodeT[nodeTSize].noofIncomeEdges = 0;
	NodeT[nodeTSize].noofOutcomeEdges = 0;
	NodeT[nodeTSize].edges = NULL;
	NodeT[nodeTSize].incomeEdges = NULL;

	*location = nodeTSize;

	nodeTSize++;
}

int search_node(char *name, unsigned int *location)
{
	unsigned int i;

	for (i = 0; i < nodeTSize; i++)
	{
		if (strcmp(NodeT[i].name, name) == 0)
		{
			*location = i;
			return RETURN_SUCCESS;
		}
	}

	return RETURN_FAILURE;
}

void print_nodes()
{
	unsigned int i, j;

	if (nodeTSize == 0)
	{
		printf(YEL"Node Table empty!\n"NRM);
		return;
	}

	for (i = 0; i < nodeTSize; i++)
	{
		printf("Node: "BLU"%s"NRM"\n", NodeT[i].name);
		printf("\tDistance: "MAG"%lf"NRM"\n", NodeT[i].distance);
		printf("\tSlack:    "MAG"%lf"NRM"\n", NodeT[i].slack);
		printf("\tPredecessor to:\n");
		if (NodeT[i].noofOutcomeEdges == 0)
		{
			printf(MAG"\t\t(null)\n"NRM);
		}
		else
		{
			for (j = 0; j < NodeT[i].noofOutcomeEdges; j++)
			{
				printf(MAG"\t\t%s\n"NRM, NodeT[NodeT[i].edges[j]].name);
			}
		}
		if (NodeT[i].noofIncomeEdges == 0)
		{
			printf(MAG"\t\t(null)\n"NRM);
		}
		else
		{
			for (j = 0; j < NodeT[i].noofIncomeEdges; j++)
			{
				printf(MAG"\t\t%s\n"NRM, NodeT[NodeT[i].incomeEdges[j]].name);
			}
		}
	}
	printf("\n");
}

void free_node_table()
{
	unsigned int i;

	for (i = 0; i < nodeTSize; i++)
	{
		free(NodeT[i].name);
		free(NodeT[i].edges);
		free(NodeT[i].incomeEdges);
	}

	free(NodeT);
	NodeT = NULL;
	nodeTSize = 0;
}

void insert_edge(unsigned int source, unsigned int destination, double weight)
{
	EdgeT = (struct edge *) realloc(EdgeT, ((edgeTSize + 1) * sizeof(struct edge)));
	if (EdgeT == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	// Initialization //
	EdgeT[edgeTSize].weight = weight;
	EdgeT[edgeTSize].source = source;
	EdgeT[edgeTSize].destination = destination;

	// Add successor //
	NodeT[source].edges = (unsigned int *) realloc(NodeT[source].edges, ((NodeT[source].noofOutcomeEdges + 1) * sizeof(unsigned int)));
	if (NodeT[source].edges == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	NodeT[source].edges[NodeT[source].noofOutcomeEdges] = destination;
	NodeT[source].noofOutcomeEdges++;

	// Add predecessor //
	printf("%d", NodeT[destination].noofIncomeEdges);
	NodeT[destination].incomeEdges = (unsigned int *) realloc(NodeT[destination].incomeEdges, ((NodeT[destination].noofIncomeEdges + 1) * sizeof(unsigned int)));
	if (NodeT[destination].incomeEdges == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	NodeT[destination].incomeEdges[NodeT[destination].noofIncomeEdges] = source;
	NodeT[destination].noofIncomeEdges++;
	printf("%d", NodeT[destination].noofIncomeEdges);

	edgeTSize++;
}

void print_edges()
{
	unsigned int i;

	if (edgeTSize == 0)
	{
		printf(YEL"Edge Table empty!\n"NRM);
		return;
	}

	for (i = 0; i < edgeTSize; i++)
	{
		printf("Edge:\n");
		printf("\tSource:      "GRN"%s"NRM"\n", NodeT[EdgeT[i].source].name);
		printf("\t             "YEL"||"NRM"\n");
		printf("\t             "YEL"||"GRN"  %lf"NRM"\n", EdgeT[i].weight);
		printf("\t             "YEL"\\/"NRM"\n");
		printf("\tDestination: "GRN"%s"NRM"\n", NodeT[EdgeT[i].destination].name);
	}
	printf("\n");
}

void free_edge_table()
{
	free(EdgeT);
	EdgeT = NULL;

	edgeTSize = 0;
}

// Add node to queue //
void queue_graphNode(unsigned int gNodeIndex)
{
	struct graph_node_queue *qNode;
	struct graphNode gNode;

	gNode = NodeT[gNodeIndex];

	qNode = (struct graph_node_queue *) calloc(1, sizeof(struct graph_node_queue));
	if (qNode == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	qNode->node = &gNode;

	if (nodeQueueSize == 0)
	{
		startNodeQueue = qNode;
	}
	else
	{
		endNodeQueue->next = qNode;
	}
	
	endNodeQueue = qNode;
	nodeQueueSize++;
}

// Remove node from the queue //
unsigned int dequeue_graphNode()
{
	struct graph_node_queue *qNode;
	struct graphNode *gNode;
	unsigned int index = 0;

	if (nodeQueueSize == 0)
	{
		return -1;
	}

	gNode = startNodeQueue->node;
	search_component(gNode->name, &index);

	qNode = startNodeQueue;
	startNodeQueue = startNodeQueue->next;
	free(qNode);

	nodeQueueSize--;
	if (nodeQueueSize == 0)
	{
		startNodeQueue = NULL;
		endNodeQueue = NULL;
	}

	return index;
}
