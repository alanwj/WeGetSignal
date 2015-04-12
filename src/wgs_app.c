#include "wgs_app.h"

#include <gtk/gtk.h>

#include "function_display.h"
#include "wgs_app_window.h"

struct _WgsApp {
  GtkApplication parent;
};

struct _WgsAppClass {
  GtkApplicationClass parent_class;
};

G_DEFINE_TYPE(WgsApp, wgs_app, GTK_TYPE_APPLICATION)

// Registers types that GtkBuilder will need to know about.
static void register_types() {
  function_display_get_type();
}

static void wgs_app_activate(GApplication *app) {
  WgsAppWindow *main_window = wgs_app_window_new(WGS_APP(app));
  gtk_window_present(GTK_WINDOW(main_window));
}

static void wgs_app_init(WgsApp *self) {
}

static void wgs_app_class_init(WgsAppClass *klass) {
  G_APPLICATION_CLASS(klass)->activate = wgs_app_activate;

  register_types();
}

WgsApp *wgs_app_new(void) {
  return g_object_new(WGS_APP_TYPE,
                      "application-id", "com.alanwj.WeGetSignal",
                      "flags", G_APPLICATION_FLAGS_NONE,
                      NULL);
}
