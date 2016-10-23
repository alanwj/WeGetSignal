#ifndef WEGETSIGNAL_SINE_H_
#define WEGETSIGNAL_SINE_H_

// The trigonometric sine function.
typedef struct _Sine Sine;

// Constructs a Sine.
void SineConstruct(Sine* sine_fn, double amp, double freq, double phase);

// Creates a new Sine.
Sine* SineNew(double amp, double freq, double phase);

#endif  // WEGETSIGNAL_SINE_H_
