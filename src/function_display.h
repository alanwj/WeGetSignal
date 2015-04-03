#ifndef   FUNCTION_DISPLAY_H_
#define   FUNCTION_DISPLAY_H_

#include <gtk/gtk.h>

#define FUNCTION_DISPLAY_TYPE   (function_display_get_type())
#define FUNCTION_DISPLAY(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj), FUNCTION_DISPLAY_TYPE, FunctionDisplay))

typedef struct _FunctionDisplay         FunctionDisplay;
typedef struct _FunctionDisplayClass    FunctionDisplayClass;

GType function_display_get_type(void);

GtkWidget *function_display_new(void);

#endif    // FUNCTION_DISPLAY_H_