#include "hw14.h"

int main(void) {
  struct DOMNode *root = alloc_node(0, LAYOUT_HORIZ);
  struct DOMNode *node1 = alloc_node(1, LAYOUT_VERT);
  struct DOMNode *node2 = alloc_node(2, LAYOUT_NONE);
  struct DOMNode *node3 = alloc_node(3, LAYOUT_NONE);
  struct DOMNode *node4 = alloc_node(4, LAYOUT_NONE);

  add_child(root, node1);
  add_child(root, node4);

  add_child(node1, node2);
  add_child(node1, node3);

  render(root, 100, 100);

  free_DOMTree(root);

  return 0;
}
