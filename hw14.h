#ifndef HW14
#define HW14

#include <stdio.h>

enum dir { LAYOUT_HORIZ, LAYOUT_VERT, LAYOUT_NONE };

struct DOMNode;
struct DOMNodeList {
  struct DOMNode *node;
  struct DOMNodeList *next;
};

struct DOMNode {
  int id;
  float padding;
  enum dir layout;
  struct DOMNodeList *children;
};

void add_child(struct DOMNode *parent, struct DOMNode *child);
struct DOMNode *alloc_node(int id, float padding, enum dir layout);

void render(struct DOMNode *root, float window_width, float window_height);
void free_DOMTree(struct DOMNode *root);

#endif // HW14
