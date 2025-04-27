#include "hw14.h"
#include <assert.h>
#include <stdlib.h>

static size_t length(struct DOMNodeList *list) {
  if (list == NULL)
    return 0;
  return 1 + length(list->next);
}

static void layout_helper(struct DOMNode *root, float left, float top,
                          float width, float height, FILE *target) {
  fprintf(target, "%d %.2f %.2f %.2f %.2f\n", root->id, left, top, left + width,
          top + height);

  size_t num_children = length(root->children);
  if (num_children == 0)
    return;

  // adjust for the margin
  float lr_margin = root->margin / 2 * width;
  float tb_margin = root->margin / 2 * height;
  left += lr_margin;
  top += tb_margin;
  width -= lr_margin * 2;
  height -= tb_margin * 2;

  if (root->layout_direction == LAYOUT_HORIZ) {
    float increment = width / num_children;
    for (struct DOMNodeList *cur = root->children; cur != NULL;
         cur = cur->next) {
      layout_helper(cur->node, left, top, increment, height, target);
      left += increment;
    }
  } else if (root->layout_direction == LAYOUT_VERT) {
    float increment = height / num_children;
    for (struct DOMNodeList *cur = root->children; cur != NULL;
         cur = cur->next) {
      layout_helper(cur->node, left, top, width, increment, target);
      top += increment;
    }
  } else {
    assert(root->layout_direction == LAYOUT_NONE);
    for (struct DOMNodeList *cur = root->children; cur != NULL;
         cur = cur->next) {
      layout_helper(cur->node, left, top, width, height, target);
    }
  }
}

void layout(struct DOMNode *root, float width, float height, FILE *target) {
  fprintf(target, "%.2f %.2f\n", width, height);
  layout_helper(root, 0, 0, width, height, target);
}

static void free_DOMNodeList(struct DOMNodeList *list) {
  if (list == NULL)
    return;
  free_DOMNodeList(list->next);
  free_DOMTree(list->node);
  free(list);
}

void free_DOMTree(struct DOMNode *root) {
  if (root == NULL)
    return;
  free_DOMNodeList(root->children);
  free(root);
}
