#include "fgen_app_window.h"

#include <gtk/gtk.h>

#include "function_display.h"
#include "signal_function.h"
#include "sin_function.h"

struct _FGenAppWindow {
  GtkApplicationWindow parent;

  // HACK: remove in the future
  SignalFunction *func;
};

struct _FGenAppWindowClass {
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(FGenAppWindow, fgen_app_window, GTK_TYPE_APPLICATION_WINDOW)

// HACK: remove in the future
static void show(GtkWidget *widget, gpointer data) {
  FGenAppWindow *self = FGEN_APP_WINDOW(widget);
  FunctionDisplay *display = FUNCTION_DISPLAY(gtk_bin_get_child(GTK_BIN(self)));

  SignalFunctionEvaluation *eval = signal_function_evaluation_new(0.0, 1.0, 44100);
  signal_function_eval_range(self->func, eval);
  function_display_update(display, eval);
  signal_function_evaluation_free(eval);
}

static void fgen_app_window_init(FGenAppWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));

  // HACK: remove in the future
  self->func = sin_function_new(1.0, 2.0, 0.0);
  g_signal_connect(self, "show", G_CALLBACK(show), NULL);
}

static void fgen_app_window_class_init(FGenAppWindowClass *klass) {
  gtk_widget_class_set_template_from_resource(
      GTK_WIDGET_CLASS(klass), "/com/alanwj/FGen/main-window.ui");
}

FGenAppWindow *fgen_app_window_new(FGenApp *app) {
  return g_object_new(
      FGEN_APP_WINDOW_TYPE,
      "application", app,
      NULL);
}
