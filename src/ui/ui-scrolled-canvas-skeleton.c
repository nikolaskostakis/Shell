#include "ui-scrolled-canvas-skeleton.h"

GtkWidget *maincanvas_scroll; // scrolled window container for main canvas //
GtkWidget *maincanvas; // main canvas widget // 
cairo_t *maincanvas_cs; // main canvas cairo state // 
GdkDrawable *maincanvas_drawable; // drawable layout window of maincanvas //

GtkWidget *maincanvas_fixed;

GtkWidget *maincanvashscrollbar; // horizontal scrollbar for maincanvas //
GtkWidget *maincanvasvscrollbar; // vertical scrollbar for maincanvas //

GtkObject *maincanvashscrollbaradjustment; // horizontal scrollbar adjustment //
GtkObject *maincanvasvscrollbaradjustment; // vertical scrollbar adjustment //

int reversey = 0; // reverse y-axis flag, place origin at bottom-left //

double scaledvpagesize, scaledhpagesize, vstep, hstep, vpagesize, hpagesize; // horizontal and vertical scrollbars adjustment parameters //

int maincanvasWidth = 550; // main canvas visible dimension - width //
int maincanvasHeight = 550; // main canvas visible dimension - height //
int maincanvasOx = 0; // main canvas visible origin translation - x offset //
int maincanvasOy = 0; // main canvas visible origin translation - y offset //

GtkWidget *mainwindow; // your main window //

double zoomvalue = 1;
double hscrollvalue = 0;
double vscrollvalue = 0;

int show_nets = 0;
double design_ratio = 0;

// Expose-Event Paint Function for maincanvas //
static void expose(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	#ifdef DEBUGMODE
	{
		printf("DEBUG: Canvas Expose\n");
	}
	#endif  

	maincanvaspaint(widget, event, data);
}

// Expose-Event Paint Function for maincanvas //
static void maincanvaspaint(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	maincanvas_drawable = maincanvas->window; // drawable drawing area window //
	//  maincanvas_drawable = GTK_LAYOUT(maincanvas)->bin_window; // drawable layout window //
	maincanvas_cs = gdk_cairo_create(maincanvas_drawable); // corresponding cairo state //

	// call main drawing function //
	draw_maincancas();
	cairo_destroy(maincanvas_cs);
}

// 
void draw_maincancas()
{
	int width = maincanvasWidth ;
	int height = maincanvasHeight ;

	// Draw Canvas
	cairo_set_source_rgb(maincanvas_cs, 0, 0, 0);
	cairo_rectangle(maincanvas_cs, 0, 0, width, height);
	cairo_fill(maincanvas_cs);
	
	setupscrolladjustments();

	if (design_name == NULL)
		draw_shapes();
	else
		draw_design();
}

