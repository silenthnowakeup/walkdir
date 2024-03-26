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

int comparator(const struct dirent **a, const struct dirent **b) {
  return strcoll((*a)->d_name, (*b)->d_name);
}

void walkDirectory(const char *dirPath, struct Options *options) {
  struct dirent **dirList;
  int n;

  n = scandir(dirPath, &dirList, NULL, options->sort ? &comparator : NULL);

  for (int i = 0; i < n; ++i) {
    struct stat fileinfo;

    char* entryPath = calloc(strlen(dirPath) + strlen(dirList[i]->d_name) + 2, sizeof(char));
    strcpy(entryPath, dirPath);
    strcat(entryPath, "/");
    strcat(entryPath, dirList[i]->d_name);

    lstat(entryPath, &fileinfo);

    snprintf(entryPath, PATH_MAX, "%s/%s", dirPath, dirList[i]->d_name);

    if (strcmp(dirList[i]->d_name, ".") == 0 || strcmp(dirList[i]->d_name, "..") == 0) {
      free(dirList[i]);
      continue;
    }

    if(S_ISDIR(fileinfo.st_mode)) {
      if(options->onlyDirectories)
        printf("%s\n", entryPath);
      walkDirectory(entryPath, options);
    }
    else if(S_ISLNK(fileinfo.st_mode) && options->onlySymlinks) {
      printf("%s\n", entryPath);
    }
    else if(S_ISREG(fileinfo.st_mode) && options->onlyFiles) {
      printf("%s\n", entryPath);
    }

    free(dirList[i]);
    free(entryPath);
  }
  free(dirList);
}


int main(int argc, char **argv) {
  struct Options options = parseOptions(argc, argv);
  walkDirectory(options.directory, &options);
  return 0;
}


