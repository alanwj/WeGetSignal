#include "signal_function.h"

#include <glib-object.h>
#include <stddef.h>
#include <stdlib.h>

G_DEFINE_INTERFACE(SignalFunction, signal_function, G_TYPE_INVALID)

static void signal_function_default_eval_range(SignalFunction *self, SignalFunctionEvaluation *eval) {
  const double step = (eval->end - eval->begin) / eval->sample_count;
  for (size_t i = 0; i < eval->sample_count; ++i) {
    const double x = eval->begin + step * i;
    eval->samples[i] = signal_function_eval(self, x);
  }
}

static void signal_function_default_init(SignalFunctionInterface *iface) {
  iface->eval_range = signal_function_default_eval_range;
}

double signal_function_eval(SignalFunction *self, double x) {
  g_return_val_if_fail(IS_SIGNAL_FUNCTION(self), 0.0);
  return SIGNAL_FUNCTION_GET_INTERFACE(self)->eval(self, x);
}

void signal_function_eval_range(SignalFunction *self, SignalFunctionEvaluation *eval) {
  g_return_if_fail(IS_SIGNAL_FUNCTION(self));
  SIGNAL_FUNCTION_GET_INTERFACE(self)->eval_range(self, eval);
}

SignalFunctionEvaluation *signal_function_evaluation_new(double begin, double end, size_t sample_count) {
  SignalFunctionEvaluation *eval = malloc(sizeof(*eval) + sizeof(double) * sample_count);
  if (eval != NULL) {
    eval->begin = begin;
    eval->end = end;
    eval->sample_count = sample_count;
  }
  return eval;
}

void signal_function_evaluation_free(SignalFunctionEvaluation *eval) {
  free(eval);
}
