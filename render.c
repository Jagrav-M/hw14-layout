#include <stdio.h>
#include <stdlib.h>

#include "libbmp/libbmp.h"

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s [layout file] [render target]\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *layout = fopen(argv[1], "r");
  if (!layout) {
    fprintf(stderr, "Failed to open layout file %s\n", argv[1]);
    return EXIT_FAILURE;
  }



  return 0;
}