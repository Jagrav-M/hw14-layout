#include "hw14.h"
#include <assert.h>
#include <stdlib.h>

static size_t length(struct DOMNodeList *list) {
  if (list == NULL)
    return 0;
  return 1 + length(list->next);
}

static void render_helper(struct DOMNode *root, float left, float top,
                          float width, float height) {
  printf("%d (%.2f, %.2f) to (%.2f, %.2f)\n", root->id, left, top, left + width,
         top + height);

  size_t num_children = length(root->children);
  if (num_children == 0)
    return;
  float padded_space = (num_children + 1) * root->padding;
  if (root->layout == LAYOUT_HORIZ) {
    float increment = (width - padded_space) / num_children;
    left += root->padding;
    for (struct DOMNodeList *cur = root->children; cur != NULL;
         cur = cur->next) {
      render_helper(cur->node, left, top, increment, height);
      left += increment + root->padding;
    }
  } else if (root->layout == LAYOUT_VERT) {
    float increment = (height - padded_space) / num_children;
    top += root->padding;
    for (struct DOMNodeList *cur = root->children; cur != NULL;
         cur = cur->next) {
      render_helper(cur->node, left, top, width, increment);
      top += increment + root->padding;
    }
  } else {
    assert(root->layout == LAYOUT_NONE);
    for (struct DOMNodeList *cur = root->children; cur != NULL;
         cur = cur->next) {
      render_helper(cur->node, left, top, width, height);
    }
  }
}

void render(struct DOMNode *root, float window_width, float window_height) {
  render_helper(root, 0, 0, window_width, window_height);
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
