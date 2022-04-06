#include "file.h"

/*
 * Note: Some of these functions require more testing on
 * different platforms such as Windows in order to determine
 * if they work more or less the same.
 */
#ifdef _WIN32

/* Check to ensure this implementation works on windows */
bool file_exists(const char* path) {
  HANDLE* fp = fopen(path, "rb");
  bool result = (fp == NULL) ? false : true;
  fclose(fp);
  return result;
}

LARGE_INTEGER file_size (const char* filename) {
  HANDLE file;
  LARGE_INTEGER file_size;
  char *buffer;
  file = CreateFile(TEXT(filename), GENERIC_READ, 0, NULL,
      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (INVALID_FILE_HANDLE == file) {
    printf("Cannot open file %s: %s\n",
            filename, strerror(errno));
    return -1;
  }

  if (!GetFileSizeEx(file, &file_size)) {
    printf("Cannot determine size of %s: %s\n",
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
bool file_exists(const char* path) {
  FILE* fp = fopen(path, "rb");
  bool result = (fp == NULL) ? false : true;
  fclose(fp);
  return result;
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

    printf("Cannot determine size of %s: %s\n",
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
bool under_limit(const char* path, off_t size) {
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
char* read_file(const char* path) {

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

/**
  * Read a file from a specified beg to an end
  * ----------------------------------
  *
  * path: A file path
  * beg: A start offset for the file
  * end: An end offset for the file
  * returns: A chunk or slice of the file contents
  */
char* read_slice(const char* path, off_t beg, off_t end) {

  FILE *fp = fopen(path, "rb");

  off_t filesize = file_size(path);
  off_t chunksize = end - beg;

  /* Allocate a buffer for the file contents on the heap */
  void* buffer = malloc(chunksize + 1);
  if (!buffer) {
    printf("Could not allocate buffer of size %ld\n", chunksize + 1);
    exit(1);
  }

  char *contents = (char*) buffer;
  /* Read a slice of the file */

  /* First we lseek to the given beginning offset of the file */
  int fd = fileno(fp);
  lseek(fd, beg, filesize);

  /* Then we read the contents of the file up to the chunksize */
  fread(contents, chunksize, 1, fp);

  fclose(fp);
  contents[filesize] = 0;
  return contents;
}

void write_file(const char* path, const char* contents) {
   FILE *fp = fopen(path, "w");
   /* Check that file could be created */
   if (fp == NULL) {
     printf("Could not create file\n");
     exit(1);
   }

   fprintf(fp, "%s", contents);
   fclose(fp);
}
#endif
