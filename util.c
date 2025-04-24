#include "hw14.h"
#include <stdlib.h>

static void insert_tail(struct DOMNodeList **list_ptr,
                        struct DOMNodeList *new_node) {
  if (*list_ptr == NULL) {
    *list_ptr = new_node;
    return;
  }

  struct DOMNodeList *cur;
  for (cur = *list_ptr; cur->next != NULL; cur = cur->next)
    ;
  cur->next = new_node;
}

void add_child(struct DOMNode *parent, struct DOMNode *child) {
  struct DOMNodeList *new_node = malloc(sizeof(struct DOMNodeList));
  new_node->node = child;
  insert_tail(&parent->children, new_node);
}

struct DOMNode *alloc_node(int id, float padding, enum dir layout) {
  struct DOMNode *node = malloc(sizeof(struct DOMNode *));
  node->id = id;
  // node->padding = padding;
  node->children = NULL;
  node->layout = layout;
  return node;
}
