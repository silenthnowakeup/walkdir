//
// Created by silenth on 06.03.24.
//

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void print_usage(const char *progName) {
  printf("Usage: %s [dir] [options]\n", progName);
  printf("Options:\n");
  printf("  -l    Only symbolic links (-type l)\n");
  printf("  -d    Only directories (-type d)\n");
  printf("  -f    Only regular files (-type f)\n");
  printf("  -s    Sort output according to LC_COLLATE\n");
}

struct Options parseOptions(int argc, char** argv) {
  struct Options options = {NULL, 0, 0, 0, 0};

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      for(int j = 1; argv[i][j] != '\0'; j++) {
        switch(argv[i][j]) {
        case 'l':
          options.onlySymlinks = 1;
          break;
        case 'd':
          options.onlyDirectories = 1;
          break;
        case 'f':
          options.onlyFiles = 1;
          break;
        case 's':
          options.sort = 1;
          break;
        default:
          print_usage(argv[0]);
          exit(1);
        }
      }
    }
    else {
      if(!options.directory) {
        options.directory = argv[i];
      }
    }
  }

  if((options.onlySymlinks || options.onlyDirectories || options.onlyFiles) == 0) {
    options.onlySymlinks = 1;
    options.onlyDirectories = 1;
    options.onlyFiles = 1;
  }

  if(options.directory == 0) {
    options.directory = "./";
  }

  return options;
}
