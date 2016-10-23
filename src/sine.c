#include "sine.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "function.h"

#define TWO_PI 6.283185307179586

// Indicates whether the Sine vtable has been initialized.
static bool init = false;

// Virtual table for Sine.
static FunctionVtable vtable;

struct _Sine {
  Function fn;
  double amp;
  double freq;
  double phase;
};

static double Eval(const Function* fn, double x) {
  const Sine* sine_fn = (const Sine*)fn;
  return sine_fn->amp * sin(TWO_PI * sine_fn->freq * x + sine_fn->phase);
}

// Initializes the Sine virtual tale.
static void Init() {
  vtable = *FunctionGetVtable();
  vtable.Eval = &Eval;
  init = true;
}

void SineConstruct(Sine* sine_fn, double amp, double freq, double phase) {
  FunctionConstruct(&sine_fn->fn, &vtable);
  sine_fn->amp = amp;
  sine_fn->freq = freq;
  sine_fn->phase = phase;
}

Sine* SineNew(double amp, double freq, double phase) {
  if (!init) {
    Init();
  }

  Sine* sine_fn = malloc(sizeof(*sine_fn));
  if (sine_fn == NULL) {
    return NULL;
  }
  SineConstruct(sine_fn, amp, freq, phase);
  return sine_fn;
}
