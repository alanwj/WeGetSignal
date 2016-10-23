#ifndef WEGETSIGNAL_WEIGHTED_SUM_H_
#define WEGETSIGNAL_WEIGHTED_SUM_H_

#include <stdbool.h>

#include "function.h"

// A Function the represents the weighted sum of a collection of Functions,
// normalized by the total weight.
typedef struct _WeightedSum WeightedSum;

// Constructs a WeightedSum.
void WeightedSumConstruct(WeightedSum* ws_fn);

// Creates a new WeightedSum.
WeightedSum* WeightedSumNew();

// Adds a Function to the list of Functions evaluated by the WeightedSum.
bool WeightedSumAdd(WeightedSum* ws_fn, Function* fn, double weight);

#endif  // WEGETSIGNAL_WEIGHTED_SUM_H_
