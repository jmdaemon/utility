#pragma once
#ifndef FILE_H
#define FILE_H

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <fileapi.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#ifdef _WIN32
bool file_exists(HANDLE* fp);
LARGE_INTEGER file_size (const char* filename);
#else
bool file_exists(FILE* fp);
off_t file_size (const char* filename);
bool under_limit(char* path, off_t size);
char* read_file(const char* path);
void write_file(char* path, char* contents);
#endif

#endif // FILE_H
