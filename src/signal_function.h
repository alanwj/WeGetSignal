#ifndef   SIGNAL_FUNCTION_H_
#define   SIGNAL_FUNCTION_H_

#include <glib-object.h>
#include <stddef.h>

#define SIGNAL_FUNCTION_TYPE                  (signal_function_get_type())
#define SIGNAL_FUNCTION(obj)                  (G_TYPE_CHECK_INSTANCE_CAST((obj), SIGNAL_FUNCTION_TYPE, SignalFunction))
#define IS_SIGNAL_FUNCTION(obj)               (G_TYPE_CHECK_INSTANCE_TYPE((obj), SIGNAL_FUNCTION_TYPE))
#define SIGNAL_FUNCTION_GET_INTERFACE(inst)   (G_TYPE_INSTANCE_GET_INTERFACE((inst), SIGNAL_FUNCTION_TYPE, SignalFunctionInterface))

typedef struct _SignalFunction              SignalFunction;  // never defined
typedef struct _SignalFunctionInterface     SignalFunctionInterface;
typedef struct _SignalFunctionEvalutation   SignalFunctionEvaluation;

struct _SignalFunctionInterface {
  GTypeInterface parent_interface;

  double (*eval)(SignalFunction *self, double x);
  void (*eval_range)(SignalFunction *self, SignalFunctionEvaluation *eval);
};

struct _SignalFunctionEvalutation {
  double begin;
  double end;
  size_t sample_count;
  double samples[];
};

GType signal_function_get_type(void);

double signal_function_eval(SignalFunction *self, double x);
void signal_function_eval_range(SignalFunction *self, SignalFunctionEvaluation *eval);

SignalFunctionEvaluation *signal_function_evaluation_new(double begin, double end, size_t sample_count);
void signal_function_evaluation_free(SignalFunctionEvaluation *eval);

#endif    // SIGNAL_FUNCTION_H_
