#include "function.h"

#include <stdlib.h>

// Default Function destructor.
static void Destruct(Function* fn) {}

// Default evaluation function. Always returns 0.0.
static double Eval(const Function* fn, double x) { return 0.0; }

// Virtual table for Function.
static FunctionVtable vtable = {&Destruct, &Eval};

const FunctionVtable* FunctionGetVtable() { return &vtable; }

void FunctionConstruct(Function* fn, const FunctionVtable* vtable) {
  fn->_vtable = vtable;
}

void FunctionFree(Function* fn) {
  if (fn != NULL) {
    fn->_vtable->Destruct(fn);
    free(fn);
  }
}

void FunctionEval(const Function* fn, double* samples, size_t count) {
  double (*eval)(const Function*, double) = fn->_vtable->Eval;
  for (size_t i = 0; i < count; ++i) {
    samples[i] = eval(fn, i / (double)count);
  }
}
