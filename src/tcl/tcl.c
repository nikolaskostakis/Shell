#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcl8.5/tcl.h>

#include "tcl.h"
#include "../parser/parser.h"
#include "../placement/placement.h"
#include "../structures/structures.h"

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
	fclose(fp);

	parse_file(file);

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