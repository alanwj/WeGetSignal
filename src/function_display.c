#include "function_display.h"

#include <stdlib.h>

// Provides the GObject type class for FunctionDisplay.
#define FUNCTION_DISPLAY_TYPE (function_display_get_type())

// Casts to a FunctionDisplay pointer.
#define FUNCTION_DISPLAY(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), FUNCTION_DISPLAY_TYPE, FunctionDisplay))

// A widget for drawing a Function. Derived from GtkDrawingArea.
typedef struct _FunctionDisplay FunctionDisplay;
typedef struct _FunctionDisplayClass FunctionDisplayClass;

struct _FunctionDisplay {
  GtkDrawingArea parent;

  cairo_surface_t* surface;
  Function* fn;
  double* samples;
  size_t sample_count;
};

struct _FunctionDisplayClass {
  GtkDrawingAreaClass parent_class;
};

G_DEFINE_TYPE(FunctionDisplay, function_display, GTK_TYPE_DRAWING_AREA)

// Replaces a FunctionDisplay's surface and destroys the old surface.
static void ReplaceSurface(FunctionDisplay* self, cairo_surface_t* surface) {
  cairo_surface_t* old_surface = self->surface;
  self->surface = surface;
  if (old_surface != NULL) {
    cairo_surface_destroy(old_surface);
  }
}

// Plots the FunctionDisplay's samples on a new surface.
static cairo_surface_t* PlotSamples(GtkWidget* widget) {
  FunctionDisplay* self = FUNCTION_DISPLAY(widget);

  const guint width = gtk_widget_get_allocated_width(widget);
  const guint height = gtk_widget_get_allocated_height(widget);

  cairo_surface_t* surface =
      cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
  cairo_t* cr = cairo_create(surface);

  // Draw empty background.
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_rectangle(cr, 0.0, 0.0, width, height);
  cairo_fill(cr);

  // Set y=0.0 in the center.
  cairo_translate(cr, 0.0, height / 2.0);

  // Flip the y-axis to match how functions are normally plotted.
  cairo_scale(cr, 1.0, -1.0);

  // Draw time axis.
  cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
  cairo_move_to(cr, 0.0, 0.0);
  cairo_line_to(cr, width, 0.0);

  // Draw quarter markings.
  for (guint i = 1; i < 4; ++i) {
    double x = i * (width / 4.0);
    cairo_move_to(cr, x, height);
    cairo_line_to(cr, x, -height);
  }
  cairo_stroke(cr);

  // If there is a Function, plot the samples.
  if (self->fn != NULL) {
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);

    // This scaling is done manually to maintain the 1px width plot lines.
    const double xscale = width / (double)(self->sample_count - 1);
    const double yscale = height / 2.0;

    cairo_move_to(cr, 0.0, self->samples[0]);
    for (size_t i = 1; i < self->sample_count; ++i) {
      cairo_line_to(cr, i * xscale, self->samples[i] * yscale);
    }
  }

  cairo_stroke(cr);
  cairo_destroy(cr);

  return surface;
}

// Callback function for the "draw" event.
static gboolean Draw(GtkWidget* widget, cairo_t* cr, gpointer data) {
  FunctionDisplay* self = FUNCTION_DISPLAY(widget);

  // If there is no surface, create one with the current samples plotted.
  if (self->surface == NULL) {
    ReplaceSurface(self, PlotSamples(widget));
  }

  // Paint the surface.
  cairo_set_source_surface(cr, self->surface, 0, 0);
  cairo_paint(cr);
  return TRUE;
}

// Callback function for the "configure-event" event.
static gboolean Configure(GtkWidget* widget, GdkEvent* event, gpointer data) {
  FunctionDisplay* self = FUNCTION_DISPLAY(widget);

  // Destroy the cached surface, forcing a redraw on the next "draw" event.
  ReplaceSurface(self, NULL);
  return FALSE;
}

// Callback function for the "destroy" event.
static void Destroy(GtkWidget* widget, gpointer data) {
  FunctionDisplay* self = FUNCTION_DISPLAY(widget);
  if (self->fn != NULL) {
    FunctionFree(self->fn);
    free(self->samples);
    self->sample_count = 0;
  }
  if (self->surface != NULL) {
    cairo_surface_destroy(self->surface);
    self->surface = NULL;
  }
}

static void function_display_class_init(FunctionDisplayClass* klass) {}

static void function_display_init(FunctionDisplay* self) {
  self->surface = NULL;
  self->fn = NULL;
  self->samples = NULL;
  self->sample_count = 0;

  g_signal_connect(self, "draw", G_CALLBACK(Draw), NULL);
  g_signal_connect(self, "configure-event", G_CALLBACK(Configure), NULL);
  g_signal_connect(self, "destroy", G_CALLBACK(Destroy), NULL);
}

void FunctionDisplayRegisterType(void) { function_display_get_type(); }

void FunctionDisplaySetFunction(GtkWidget* display, Function* fn,
                                size_t sample_count) {
  FunctionDisplay* self = FUNCTION_DISPLAY(display);

  double* samples = malloc(sample_count * sizeof(*samples));
  if (samples == NULL) {
    // Oh well, nothing to be done about this. Maybe add some logging.
    return;
  }
  FunctionEval(fn, samples, sample_count);

  // Replace old resources.
  if (self->fn != NULL) {
    FunctionFree(self->fn);
    free(self->samples);
  }
  self->fn = fn;
  self->samples = samples;
  self->sample_count = sample_count;

  // Destroy the cached surface, forcing a redraw on the next "draw" event.
  ReplaceSurface(self, NULL);
}
