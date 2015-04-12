#ifndef   SIN_FUNCTION_H_
#define   SIN_FUNCTION_H_

#include <glib-object.h>

#include "signal_function.h"

#define SIN_FUNCTION_TYPE   (sin_function_get_type())
#define SIN_FUNCTION(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj), SIN_FUNCTION_TYPE, SinFunction))

typedef struct _SinFunction         SinFunction;
typedef struct _SinFunctionClass    SinFunctionClass;

GType sin_function_get_type(void);

SignalFunction *sin_function_new(double amplitude, double frequency, double phase);

#endif    // SIN_FUNCTION_H_
