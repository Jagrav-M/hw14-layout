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

void layout(struct DOMNode *root, float window_width, float window_height, FILE *target);
void free_DOMTree(struct DOMNode *root);


// UTILITY STUFF HERE
// DO NOT MODIFY

void add_child(struct DOMNode *parent, struct DOMNode *child);
struct DOMNode *alloc_node(int id, enum dir layout, float padding);

struct stream {
  char *text;
  size_t pos;
  size_t length;
};

struct DOMNode *load_tree(struct stream *s);

#endif // HW14
