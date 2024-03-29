#pragma once
#ifndef FILE_H
#define FILE_H

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Enable GNU C Extensions */
#define _GNU_SOURCE

/* https://linux.die.net/man/3/lseek64 */
#define _FILE_OFFSET_BITS 64

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#include <fcntl.h>

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <fileapi.h>
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#endif

#ifdef _WIN32
bool file_exists(const char* path);
LARGE_INTEGER file_size (const char* filename);
#else
bool file_exists(const char* path);
off_t file_size (const char* filename);
bool under_limit(const char* path, off_t size);
char* read_file(const char* path);
char* read_slice(const char* path, off_t beg, off_t end);
void write_file(const char* path, const char* contents, const char* mode);
void append_file(const char* src, const char* dest);
size_t find_str_offset(const char* src, const char* search_term);
#endif

#ifdef __cplusplus
}
#endif

#endif // FILE_H
