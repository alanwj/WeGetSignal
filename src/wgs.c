#include <gtk/gtk.h>

#include "wgs_app.h"

int main(int argc, char *argv[]) {
  return g_application_run(G_APPLICATION(wgs_app_new()), argc, argv);
}
