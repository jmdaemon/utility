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
bool file_exists(const char* path) {
  bool result = (access(path, F_OK) == 0) ? true : false;
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
  void* buffer = calloc(1, filesize + 1);
  if (!buffer) {
    fprintf(stderr, "Could not allocate buffer of size %ld\n", filesize + 1);
    exit(1);
  }

  char *contents = (char*) buffer;
  fread(contents, filesize, 1, fp);
  /* Reset file descriptor */
  lseek(fileno(fp), 0, SEEK_SET);
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
  void* buffer = calloc(1, chunksize + 1);
  if (!buffer) {
    fprintf(stderr, "Could not allocate buffer of size %ld\n", chunksize + 1);
    exit(1);
  }

  /* Read a slice of the file */
  char *contents = (char*) buffer;

  /* First we lseek to the given beginning offset of the file */
  int fd = fileno(fp);
  lseek(fd, beg, filesize);

  /* Then we read the contents of the file up to the chunksize */
  fread(contents, chunksize, 1, fp);

  /* Reset file descriptor */
  lseek(fd, 0, SEEK_SET);

  fclose(fp);
  return contents;
}

/** Write a string to the file specified by path */
void write_file(const char* path, const char* contents, const char* mode) {
   FILE *fp = fopen(path, mode);
   /* Check that file could be created */
   if (fp == NULL) {
     fprintf(stderr, "Could not create file\n");
     exit(1);
   }

   fprintf(fp, "%s", contents);
   fclose(fp);
}

/** Appends the contents of one file to another file. */
void append_file(const char* src, const char* dest) {
  FILE *psrc, *pdest;
  char buffer[256];

  psrc  = fopen(src, "r");
  pdest = fopen(dest, "a");

  if(psrc == NULL)
    fprintf(stderr, "Error reading file: %s\n", src);
  else
    // Read from src
    while(fgets(buffer, sizeof(buffer), psrc))
      // Append to dest
      fprintf(pdest, "%s", buffer);

  fclose(psrc);
  fclose(pdest);
}

/** Finds the first occurence of a substring in a large file.
  Note that this function does not account for repeated occurences. */
size_t find_str_offset(const char* src, const char* search_term) {
  int fd = open(src, O_RDONLY);
  size_t length = lseek(fd, 0, SEEK_END);
  void *data = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);

  if (data == NULL) {
    fprintf(stderr, "mmap() failed.\n");
    close(fd);
    exit(1);
  }

  void *ptr = memmem(data, length, search_term, strlen(search_term));

  if (ptr == NULL) {
    fprintf(stderr, "memmem() failed.\n");
    close(fd);
    exit(1);
  }

  size_t offset = ptr - data;
  munmap(data, length);
  /* Reset file descriptor */
  lseek(fd, 0, SEEK_SET);
  close(fd);
  return offset;
}

#endif
