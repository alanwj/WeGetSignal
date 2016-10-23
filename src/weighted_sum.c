#include "weighted_sum.h"

#include <stdlib.h>

// Indicates whether the WeightedSum vtable has been initialized.
static bool init = false;

// Virtual table for WeightedSum.
static FunctionVtable vtable;

// Linked list node representing a Function and its weight.
typedef struct _WeightedFunction {
  struct _WeightedFunction* next;
  Function* fn;
  double weight;
} WeightedFunction;

struct _WeightedSum {
  Function fn;
  WeightedFunction* first;
  WeightedFunction* last;
  double total_weight;
};

static void Destruct(Function* fn) {
  FunctionGetVtable()->Destruct(fn);

  WeightedSum* ws_fn = (WeightedSum*)fn;

  WeightedFunction* wf = ws_fn->first;
  while (wf != NULL) {
    WeightedFunction* next = wf->next;
    FunctionFree(wf->fn);
    free(wf);
    wf = next;
  }
}

static double Eval(const Function* fn, double x) {
  const WeightedSum* ws_fn = (const WeightedSum*)fn;
  double val = 0.0;
  for (const WeightedFunction* wf = ws_fn->first; wf != NULL; wf = wf->next) {
    val += wf->weight / ws_fn->total_weight * wf->fn->_vtable->Eval(wf->fn, x);
  }
  return val;
}

// Initializes the WeightedSum virtual tale.
static void Init() {
  vtable = *FunctionGetVtable();
  vtable.Destruct = &Destruct;
  vtable.Eval = &Eval;
  init = true;
}

void WeightedSumConstruct(WeightedSum* ws_fn) {
  FunctionConstruct(&ws_fn->fn, &vtable);
  ws_fn->first = NULL;
  ws_fn->last = NULL;
  ws_fn->total_weight = 0.0;
}

WeightedSum* WeightedSumNew() {
  if (!init) {
    Init();
  }

  WeightedSum* ws_fn = malloc(sizeof(*ws_fn));
  if (ws_fn == NULL) {
    return NULL;
  }
  WeightedSumConstruct(ws_fn);
  return ws_fn;
}

bool WeightedSumAdd(WeightedSum* ws_fn, Function* fn, double weight) {
  WeightedFunction* wf = malloc(sizeof(*wf));
  if (wf == NULL) {
    return false;
  }
  wf->next = NULL;
  wf->fn = fn;
  wf->weight = weight;

  if (ws_fn->last != NULL) {
    ws_fn->last->next = wf;
  } else {
    ws_fn->first = wf;
  }
  ws_fn->last = wf;
  ws_fn->total_weight += weight;

  return true;
}
