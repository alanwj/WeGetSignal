#ifndef WEGETSIGNAL_FUNCTION_H_
#define WEGETSIGNAL_FUNCTION_H_

#include <stddef.h>

// Casts to a Function pointer.
#define FUNCTION(fn) ((Function*)fn)

// Abstract Base for all Functions.
//
// A Function is defined as any mathematical function that is periodic in the
// domain [0.0, 1.0). Functions will only ever be evaluated within this domain.
//
// To create a subclass, include a Function as its first member. During
// construction, FunctionConstruct must be called on this member with a suitable
// vtable.
typedef struct _Function { const struct _FunctionVtable* _vtable; } Function;

// Virtual table for a Function.
//
// A vtable may be created by copying the result of FunctionGetVtable and
// replacing the relevant function pointers.
typedef struct _FunctionVtable {
  // Destructs a Function, cleaning up any internally held resources, but does
  // not free the Function object itself.
  //
  // If this is replaced, the replacement function should call the original
  // Destruct to ensure parent class resources are freed.
  void (*Destruct)(Function*);

  // Evaluates a Function at a given point. By default this will always return
  // 0.0. Subclasses are expected to replace this function.
  double (*Eval)(const Function*, double);
} FunctionVtable;

// Returns the default virtual table for Function.
const FunctionVtable* FunctionGetVtable();

// Constructs a Function.
void FunctionConstruct(Function* fn, const FunctionVtable* vtable);

// Frees a Function and calls Destruct to free any resources that it owns.
//
// This may be called on any subclass of Function.
void FunctionFree(Function* fn);

// Evaluates a function at equidistant points in the domain [0.0, 1.0).
void FunctionEval(const Function* fn, double* samples, size_t count);

#endif  // WEGETSIGNAL_FUNCTION_H_
