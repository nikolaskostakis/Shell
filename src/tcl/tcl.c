#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcl8.5/tcl.h>

#include "tcl.h"

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