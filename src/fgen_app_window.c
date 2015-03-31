#include "fgen_app_window.h"

#include <gtk/gtk.h>

struct _FGenAppWindow {
  GtkApplicationWindow parent;
};

struct _FGenAppWindowClass {
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(FGenAppWindow, fgen_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void fgen_app_window_init(FGenAppWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));
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
