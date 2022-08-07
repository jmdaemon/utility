#pragma once
#ifndef UTILITY_H
#define UTILITY_H

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Third Party Libraries */
#include <pcre.h>

const char* is_true(bool cond);
const char *match(const char *input, const char *regex);
bool found_in(const char *elem, const char *array[], int array_size);
bool smatch(const char* input, const char* pattern);

#ifdef __cplusplus
}
#endif

#endif // UTILITY_H
