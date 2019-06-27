#include "tcl.h"

// Tcl Interpreter
Tcl_Interp *interpreter = NULL;

// Function "init_tcl"
//
void init_tcl()
{
	// Initialize the interpreter
	interpreter = Tcl_CreateInterp();

	// Create the commands
	Tcl_CreateObjCommand(interpreter, "less", less, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "ls", ls, NULL, NULL);

	Tcl_CreateObjCommand(interpreter, "read_design", read_design, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "clear_design", clear_design, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "print_design_rows", print_design_rows, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "print_design_ios", print_design_ios, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "print_design_components", print_design_components, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "print_design_nets", print_design_nets, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "place_random", place_random, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "report_WL", report_WL, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "display_nets", display_nets, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "tw_minimise_WL", tw_minimise_WL, NULL, NULL);

	Tcl_CreateObjCommand(interpreter, "cube_intersect_2", cube_intersect_2, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "supercube_2", supercube_2, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "distance_2", distance_2, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "cube_cover_2", cube_cover_2, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "sharp_2", sharp_2, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "sharp", sharp, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "OFF_f", OFF_f, NULL, NULL);
	
	Tcl_CreateObjCommand(interpreter, "read_graph", read_graph, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "write_graph", write_graph, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "print_graph_nodes", print_graph_nodes, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "print_graph_edges", print_graph_edges, NULL, NULL);
	Tcl_CreateObjCommand(interpreter, "graph_critical_path", graph_critical_path, NULL, NULL);

	Tcl_CreateObjCommand(interpreter, "alg_division", alg_division, NULL, NULL);
}

