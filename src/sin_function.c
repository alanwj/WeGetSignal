#include "sin_function.h"

#include <glib-object.h>
#include <math.h>

#include "signal_function.h"

struct _SinFunction {
  GObject parent;

  double amplitude;
  double frequency;
  double phase;
};

struct _SinFunctionClass {
  GObjectClass parent_class;
};

enum {
  PROP_0,

  PROP_AMPLITUDE,
  PROP_FREQUENCY,
  PROP_PHASE,

  N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES] = {NULL, };


static double sin_function_eval(SignalFunction *func, double x) {
  SinFunction *self = SIN_FUNCTION(func);
  return self->amplitude * sin(2.0 * G_PI * self->frequency * x + self->phase);
}

static void signal_function_interface_init(SignalFunctionInterface *iface) {
  iface->eval = sin_function_eval;
}

G_DEFINE_TYPE_WITH_CODE(SinFunction, sin_function, G_TYPE_OBJECT,
    G_IMPLEMENT_INTERFACE(SIGNAL_FUNCTION_TYPE, signal_function_interface_init))

static void sin_function_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
  SinFunction *self = SIN_FUNCTION(object);
  switch (property_id) {
   case PROP_AMPLITUDE:
    self->amplitude = g_value_get_double(value);
    break;
   case PROP_FREQUENCY:
    self->frequency = g_value_get_double(value);
    break;
   case PROP_PHASE:
    self->phase = g_value_get_double(value);
    break;
   default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    break;
  }
}

static void sin_function_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
  SinFunction *self = SIN_FUNCTION(object);
  switch (property_id) {
   case PROP_AMPLITUDE:
    g_value_set_double(value, self->amplitude);
    break;
   case PROP_FREQUENCY:
    g_value_set_double(value, self->frequency);
    break;
   case PROP_PHASE:
    g_value_set_double(value, self->phase);
    break;
   default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    break;
  }
}

static void sin_function_class_init(SinFunctionClass *klass) {
  GObjectClass *parent_class = G_OBJECT_CLASS(klass);
  parent_class->set_property = sin_function_set_property;
  parent_class->get_property = sin_function_get_property;

  properties[PROP_AMPLITUDE] = g_param_spec_double(
      "amplitude", "amplitude", "Wave amplitude",
      -G_MAXDOUBLE, G_MAXDOUBLE, 1.0,
      G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  properties[PROP_FREQUENCY] = g_param_spec_double(
      "frequency", "frequency", "Wave frequency",
      -G_MAXDOUBLE, G_MAXDOUBLE, 1.0,
      G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  properties[PROP_PHASE] = g_param_spec_double(
      "phase", "phase", "Wave phase",
      -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
      G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties(parent_class, N_PROPERTIES, properties);
}

static void sin_function_init(SinFunction *self) {
}

SignalFunction *sin_function_new(double amplitude, double frequency, double phase) {
  return SIGNAL_FUNCTION(g_object_new(
      SIN_FUNCTION_TYPE,
      "amplitude", amplitude,
      "frequency", frequency,
      "phase", phase,
      NULL));
}
