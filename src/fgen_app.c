#include "fgen_app.h"

#include <gtk/gtk.h>

#include "fgen_app_window.h"

struct _FGenApp {
  GtkApplication parent;
};

struct _FGenAppClass {
  GtkApplicationClass parent_class;
};

G_DEFINE_TYPE(FGenApp, fgen_app, GTK_TYPE_APPLICATION)

static void fgen_app_activate(GApplication *app) {
  FGenAppWindow *main_window = fgen_app_window_new(FGEN_APP(app));
  gtk_window_present(GTK_WINDOW(main_window));
}

static void fgen_app_init(FGenApp *self) {
}

static void fgen_app_class_init(FGenAppClass *klass) {
  G_APPLICATION_CLASS(klass)->activate = fgen_app_activate;
}

FGenApp *fgen_app_new(void) {
  return g_object_new(FGEN_APP_TYPE,
                      "application-id", "com.alanwj.FGen",
                      "flags", G_APPLICATION_FLAGS_NONE,
                      NULL);
}