int less(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	char syntax[] = "<filepath>";
	char command[] = "less";
	char *ex_command = NULL, *arg = NULL;
	int len = 0;

	if (argc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	arg = Tcl_GetStringFromObj(argv[1], &len);
	if (arg == NULL)
	{
		printf("Wrong Encoding of Argument: 1\n");
		return TCL_ERROR;
	}

	ex_command = (char *) malloc((len + 4 + 2) * sizeof(char));
	if (ex_command == NULL)
	{
		printf("Unable to Allocate Memory! Exiting...\n");
		exit(1);
	}

	sprintf(ex_command, "%s %s", command, arg);

	system(ex_command);
	free(ex_command);

	return TCL_OK;
}

int ls(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	char syntax[] = "[[directory] [-arguments]] | [[-arguments] [directory]]";
	char command[] = "ls";

	char *ex_command = NULL, *arg1 = NULL, *arg2= NULL;
	int len1 = 0, len2 = 0;
	int arg = 0;
	int dir = 0;

	if (argc > 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	if (argc == 3)
	{
		arg1 = Tcl_GetStringFromObj(argv[1], &len1);
		if (arg1 == NULL)
		{
			printf("Wrong Encoding of Argument: 1\n");
			return TCL_ERROR;
		}

		// Check whether the arg is arguement or directory
		if (arg1[0] == '-')
			arg = 1;
		else
			dir = 1;

		arg2 = Tcl_GetStringFromObj(argv[2], &len2);
		if (arg2 == NULL)
		{
			printf("Wrong Encoding of Argument: 2\n");
			return TCL_ERROR;
		}

		//  Check whether the arg is arguement or directory and if it is     //
		// same type with the previous arguement.                            //
		if ((arg2[0] == '-') && (arg))
		{
			Tcl_WrongNumArgs(interp, 1, argv, syntax);
			return TCL_ERROR;
		}
		if ((arg2[0] != '-') && (dir))
		{
			Tcl_WrongNumArgs(interp, 1, argv, syntax);
			return TCL_ERROR;
		}

		ex_command = (char *) malloc((len1 + len2 + 2 + 3) * sizeof(char));
		if (ex_command == NULL)
		{
			printf("Unable to Allocate Memory! Exiting...\n");
			exit(1);
		}

		sprintf(ex_command, "%s %s %s", command, arg1, arg2);
	}
	else if (argc == 2)
	{
		arg1 = Tcl_GetStringFromObj(argv[1], &len1);
		if (arg1 == NULL)
		{
			printf("Wrong Encoding of Argument: 1\n");
			return TCL_ERROR;
		}

		ex_command = (char *) malloc((len1 + 2 + 2) * sizeof(char));
		if (ex_command == NULL)
		{
			printf("Unable to Allocate Memory! Exiting...\n");
			exit(1);
		}

		sprintf(ex_command, "%s %s", command, arg1);
	}
	else
	{
		ex_command = strdup(command);
		if (ex_command == NULL)
		{
			printf("Unable to Allocate Memory! Exiting...\n");
			exit(1);
		}
	}

	system(ex_command);
	free(ex_command);

	return TCL_OK;
}

int read_design(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<filepath>";

	int len = 0;
	FILE *fp = NULL;
	char *file = NULL;

	if (argc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	file = Tcl_GetStringFromObj(argv[1], &len);

	fp = fopen(file, "r");

	if (fp == NULL)
	{
		printf("File does not exist!\n");
		return TCL_ERROR;
	}

	parse_design_file(fp);
	// fclose(fp);

	connect_net_edges();

	return TCL_OK;
}

int print_design_rows(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	print_rows();

	return TCL_OK;
}

int print_design_ios(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	print_ios();

	return TCL_OK;
}

int print_design_components(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	print_components();

	return TCL_OK;
}

int print_design_nets(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	print_nets();

	return TCL_OK;
}

int clear_design(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	if (design_name == NULL)
	{
		printf(YEL"No design has been imported!"NRM);
		return TCL_OK;
	}

	free_row_table();
	free_io_table();
	free_component_table();
	free_net_table();

	free(design_name);
	core_utilisation = 0;
	core_width = 0;
	core_height = 0;
	aspect_ratio = 0;
	core_X_offset = 0;
	core_Y_offset = 0;

	free(RandomT);
	randomT_x = 0;
	randomT_y = 0;

	printf(GRN"Design has been cleared!\n"NRM);

	return TCL_OK;
}

int place_random(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";
	int result;

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	if (design_name == NULL)
	{
		printf(YEL"There is no design to be placed!\n"NRM);
		return TCL_OK;
	}

	create_random_array();
	result = random_place_components();

	printf("Random placement: ");
	if (result == RETURN_FAILURE)
		printf(RED"Failed! Please try again...\n"NRM);
	else
		printf(GRN"Succeed!\n"NRM);

	return TCL_OK;
}

int report_WL(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";
	double result;

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	if (design_name == NULL)
	{
		printf(YEL"There is no design!\n"NRM);
		return TCL_OK;
	}

	result = calculate_WL();
	printf("Total wire length: %lf\n", result);

	return TCL_OK;
}

int display_nets(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "[-on|-off]";
	double result;

	int len = 0;
	char *flag = NULL;

	if (argc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	flag = Tcl_GetStringFromObj(argv[1], &len);
	if (flag == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	if (!strcmp(flag, "-on"))
		show_nets = 1;
	else if (!strcmp(flag, "-off"))
		show_nets = 0;
	else
	{
		printf("Wrong arguement %s.\n", flag);
		return TCL_ERROR;
	}

	return TCL_OK;
}

int tw_minimise_WL(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<noof_loops>";
	double result;

	int loops = 0;
	int len = 0;

	if (argc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	Tcl_GetInt(interp, Tcl_GetStringFromObj(argv[1], &len), &loops);

	timberwolf(loops);

	return TCL_OK;
}

int cube_intersect_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<cube_one> <cube_two>";
	char *cube1 = NULL;
	char *cube2 = NULL;
	char *intersection = NULL;
	int len1 = 0;
	int len2 = 0;

	if (argc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get first cube //
	cube1 = Tcl_GetStringFromObj(argv[1], &len1);
	if (cube1 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get second cube //
	cube2 = Tcl_GetStringFromObj(argv[2], &len2);
	if (cube2 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if cubes' representations are valid //
	if ((check_cube(cube1, len1) == RETURN_FAILURE) || (check_cube(cube2, len2) == RETURN_FAILURE))
	{
		return TCL_ERROR;
	}

	// Check if cubes have the same length //
	if (len1 != len2)
	{
		printf(RED"Cubes do not have the same size!\n"NRM);
		return TCL_ERROR;
	}

	// Run the intersection function and print the result //
	intersection = find_intersect_2(cube1, cube2, len1);
	printf("Intersection of the two cubes: "MAG"%s\n"NRM, intersection);
	free(intersection);

	return TCL_OK;
}

int supercube_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<cube_one> <cube_two>";
	char *cube1 = NULL;
	char *cube2 = NULL;
	char *supercube = NULL;
	int len1 = 0;
	int len2 = 0;

	if (argc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get first cube //
	cube1 = Tcl_GetStringFromObj(argv[1], &len1);
	if (cube1 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get second cube //
	cube2 = Tcl_GetStringFromObj(argv[2], &len2);
	if (cube2 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if cubes' representations are valid //
	if ((check_cube(cube1, len1) == RETURN_FAILURE) || (check_cube(cube2, len2) == RETURN_FAILURE))
	{
		return TCL_ERROR;
	}

	// Check if cubes have the same length //
	if (len1 != len2)
	{
		printf(RED"Cubes do not have the same size!\n"NRM);
		return TCL_ERROR;
	}

	// Run the supercube function and print the result//
	supercube = find_supercube_2(cube1, cube2, len1);
	printf("Supercube of the two cubes: "MAG"%s\n"NRM, supercube);
	free(supercube);

	return TCL_OK;
}

int distance_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<cube_one> <cube_two>";
	char *cube1 = NULL;
	char *cube2 = NULL;
	char *intersection = NULL;
	int len1 = 0;
	int len2 = 0;
	int distance  = 0;

	if (argc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get first cube //
	cube1 = Tcl_GetStringFromObj(argv[1], &len1);
	if (cube1 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get second cube //
	cube2 = Tcl_GetStringFromObj(argv[2], &len2);
	if (cube2 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if cubes' representations are valid //
	if ((check_cube(cube1, len1) == RETURN_FAILURE) || (check_cube(cube2, len2) == RETURN_FAILURE))
	{
		return TCL_ERROR;
	}

	// Check if cubes have the same length //
	if (len1 != len2)
	{
		printf(RED"Cubes do not have the same size!\n"NRM);
		return TCL_ERROR;
	}

	// Run the intersection function //
	intersection = find_intersect_2(cube1, cube2, len1);

	// Find distance from intersection //
	distance = find_distance(intersection, len1);
	free(intersection);


	// Print result //
	printf("Distance of the two cubes: "MAG"%d\n"NRM, distance);

	return TCL_OK;
}

int cube_cover_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<cube_one> <cube_two>";
	char *cube1 = NULL;
	char *cube2 = NULL;
	int len1 = 0;
	int len2 = 0;

	if (argc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get first cube //
	cube1 = Tcl_GetStringFromObj(argv[1], &len1);
	if (cube1 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get second cube //
	cube2 = Tcl_GetStringFromObj(argv[2], &len2);
	if (cube2 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if cubes' representations are valid //
	if ((check_cube(cube1, len1) == RETURN_FAILURE) || (check_cube(cube2, len2) == RETURN_FAILURE))
	{
		return TCL_ERROR;
	}

	// Check if cubes have the same length //
	if (len1 != len2)
	{
		printf(RED"Cubes do not have the same size!\n"NRM);
		return TCL_ERROR;
	}

	// Run the coverage function and print the result//
	printf("The first cube ");
	if (find_cube_cover_2(cube1, cube2, len1) == RETURN_FAILURE)
	{
		printf(RED"Does Not "NRM);
	}
	else
	{
		printf(GRN"Does "NRM);
	}
	printf("cover the second cube!\n");

	return TCL_OK;
}

int sharp_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<cube_one> <cube_two>";
	char *cube1 = NULL;
	char *cube2 = NULL;
	char **list = NULL;
	int len1 = 0;
	int len2 = 0;
	int listLength = 0;
	int i;

	if (argc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get first cube //
	cube1 = Tcl_GetStringFromObj(argv[1], &len1);
	if (cube1 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get second cube //
	cube2 = Tcl_GetStringFromObj(argv[2], &len2);
	if (cube2 == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if cubes' representations are valid //
	if ((check_cube(cube1, len1) == RETURN_FAILURE) || (check_cube(cube2, len2) == RETURN_FAILURE))
	{
		return TCL_ERROR;
	}

	// Check if cubes have the same length //
	if (len1 != len2)
	{
		printf(RED"Cubes do not have the same size!\n"NRM);
		return TCL_ERROR;
	}

	// Run the sharp function for the two cubes //
	list = find_sharp_2_set(cube1, cube2, len1, &listLength);

	// Print and free the list //
	print_sharp_2_set(cube1, cube2, list, listLength);
	free_sharp_set(list, listLength);

	return TCL_OK;
}

int sharp(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<cube_one> {list_of_cubes}";
	char *cube = NULL;
	Tcl_Obj **objList = NULL;
	char **list = NULL;
	char ***sharpList = NULL;
	int len = 0;
	int listLength = 0;
	int listObjLen = 0;
	int objListLength = 0;
	int *sharpListLenghtArray = NULL;
	int i;

	if (argc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get cube //
	cube = Tcl_GetStringFromObj(argv[1], &len);
	if (cube == NULL)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get list //
	if (Tcl_ListObjGetElements(interp, argv[2], &objListLength, &objList) != TCL_OK)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if all the cubes representations are valid and  have the same length //
	if (check_cube(cube, len) == RETURN_FAILURE)
	{
		return TCL_ERROR;
	}
	for (i = 0; i < objListLength; ++i)
	{
		// Check if valid //
		if (check_cube(Tcl_GetStringFromObj(objList[i], &listObjLen), listObjLen) == RETURN_FAILURE)
		{
			return TCL_ERROR;
		}

		// Check if they have the same lenght //
		if (len != listObjLen)
		{
			printf(RED"Cubes do not have the same size!\n"NRM);
			return TCL_ERROR;
		} 
	}

	// If the function has one cube, run sharp_2 //
	if (objListLength == 1)
	{
		list = find_sharp_2_set(cube, Tcl_GetStringFromObj(objList[0], &listObjLen), len, &listLength);
	}
	else
	{
		sharpList = (char ***) calloc(objListLength, sizeof(char **));
		if (sharpList == NULL)
		{
			printf(RED"Error! Unable to allocate memory\n"NRM);
			exit(1);
		}

		sharpListLenghtArray = (int *) calloc(objListLength, sizeof(int));
		if (sharpListLenghtArray == NULL)
		{
			printf(RED"Error! Unable to allocate memory\n"NRM);
			exit(1);
		}

		// run sharp_2 for each cube of the function //
		for (i = 0; i < objListLength; i++)
		{
			sharpList[i] = find_sharp_2_set(cube, Tcl_GetStringFromObj(objList[i], &listObjLen), len, &sharpListLenghtArray[i]);
		}

		// then gather up all the sharp_2 results to find the sharp result //
		list = find_sharp_set(sharpList, sharpListLenghtArray, objListLength, len, &listLength);
	}

	// Print and free the list //
	print_sharp_2_set(cube, Tcl_GetStringFromObj(argv[2], &objListLength), list, listLength);
	free_sharp_set(list, listLength);

	return TCL_OK;
}


int OFF_f(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "{list_of_cubes}";
	char *cube = NULL;
	char *cubeList = NULL;
	Tcl_Obj **objList = NULL;
	char **list = NULL;
	char ***sharpList = NULL;
	int len = 0;
	int listLength = 0;
	int listObjLen = 0;
	int objListLength = 0;
	int *sharpListLenghtArray = NULL;
	int i;

	if (argc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get list //
	if (Tcl_ListObjGetElements(interp, argv[1], &objListLength, &objList) != TCL_OK)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if all the cubes representations are valid and  have the same length //
	// Take the first's cube length as the default cube length
	cubeList = Tcl_GetStringFromObj(objList[0], &len);
	if (check_cube(cubeList, len) == RETURN_FAILURE)
	{
		return TCL_ERROR;
	}
	for (i = 1; i < objListLength; ++i)
	{
		// Check if valid //
		cubeList = Tcl_GetStringFromObj(objList[i], &listObjLen);
		if (check_cube(cubeList, listObjLen) == RETURN_FAILURE)
		{
			return TCL_ERROR;
		}

		// Check if they have the same lenght //
		if (len != listObjLen)
		{
			printf(RED"Cubes do not have the same size!\n"NRM);
			return TCL_ERROR;
		} 
	}

	cube = create_universe(len);

	// If the function has one cube, run sharp_2 //
	if (objListLength == 1)
	{
		list = find_sharp_2_set(cube, Tcl_GetStringFromObj(objList[0], &listObjLen), len, &listLength);
	}
	else
	{
		// Array to store all sharp_2 results //
		sharpList = (char ***) calloc(objListLength, sizeof(char **));
		if (sharpList == NULL)
		{
			printf(RED"Error! Unable to allocate memory\n"NRM);
			exit(1);
		}

		sharpListLenghtArray = (int *) calloc(objListLength, sizeof(int));
		if (sharpListLenghtArray == NULL)
		{
			printf(RED"Error! Unable to allocate memory\n"NRM);
			exit(1);
		}

		// run sharp_2 for each cube of the function //
		for (i = 0; i < objListLength; i++)
		{
			sharpList[i] = find_sharp_2_set(cube, Tcl_GetStringFromObj(objList[i], &listObjLen), len, &sharpListLenghtArray[i]);
		}

		// then gather up all the sharp_2 results to find the sharp result //
		list = find_sharp_set(sharpList, sharpListLenghtArray, objListLength, len, &listLength);
	}

	// Print and free the list //
	print_sharp_2_set(cube, Tcl_GetStringFromObj(argv[1], &objListLength), list, listLength);
	free_sharp_set(list, listLength);
	free(cube);

	return TCL_OK;
}

int read_graph(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<filepath>";

	int len = 0;
	FILE *fp = NULL;
	char *file = NULL;

	if (argc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	file = Tcl_GetStringFromObj(argv[1], &len);

	fp = fopen(file, "r");

	if (fp == NULL)
	{
		printf(RED"File does not exist!\n"NRM);
		return TCL_ERROR;
	}

	parse_graph_file(fp);
	fclose(fp);

	return TCL_OK;
}

int write_graph(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "<filepath>";

	int len = 0;
	FILE *fp = NULL;
	char *file = NULL;

	if (argc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	file = Tcl_GetStringFromObj(argv[1], &len);

	fp = fopen(file, "w");

	if (fp == NULL)
	{
		printf(RED"Problem while trying to open the file!\n"NRM);
		return TCL_ERROR;
	}

	write_graph_file(fp);
	fclose(fp);

	return TCL_OK;
}

int print_graph_nodes(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	print_nodes();

	return TCL_OK;
}

int print_graph_edges(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	print_edges();

	return TCL_OK;
}

int graph_critical_path(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "";

	if (argc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	longest_path(0);

	return TCL_OK;
}

int alg_division(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
{
	const char syntax[] = "{list_of_cubes} {list_of_cubes}";
	char **quotient = NULL;
	char **remainder = NULL;
	char **dividend = NULL;
	char **divisor = NULL;
	char *cubeList = NULL;
	Tcl_Obj **firstObjList = NULL;
	Tcl_Obj **secondObjList = NULL;
	// int dividendLength = 0;
	// int divisorLength = 0;
	int quotientLength = 0;
	int remainderLength = 0;
	int firstObjListLength = 0;
	int secondObjListLength = 0;
	int oldLen = 0;
	int len = 0;
	int objLen = 0;
	int i;

	if (argc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Get first list //
	if (Tcl_ListObjGetElements(interp, argv[1], &firstObjListLength, &firstObjList) != TCL_OK)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if all the cubes representations are valid and have the same length //
	// Take the first's cube length as the default cube length //
	cubeList = Tcl_GetStringFromObj(firstObjList[0], &len);
	if (check_cube(cubeList, len) == RETURN_FAILURE)
	{
		return TCL_ERROR;
	}
	for (i = 1; i < firstObjListLength; ++i)
	{
		// Check if valid //
		cubeList = Tcl_GetStringFromObj(firstObjList[i], &objLen);
		if (check_cube(cubeList, objLen) == RETURN_FAILURE)
		{
			return TCL_ERROR;
		}

		// Check if they have the same lenght //
		if (len != objLen)
		{
			printf(RED"Cubes do not have the same size!\n"NRM);
			return TCL_ERROR;
		} 
	}
	oldLen = len;

	// Get second list //
	if (Tcl_ListObjGetElements(interp, argv[2], &secondObjListLength, &secondObjList) != TCL_OK)
	{
		Tcl_WrongNumArgs(interp, 1, argv, syntax);
		return TCL_ERROR;
	}

	// Check if all the cubes representations are valid and have the same length //
	// Take the first's cube length as the default cube length //
	// Additionally check if the length is the same as the one of the first list //
	cubeList = Tcl_GetStringFromObj(secondObjList[0], &len);
	if (check_cube(cubeList, len) == RETURN_FAILURE)
	{
		return TCL_ERROR;
	}
	if (len != oldLen) // The value objLen keeps the old length //
	{
		printf(RED"Inconsistent cube size between the two lists!%d %d\n"NRM, len, objLen);
		return TCL_ERROR;
	}
	for (i = 1; i < secondObjListLength; ++i)
	{
		// Check if valid //
		cubeList = Tcl_GetStringFromObj(secondObjList[i], &objLen);
		if (check_cube(cubeList, objLen) == RETURN_FAILURE)
		{
			return TCL_ERROR;
		}

		// Check if they have the same lenght //
		if (len != objLen)
		{
			printf(RED"Cubes do not have the same size!\n"NRM);
			return TCL_ERROR;
		} 
	}

	// Create arrays with the cubes of the two lists //
	dividend = (char **) calloc(firstObjListLength, sizeof(char *));
	if (dividend == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}
	divisor = (char **) calloc(secondObjListLength, sizeof(char *));
	if (divisor == NULL)
	{
		printf(RED"Error! Unable to allocate memory\n"NRM);
		exit(1);
	}

	// Fill the arrays //
	for (i = 0; i < firstObjListLength; i++)
	{
		dividend[i] = strdup(Tcl_GetStringFromObj(firstObjList[i], &objLen));
	}
	for (i = 0; i < secondObjListLength; i++)
	{
		divisor[i] = strdup(Tcl_GetStringFromObj(secondObjList[i], &objLen));
	}

	quotient = weak_div(dividend, divisor, firstObjListLength, secondObjListLength, len, &quotientLength);
	if (quotient == NULL)
	{
		printf("Division is not feasible\n");
	}
	else
	{
		remainder = weak_div_remainder(dividend, divisor, quotient, firstObjListLength, secondObjListLength, quotientLength, len, &remainderLength);
		printf("Quotient:\n");
		for (i = 0; i < quotientLength; i++)
		{
			printf("\t%s\n", quotient[i]);
		}
		printf("Remainder:\n");
		for (i = 0; i < remainderLength; i++)
		{
			printf("\t%s\n", remainder[i]);
		}
	}
	

	return TCL_OK;
}
