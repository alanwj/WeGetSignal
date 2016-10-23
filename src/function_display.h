#ifndef FUNCTION_DISPLAY_H_
#define FUNCTION_DISPLAY_H_

#include <gtk/gtk.h>
#include <stddef.h>

// Ensures that the necessary types are registers with GObject so that
// GtkBuilder can find them.
void FunctionDisplayRegisterType(void);

// HACK: remove in the future
void FunctionDisplayUpdate(GtkWidget* display, double* samples, size_t count);

#endif  // FUNCTION_DISPLAY_H_
