#pragma once
#ifndef COMMAND_H
#define COMMAND_H

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

char* exec(const char* command, off_t size);

#ifdef __cplusplus
}
#endif

#endif // COMMAND_H
