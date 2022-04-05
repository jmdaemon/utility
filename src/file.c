#include "file.h"

#ifdef _WIN32
bool file_exists(HANDLE* fp) {
  if (fp == NULL) {
    printf("File Not Found!\n");
    return false;
  }
  return true;
}

LARGE_INTEGER file_size (const char* filename) {
  HANDLE file;
  LARGE_INTEGER file_size;
  char *buffer;
  file = CreateFile(TEXT(filename), GENERIC_READ, 0, NULL,
      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (INVALID_FILE_HANDLE == file) {
    fprintf(stderr, "Cannot open file %s: %s\n",
            filename, strerror(errno));
    return -1;
  }

  if (!GetFileSizeEx(file, &file_size)) {
    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));
    return -1;

  }
  return file_size;
}
#else
/**
  * Check if a file exists
  * ----------------------
  * If the file is not null then it is valid.
  *
  * fp: The file path to check
  * returns: True if the file is not null, and false otherwise
  */
bool file_exists(FILE* fp) {
  if (fp == NULL) {
    printf("File Not Found!\n");
    return false;
  }
  return true;
}

/**
  * Returns the size of the file on disk
  * ------------------------------------
  * Note that we don't to exit if the file doesn't exist
  * since we may only want to handle this. This function is 
  * capable of handling files > 4 GiB. Note that the stat
  * function is exclusive to POSIX systems.
  *
  *
  * filename: The file name/path
  * returns: The size of the file on disk, -1 if there was an error
  */
off_t file_size(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));

    return -1;
}

/**
  * Checks if a file is below a set size limit
  * ------------------------------------------
  * path: The file path
  * size: The upper bound size limit
  * returns: True if the file is less than or equal to the upper bound and False otherwise
  */
bool under_limit(char* path, off_t size) {
  size_t filesize = file_size(path);
  bool result = (filesize <= size) ? true : false;
  return result;
}

/**
  * Read a file into a character array
  * ----------------------------------
  * Note that this function assumes that the file exists
  * so make sure to check it with file_exists beforehand
  *
  * path: A file path
  * returns: The file contents as a character array
  */
char* read_file(char* path) {

  FILE *fp = fopen(path, "rb");
  /* Here is where you would check if the file exists */
  /* For now we'll assume if you open the file that it will
  exist */
  off_t filesize = file_size(path);

  /* Allocate a buffer for the file contents on the heap */
  void* buffer = malloc(filesize + 1);
  if (!buffer) {
    printf("Could not allocate buffer of size %ld\n", filesize + 1);
    exit(1);
  }

  char *contents = (char*) buffer;
  fread(contents, filesize, 1, fp);
  fclose(fp);
  contents[filesize] = 0;
  return contents;
}

void* write_file(char* path, char* contents) {
   FILE *fp = fopen(path, "w");

   /* Check that file could be created */
   if (!file_exists(fp)) {
     printf("Could not create file\n");
     exit(1);
   }

   fprintf(fp, "%s", contents);
   fclose(fp);
   return 0;
}
#endif
