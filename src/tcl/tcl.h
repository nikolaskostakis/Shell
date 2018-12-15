#ifndef TCL
#define TCL

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcl8.5/tcl.h>

#include "../main.h"
#include "../cubes/cubes.h"
#include "../io/io.h"
#include "../placement/placement.h"
#include "../sta/sta.h"
#include "../structures/structures.h"

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

int cube_intersect_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int supercube_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int distance_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int cube_cover_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int sharp_2(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int sharp(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int OFF_f(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

int read_graph(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int write_graph(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int print_graph_nodes(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int print_graph_edges(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);
int graph_critical_path(ClientData clientdata, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

#endif // TCL