#include "wgs_app_window.h"

#include <gtk/gtk.h>

#include "function_display.h"
#include "signal_function.h"
#include "sin_function.h"

struct _WgsAppWindow {
  GtkApplicationWindow parent;

  // HACK: remove in the future
  SignalFunction *func;
};

struct _WgsAppWindowClass {
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(WgsAppWindow, wgs_app_window, GTK_TYPE_APPLICATION_WINDOW)

// HACK: remove in the future
static void show(GtkWidget *widget, gpointer data) {
  WgsAppWindow *self = WGS_APP_WINDOW(widget);
  FunctionDisplay *display = FUNCTION_DISPLAY(gtk_bin_get_child(GTK_BIN(self)));

  SignalFunctionEvaluation *eval = signal_function_evaluation_new(0.0, 1.0, 44100);
  signal_function_eval_range(self->func, eval);
  function_display_update(display, eval);
  signal_function_evaluation_free(eval);
}

static void wgs_app_window_init(WgsAppWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));

  // HACK: remove in the future
  self->func = sin_function_new(1.0, 2.0, 0.0);
  g_signal_connect(self, "show", G_CALLBACK(show), NULL);
}

static void wgs_app_window_class_init(WgsAppWindowClass *klass) {
  gtk_widget_class_set_template_from_resource(
      GTK_WIDGET_CLASS(klass), "/com/alanwj/WeGetSignal/main-window.ui");
}

WgsAppWindow *wgs_app_window_new(WgsApp *app) {
  return g_object_new(
      WGS_APP_WINDOW_TYPE,
      "application", app,
      NULL);
}
