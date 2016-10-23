#include "function_display.h"

#include <gtk/gtk.h>
#include <math.h>

struct _FunctionDisplay {
  GtkDrawingArea parent;

  cairo_surface_t *surface;
};

struct _FunctionDisplayClass {
  GtkDrawingAreaClass parent_class;
};

G_DEFINE_TYPE(FunctionDisplay, function_display, GTK_TYPE_DRAWING_AREA)

static gboolean function_display_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
  FunctionDisplay *self = FUNCTION_DISPLAY(widget);
  if (self->surface != NULL) {
    cairo_set_source_surface(cr, self->surface, 0, 0);
    cairo_paint(cr);
  } else {
    const guint width = gtk_widget_get_allocated_width(widget);
    const guint height = gtk_widget_get_allocated_height(widget);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_rectangle(cr, 0.0, 0.0, width, height);
    cairo_fill(cr);
  }
  return TRUE;
}

static void function_display_class_init(FunctionDisplayClass *klass) {
}

static void function_display_init(FunctionDisplay *self) {
  self->surface = NULL;

  g_signal_connect(self, "draw", G_CALLBACK(function_display_draw), NULL);
}

GtkWidget *function_display_new(void) {
  return GTK_WIDGET(g_object_new(FUNCTION_DISPLAY_TYPE, NULL));
}

void function_display_update(FunctionDisplay *self, double* samples, size_t count) {
  GtkWidget *self_widget = GTK_WIDGET(self);

  const guint width = gtk_widget_get_allocated_width(self_widget);
  const guint height = gtk_widget_get_allocated_height(self_widget);

  cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
  cairo_t *cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_rectangle(cr, 0.0, 0.0, width, height);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
  cairo_translate(cr, 0.0, height / 2.0);

  // This should be doable with cairo_scale, but it doesn't work for whatever reason.
  const double xscale = width / (double) (count - 1);
  const double yscale = height / -2.0;

  cairo_move_to(cr, 0.0, samples[0]);
  for (size_t i = 1; i < count; ++i) {
    cairo_line_to(cr, i * xscale, samples[i] * yscale);
  }
  cairo_stroke(cr);
  cairo_destroy(cr);

  cairo_surface_t *old_surface = self->surface;
  self->surface = surface;
  if (old_surface != NULL) {
    cairo_surface_destroy(old_surface);
  }
  gtk_widget_queue_draw(self_widget);
}
