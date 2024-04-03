#define _POSIX_SOURCE
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#define _DEFAULT_SOURCE

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int checkFileType(const char *path, struct Options *options) {
  struct stat st;
  if (lstat(path, &st) == -1) {
    perror("lstat");
    return 0;
  }

  if (options->onlySymlinks && S_ISLNK(st.st_mode)) {
    return 1;
  } else if (options->onlyDirectories && S_ISDIR(st.st_mode)) {
    return 1;
  } else if (options->onlyFiles && S_ISREG(st.st_mode)) {
    return 1;
  }

  return 0;
}

int comparator(const struct dirent **a, const struct dirent **b) {
  return strcoll((*a)->d_name, (*b)->d_name);
}

void walkDirectory(const char *dirPath, struct Options *options) {
  struct dirent **dirList;
  int n;

  n = scandir(dirPath, &dirList, NULL, options->sort ? &comparator : NULL);
  if (n == -1) {
    perror("scandir");
    return;
  }

  for (int i = 0; i < n; ++i) {
    if (strcmp(dirList[i]->d_name, ".") == 0 || strcmp(dirList[i]->d_name, "..") == 0) {
      free(dirList[i]);
      continue;
    }

    char entryPath[PATH_MAX];
    snprintf(entryPath, PATH_MAX, "%s/%s", dirPath, dirList[i]->d_name);

    if (checkFileType(entryPath, options)) {
      printf("%s\n", entryPath);
    }
    free(dirList[i]);
  }
  free(dirList);
}

int main(int argc, char **argv) {
  struct Options options = parseOptions(argc, argv);
  walkDirectory(options.directory, &options);
  return 0;
}