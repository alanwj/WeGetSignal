#ifndef FUNCTION_DISPLAY_H_
#define FUNCTION_DISPLAY_H_

#include <gtk/gtk.h>
#include <stddef.h>

#include "function.h"

// Ensures that the necessary types are registers with GObject so that
// GtkBuilder can find them.
void FunctionDisplayRegisterType(void);

// Sets the Function to be displayed.
//
// Takes ownership of the Function.
//
// This does NOT generate a redraw. If a redraw is desired, call
// gtk_widget_queue_draw.
void FunctionDisplaySetFunction(GtkWidget* display, Function* fn,
                                size_t sample_count);

#endif  // FUNCTION_DISPLAY_H_
