#include "hw14.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// static void test_render() {
//   // (0 horiz 1 (1 vert 0.5 (2 none 0) (3 none 0)) (4 none 0))
//   struct DOMNode *root = alloc_node(0, LAYOUT_HORIZ, 1.f);
//   struct DOMNode *node1 = alloc_node(1, LAYOUT_VERT, 0.5f);
//   struct DOMNode *node2 = alloc_node(2, LAYOUT_NONE, 0.f);
//   struct DOMNode *node3 = alloc_node(3, LAYOUT_NONE, 0.f);
//   struct DOMNode *node4 = alloc_node(4, LAYOUT_NONE, 0.5f);

//   add_child(root, node1);
//   add_child(root, node4);

//   add_child(node1, node2);
//   add_child(node1, node3);

//   render(root, 100, 100, stdout);

//   free_DOMTree(root);
// }

// static void test_parse_render() {
//   char tree[] = "(0 horiz 1 (1 vert 0.5 (2 none 0) (3 none 0)) (4 none 0))";
//   struct stream s = {
//     .text = tree, .pos = 0, .length = strlen(tree)
//   };

//   struct DOMNode *root = load_tree(&s);
//   render(root, 100, 100, stdout);
// }

int main(int argc, char **argv) {
  
  if (argc < 3) {
    fprintf(stderr, "Usage: %s [input] [output]\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *source = fopen(argv[1], "r");
  if (!source) {
    fprintf(stderr, "Failed to open input file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  char buf[2048] = {0};
  fgets(buf, 2048, source);
  fclose(source);

  struct stream s = {
    .text = buf, .pos = 0, .length = strlen(buf)
  };
  struct DOMNode *root = load_tree(&s);
  

  FILE *target = fopen(argv[2], "w");
  if (!target) {
    fprintf(stderr, "Failed to open output file %s\n", argv[2]);
    return EXIT_FAILURE;
  }

  layout(root, 128, 128, target);
  fclose(target);

  return 0;
}
