#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#include "../placement/placement.h"
#include "../structures/structures.h"

#ifndef UI
#define UI

#define ZOOMSTEP      0.1
#define BOUNDZOOMIN   2
#define BOUNDZOOMOUT  0.1

extern GtkWidget *maincanvas_scroll; // scrolled window container for main canvas //
extern GtkWidget *maincanvas; // main canvas widget // 
extern cairo_t *maincanvas_cs; // main canvas cairo state // 
extern GdkDrawable *maincanvas_drawable; // drawable layout window of maincanvas //

extern GtkWidget *maincanvas_fixed;

extern GtkWidget *maincanvashscrollbar; // horizontal scrollbar for maincanvas //
extern GtkWidget *maincanvasvscrollbar; // vertical scrollbar for maincanvas //

extern GtkObject *maincanvashscrollbaradjustment; // horizontal scrollbar adjustment //
extern GtkObject *maincanvasvscrollbaradjustment; // vertical scrollbar adjustment //

extern int reversey; // reverse y-axis flag, place origin at bottom-left //

extern double scaledvpagesize, scaledhpagesize, vstep, hstep, vpagesize, hpagesize; // horizontal and vertical scrollbars adjustment parameters //

extern int maincanvasWidth; // main canvas visible dimension - width //
extern int maincanvasHeight; // main canvas visible dimension - height //
extern int maincanvasOx; // main canvas visible origin translation - x offset //
extern int maincanvasOy; // main canvas visible origin translation - y offset //

extern GtkWidget *mainwindow; // your main window //

extern int show_nets;
extern double design_ratio;

// *** Function Prototypes *** //

static void expose(GtkWidget *, GdkEventExpose *, gpointer);
static void maincanvaspaint(GtkWidget *, GdkEventExpose *, gpointer);
static void resizemaincanvas(GtkWidget *, GdkRectangle *, gpointer);
static gboolean maincanvasvscroll(GtkRange *, GtkScrollType, gdouble, gpointer);
static gboolean maincanvashscroll(GtkRange *, GtkScrollType, gdouble, gpointer);
static void scroll(GtkWidget *, GdkEventScroll *, gpointer);
void setupscrolladjustments();
static void mousebutton(GtkWidget *, GdkEventButton *, gpointer);
static void quitaction();
void start_gui();

void draw_maincancas();
void draw_shapes();

void draw_design();
void draw_io();
void draw_rows();
void draw_components();
void draw_nets();

#endif