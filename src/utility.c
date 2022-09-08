#include "utility.h"

/*! Returns "true" if a condition is true else "false".
  Useful for printing/logging a boolean condition with printf */
const char* is_true(bool cond) {
  const char* is_true = cond ? "true" : "false";
  return is_true;
}

/*! Determine if there are any regex matches with the input text */
const char *match(const char *input, const char *regex) {
  /* for pcre_compile */
  pcre *re;
  const char *error;
  int erroffset;

  /* for pcre_exec */
  int rc;
  int ovector[32];

  /* to get substrings from regex */
  const char *substring;

  /* we'll start after the first quote and chop off the end quote */
  const char *subject = input;

  re = pcre_compile(regex, 0, &error, &erroffset, NULL);
  rc = pcre_exec(re, NULL, subject, strlen(subject), 0, 0, ovector, 30);

  if (rc == PCRE_ERROR_NOMATCH) {
    fprintf(stderr, "no match\n");
    exit(0);
  } else if (rc < -1) {
    fprintf(stderr, "error %d from regex\n",rc);
    exit(rc);
  }

  pcre_get_substring(subject, ovector, rc, 0, &substring);
  pcre_free(re);

  return substring;
}

/*! Determine if an element is found in the array of strings */
bool found_in(const char *elem, const char *array[], int array_size) {
  for (int i = 0; i < array_size; i++)
    if (smatch(elem, array[i]))
      return true;
  return false;
}

/*! Determine if a string is equal to some pattern */
bool smatch(const char* input, const char* pattern) {
  bool is_equal = (strcmp(input, pattern) == 0) ? true : false;
  return is_equal;
}

/*! Get the current time */
time_t get_time() {
    time_t t = time(NULL);
    return t;
}

/*! Create the local timestamp string from a time.
    Note that the caller is responsible for freeing the allocated string. */
char* ltimestamp(time_t t) {
    struct tm lt = {0};
    localtime_r(&t, &lt);
    char* result = (char*) malloc(5 * sizeof(char));
    sprintf(result, "%2d:%02d", lt.tm_hour, lt.tm_min);
    return result;
}
