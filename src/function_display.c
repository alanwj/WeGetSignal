#include "function_display.h"

#include <gtk/gtk.h>
#include <math.h>

struct _FunctionDisplay {
  GtkDrawingArea parent;
};

struct _FunctionDisplayClass {
  GtkDrawingAreaClass parent_class;
};

G_DEFINE_TYPE(FunctionDisplay, function_display, GTK_TYPE_DRAWING_AREA)

static void set_pixel_line_width(cairo_t *cr, double pixels) {
  double ux = pixels;
  double uy = pixels;
  cairo_device_to_user_distance(cr, &ux, &uy);
  if (ux < uy) {
    ux = uy;
  }
  cairo_set_line_width(cr, ux);
}

static gboolean function_display_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
  const guint width = gtk_widget_get_allocated_width(widget);
  const guint height = gtk_widget_get_allocated_height(widget);

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_rectangle(cr, 0.0, 0.0, width, height);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
  cairo_translate(cr, 0.0, height / 2.0);
  cairo_scale(cr, width / (G_PI * 2.0), height / -2.0);
  set_pixel_line_width(cr, 1.0);

  cairo_move_to(cr, 0.0, 0.0);
  for (double x = 0.0; x < (G_PI * 2.0); x += .001) {
    cairo_line_to(cr, x, sin(x));
  }
  cairo_stroke(cr);
  return TRUE;
}

static void function_display_class_init(FunctionDisplayClass *klass) {
}

static void function_display_init(FunctionDisplay *self) {
  g_signal_connect(self, "draw", G_CALLBACK(function_display_draw), NULL);
}

GtkWidget *function_display_new(void) {
  return GTK_WIDGET(g_object_new(FUNCTION_DISPLAY_TYPE, NULL));
}
