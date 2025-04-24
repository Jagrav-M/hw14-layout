#include "hw14.h"

int main(void) {
  struct DOMNode *root = alloc_node(0, 10.f, LAYOUT_HORIZ);
  struct DOMNode *node1 = alloc_node(1, 5.f, LAYOUT_VERT);
  struct DOMNode *node2 = alloc_node(2, 0.f, LAYOUT_NONE);
  struct DOMNode *node3 = alloc_node(3, 0.f, LAYOUT_NONE);
  struct DOMNode *node4 = alloc_node(4, 5.f, LAYOUT_NONE);

  add_child(root, node1);
  add_child(root, node4);

  add_child(node1, node2);
  add_child(node1, node3);

  render(root, 100, 100);

  free_DOMTree(root);

  return 0;
}
