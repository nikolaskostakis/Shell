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
int print_design_rows(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int print_design_ios(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int print_design_components(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int print_design_nets(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int clear_design(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int place_random(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int report_WL(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int display_nets(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int tw_minimise_WL(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

#endif // TCL