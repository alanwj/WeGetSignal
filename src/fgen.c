#include <gtk/gtk.h>

#include "fgen_app.h"

int main(int argc, char *argv[]) {
  return g_application_run(G_APPLICATION(fgen_app_new()), argc, argv);
}
