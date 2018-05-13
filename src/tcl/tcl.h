#ifndef TCL
#define TCL

#include <tcl8.5/tcl.h>

#include "../main.h"

// Tcl Interpreter
extern Tcl_Interp *interpreter;

extern int errno;

void init_tcl();

// Tcl Functions
int less(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int ls(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

int read_design(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

#endif // TCL