void draw_shapes()
{
	cairo_text_extents_t te;

	// Red filled Square
	cairo_rectangle(maincanvas_cs, 40*zoomvalue - maincanvasOx, 40*zoomvalue - maincanvasOy, 100*zoomvalue, 100*zoomvalue);
	cairo_set_source_rgb(maincanvas_cs, 1, 0, 0);
	cairo_fill(maincanvas_cs);

	cairo_set_source_rgb(maincanvas_cs, 1, 1, 1);
	cairo_select_font_face (maincanvas_cs, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (maincanvas_cs, 15*zoomvalue);
	cairo_text_extents (maincanvas_cs, "Square", &te);
	cairo_move_to (maincanvas_cs, (40 + 50)*zoomvalue - maincanvasOx - te.width / 2 - te.x_bearing,
	    (40 + 50)*zoomvalue - maincanvasOy - te.height / 2 - te.y_bearing);
	cairo_show_text (maincanvas_cs, "Square");

	// Green-ish Rectangle
	cairo_rectangle(maincanvas_cs, 340*zoomvalue - maincanvasOx, 430*zoomvalue - maincanvasOy, 100*zoomvalue, 40*zoomvalue);
	cairo_set_source_rgb(maincanvas_cs, 153/255, 255/255, 204/255);
	cairo_stroke(maincanvas_cs);
	
	cairo_set_source_rgb(maincanvas_cs, 153/255, 255/255, 204/255);
	cairo_select_font_face (maincanvas_cs, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (maincanvas_cs, 15*zoomvalue);
	cairo_text_extents (maincanvas_cs, "Rectangle", &te);
	cairo_move_to (maincanvas_cs, (340 + 50)*zoomvalue - maincanvasOx - te.width / 2 - te.x_bearing,
	    (430 + 20)*zoomvalue - maincanvasOy - te.height / 2 - te.y_bearing);
	cairo_show_text (maincanvas_cs, "Rectangle");
}

void draw_design()
{
	double x_ratio, y_ratio;

	x_ratio = floor(maincanvasWidth / (core_width + (2 * core_X_offset)));
	y_ratio = floor(maincanvasHeight / (core_height + (2 * core_Y_offset)));

	design_ratio = (x_ratio < y_ratio) ? x_ratio : y_ratio;

	draw_io();
	draw_rows();
	draw_components();

	if (show_nets == 1)
		draw_nets();
}

void draw_io()
{
	const double radius = 0.01;

	unsigned int i;

	for (i = 0; i < ioT_size; i++)
	{
		cairo_arc(maincanvas_cs, (IOT[i].x * zoomvalue * design_ratio) - maincanvasOx, (IOT[i].y * zoomvalue * design_ratio) - maincanvasOy, (radius * zoomvalue * design_ratio), 0, 2*M_PI);
		cairo_stroke_preserve(maincanvas_cs);
		cairo_set_source_rgb(maincanvas_cs, 1, 1, 0); // Yellow
		cairo_fill(maincanvas_cs);
	}
}

void draw_rows()
{
	unsigned int i;

	for (i = 0; i < rowT_size; i++)
	{
		cairo_rectangle(maincanvas_cs, (RowT[i].location_x * zoomvalue * design_ratio) - maincanvasOx, (RowT[i].location_y * zoomvalue * design_ratio) - maincanvasOy, (RowT[i].width * zoomvalue * design_ratio), (RowT[i].height * zoomvalue * design_ratio));
		cairo_set_source_rgb(maincanvas_cs, 0, 0, 1); 
		cairo_stroke(maincanvas_cs);
	}
}

void draw_components()
{
	unsigned int i;
	cairo_text_extents_t te;

	for (i = 0; i < componentT_size; i++)
	{
		cairo_rectangle(maincanvas_cs, (ComponentT[i].x * zoomvalue * design_ratio) - maincanvasOx, (ComponentT[i].y * zoomvalue * design_ratio) - maincanvasOy, (CELL_WIDTH * zoomvalue * design_ratio), (CELL_HEIGHT * zoomvalue * design_ratio));
		cairo_set_source_rgb(maincanvas_cs, 0, 1, 0);
		cairo_stroke(maincanvas_cs);

		cairo_set_source_rgb(maincanvas_cs, 0, 1, 0); 
		cairo_select_font_face (maincanvas_cs, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
		cairo_set_font_size (maincanvas_cs, 0.08 * design_ratio * zoomvalue);
		cairo_text_extents (maincanvas_cs, ComponentT[i].name, &te);
		cairo_move_to (maincanvas_cs, ((ComponentT[i].x + CELL_WIDTH/2) * zoomvalue * design_ratio) - maincanvasOx - te.width / 2 - te.x_bearing,
		    ((ComponentT[i].y + CELL_HEIGHT/2) * zoomvalue * design_ratio) - maincanvasOy - te.height / 2 - te.y_bearing);
		cairo_show_text (maincanvas_cs, ComponentT[i].name);
	}
}

void draw_nets()
{
	unsigned int i;

	cairo_set_source_rgb(maincanvas_cs, 1, 153/255, 0);
	for (i = 0; i < netT_size; i++)
	{
		if (NetT[i].edge_type_one == io)
			cairo_move_to(maincanvas_cs, (IOT[NetT[i].edge_pointer_one].x) * zoomvalue * design_ratio, (IOT[NetT[i].edge_pointer_one].y) * zoomvalue * design_ratio);
		else // Component
			cairo_move_to(maincanvas_cs, (ComponentT[NetT[i].edge_pointer_one].x + CELL_WIDTH/2) * zoomvalue * design_ratio, (ComponentT[NetT[i].edge_pointer_one].y + CELL_HEIGHT/2) * zoomvalue * design_ratio);
		
		if (NetT[i].edge_type_two == io)
			cairo_line_to(maincanvas_cs, (IOT[NetT[i].edge_pointer_two].x) * zoomvalue * design_ratio, (IOT[NetT[i].edge_pointer_two].y) * zoomvalue * design_ratio);
		else // Component
			cairo_line_to(maincanvas_cs, (ComponentT[NetT[i].edge_pointer_two].x + CELL_WIDTH/2) * zoomvalue * design_ratio, (ComponentT[NetT[i].edge_pointer_two].y + CELL_HEIGHT/2) * zoomvalue * design_ratio);
	}
	cairo_stroke(maincanvas_cs);
}

// Size-Allocate Event Function for maincanvas // 
static void resizemaincanvas(GtkWidget *widget, GdkRectangle *gdkrect, gpointer data)
{
	int newmaincanvasWidth;
	int newmaincanvasHeight;

	#ifdef DEBUGMODE
	{
		printf("DEBUG: Resize Main Canvas.\n");
		printf("DEBUG: Current Width, Height = (%d, %d), New Width, Height = (%d, %d)\n", maincanvasWidth, maincanvasHeight, gdkrect->width, gdkrect->height);
	}
	#endif

	// resize code //
	newmaincanvasWidth = gdkrect->width;
	newmaincanvasHeight = gdkrect->height;

	maincanvasWidth = newmaincanvasWidth;
	maincanvasHeight = newmaincanvasHeight;
}

static gboolean maincanvasvscroll(GtkRange *range, GtkScrollType scroll, gdouble value, gpointer data)
{
	double maxmaincanvasOy;
	int ivalue; // calibrated, inter y-offset value, based on vertical scrollbar value //
	double dvalue;
	dvalue = gtk_adjustment_get_value(GTK_ADJUSTMENT(maincanvasvscrollbaradjustment));

	#ifdef DEBUGMODE
	{
		printf("DEBUG: Vertical Scroll\n");
		printf("DEBUG: Scroll value = %.3f\n", dvalue);
	}
	#endif  

	// vertical scrollbar code here //
	maincanvasOy = (scaledvpagesize - maincanvasHeight)/2 + dvalue;
	vscrollvalue = dvalue;
	gtk_widget_queue_draw(maincanvas);
	
}

static gboolean maincanvashscroll(GtkRange *range, GtkScrollType scroll, gdouble value, gpointer data)
{
	double maxmaincanvasOx;
	int ivalue; // calibrated, inter x-offset value, based on horizontal scrollbar value //
	double dvalue;
	dvalue = gtk_adjustment_get_value(GTK_ADJUSTMENT(maincanvashscrollbaradjustment));
	#ifdef DEBUGMODE
	{
		printf("DEBUG: Horizontal Scroll\n");      
		printf("DEBUG: Scroll value = %.3f\n", dvalue);
	}
	#endif  

	// horizontal scrollbar code here //
	maincanvasOx = (scaledhpagesize - maincanvasWidth)/2 + dvalue;
	hscrollvalue = dvalue;
	gtk_widget_queue_draw(maincanvas);

}

static void scroll(GtkWidget *widget, GdkEventScroll *eev, gpointer data)
{
	#ifdef DEBUGMODE
	{
		printf("DEBUG: Canvas Mouse Scroll\n");
	}
	#endif

	// mouse wheel (scroll) code here //
	if (eev->direction == GDK_SCROLL_UP)
	{
		if (zoomvalue < BOUNDZOOMIN)
			zoomvalue += ZOOMSTEP;
	}
	if (eev->direction == GDK_SCROLL_DOWN)
	{
		if (zoomvalue > (BOUNDZOOMOUT + ZOOMSTEP))
			zoomvalue -= ZOOMSTEP;
	}

	gtk_widget_queue_draw(maincanvas);
}

void setupscrolladjustments()
{
  // setup horizontal and vertical scrollbar adjustments //
	double w, h;

	scaledhpagesize = maincanvasWidth * zoomvalue;
	scaledvpagesize = maincanvasHeight * zoomvalue;
	hstep = (scaledhpagesize - maincanvasWidth) / 10;
	vstep = (scaledvpagesize - maincanvasHeight) / 10;
	w = (scaledhpagesize - maincanvasWidth) / 2;
	h = (scaledvpagesize - maincanvasHeight) / 2;


  // use gtk_adjustment_configure() //
	if (zoomvalue <= 1)
	{
		gtk_adjustment_configure(GTK_ADJUSTMENT(maincanvashscrollbaradjustment), 0, 0, 0, 0, 0, 0);
		gtk_adjustment_configure(GTK_ADJUSTMENT(maincanvasvscrollbaradjustment), 0, 0, 0, 0, 0, 0);
	}
	else
	{
		gtk_adjustment_configure(GTK_ADJUSTMENT(maincanvashscrollbaradjustment), hscrollvalue, -w, w, hstep, 0, 0);
		gtk_adjustment_configure(GTK_ADJUSTMENT(maincanvasvscrollbaradjustment), vscrollvalue, -h, h, vstep, 0, 0);
	}
}

static void mousebutton(GtkWidget *widget, GdkEventButton *eev, gpointer data)
{
	#ifdef DEBUGMODE
	{
		printf("DEBUG: Mouse Button %d Pressed\n", eev->button);
	}
	#endif

	if (eev->button == 1) // Left Mouse Button //
	{
		// code here //
		zoomvalue = 1;
		hscrollvalue = 0;
		vscrollvalue = 0;
	}

	if (eev->button == 3) // Right Mouse Button //
	{
		// code here //
		zoomvalue = 1;
		hscrollvalue = 0;
		vscrollvalue = 0;
	}
  
	gtk_widget_queue_draw(maincanvas);
}

static void quitaction()
{
	#ifdef DEBUGMODE
	{
		printf("DEBUG: Quit Action\n");
	}
	#endif

	printf("Thank you. Bye now.\n");
	gtk_main_quit();
}


void start_gui()
{  
	// *** Local Variables *** //

	GtkWidget *maincanvashbox; // contains maincanvas and vertical scrollbar //
	GtkWidget *maincanvasvbox; // contains maincanvashbox and horizontal scrollbar //

	GtkWidget *hpane; // horizontal pane //
	GtkWidget *hpane2; // horizontal pane //

	GtkWidget *mainframe; // main canvas frame //
	GtkWidget *hierarchybrowserframe; // hierarchy browser frame //

	// *** Local Variables End *** //

	gtk_init(NULL,  NULL);

	mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(mainwindow), "CADII - Assignment 3");
	gtk_window_set_default_size(GTK_WINDOW(mainwindow), 300, 300); // default size //

	g_signal_connect(G_OBJECT(mainwindow), "destroy", G_CALLBACK(quitaction), mainwindow);

	maincanvashbox = gtk_hbox_new(FALSE, 0);
	maincanvasvbox = gtk_vbox_new(FALSE, 0);

	// Frames //
	mainframe = gtk_frame_new("Layout View");
	hierarchybrowserframe = gtk_frame_new("Other Frame");

	// Canvas Drawing Area, Frames and Associated Callbacks //
	maincanvas = gtk_drawing_area_new();
	//  maincanvas = gtk_layout_new(NULL, NULL);

	gtk_widget_set_size_request(maincanvas, maincanvasWidth, maincanvasHeight);

	// Application Paintable and Double-Buffering Flags for maincanvas //
	//  gtk_widget_set_app_paintable(maincanvas, FALSE);
	//  gtk_widget_set_double_buffered(maincanvas, FALSE);

	// maincanvas Event Handlers //
	g_signal_connect(G_OBJECT(maincanvas), "expose-event", G_CALLBACK(expose), maincanvas);

	gtk_widget_add_events(maincanvas, GDK_SCROLL);
	gtk_widget_add_events(maincanvas, GDK_BUTTON_PRESS_MASK);

	g_signal_connect(G_OBJECT(maincanvas), "scroll-event", G_CALLBACK(scroll), maincanvas);
	g_signal_connect(G_OBJECT(maincanvas), "button-press-event", G_CALLBACK(mousebutton), maincanvas);

	maincanvasvscrollbaradjustment = gtk_adjustment_new(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	maincanvashscrollbaradjustment = gtk_adjustment_new(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	// setup horizontal and vertical scrollbar adjustments //
	setupscrolladjustments();

	maincanvasvscrollbar = gtk_vscrollbar_new(GTK_ADJUSTMENT(maincanvasvscrollbaradjustment));
	maincanvashscrollbar = gtk_hscrollbar_new(GTK_ADJUSTMENT(maincanvashscrollbaradjustment));

	g_signal_connect(G_OBJECT(maincanvasvscrollbar), "value-changed", G_CALLBACK(maincanvasvscroll), maincanvasvscrollbar);
	g_signal_connect(G_OBJECT(maincanvashscrollbar), "value-changed", G_CALLBACK(maincanvashscroll), maincanvashscrollbar);

	// Two Boxes and one Pane Layout //

	gtk_box_pack_start(GTK_BOX(maincanvashbox), maincanvas, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(maincanvashbox), maincanvasvscrollbar, FALSE, FALSE, 0);

	gtk_box_set_child_packing(GTK_BOX(maincanvashbox), maincanvas, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_box_set_child_packing(GTK_BOX(maincanvashbox), maincanvasvscrollbar, FALSE, FALSE, 0, GTK_PACK_END);

	gtk_box_pack_start(GTK_BOX(maincanvasvbox), maincanvashbox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(maincanvasvbox), maincanvashscrollbar, FALSE, FALSE, 0);

	gtk_box_set_child_packing(GTK_BOX(maincanvasvbox), maincanvashbox, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_box_set_child_packing(GTK_BOX(maincanvasvbox), maincanvashscrollbar, FALSE, FALSE, 0, GTK_PACK_END);

	gtk_container_add(GTK_CONTAINER(mainframe), maincanvasvbox);

	g_signal_connect(G_OBJECT(maincanvas), "size-allocate", G_CALLBACK(resizemaincanvas), maincanvas);

	hpane = gtk_hpaned_new();
	gtk_paned_add1(GTK_PANED(hpane), hierarchybrowserframe);
	gtk_paned_add2(GTK_PANED(hpane), mainframe);  

	gtk_container_add(GTK_CONTAINER(mainwindow), hpane);

	gtk_widget_show_all(mainwindow);

	gtk_main();

}

// gint main (gint argc, gchar **argv)
// {
// 	// you may call start_gui() from TCL, based on a TCL command //
// 	// alternatively, you may create a thread, but this is a lot more complex! //
// 	start_gui();

// 	return EXIT_SUCCESS;

// }
