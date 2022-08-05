#include "utility.h"

/** Returns "true" if a condition is true else "false".
  Useful for printing/logging a boolean condition with printf */
const char* is_true(bool cond) {
  const char* is_true = cond ? "true" : "false";
  return is_true;
}
