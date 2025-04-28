#include "hw14.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float x, y;
} Coords;

static int ll_len(struct DOMNodeList *head);
static void layout_helper(struct DOMNode *root, float width, float height,
                          Coords start_c, FILE *target);

void layout(struct DOMNode *root, float width, float height, FILE *target) {
  fprintf(target, "%.2f %.2f\n", width, height);
  layout_helper(root, width, height, (Coords){.x = 0, .y = 0}, target);
}

static void layout_helper(struct DOMNode *root, float width, float height,
                          Coords start_c, FILE *target) {
  if (root == NULL) {
    return;
  }

  fprintf(target, "%d %.2f %.2f %.2f %.2f\n", root->id, start_c.x, start_c.y,
          start_c.x + width, start_c.y + height);

  int num_children = ll_len(root->children);

  float margin_width = width * root->margin / 2,
        margin_height = height * root->margin / 2;
  float usable_width = width - 2 * margin_width,
        usable_height = height - 2 * margin_height;

  if (root->layout_direction == LAYOUT_NONE) {
    struct DOMNodeList *curr = root->children;
    for (int i = 0; i < num_children; i++) {
      assert(curr != NULL);
      layout_helper(curr->node, usable_width, usable_height,
                    (Coords){.x = start_c.x + margin_width,
                             .y = start_c.y + margin_height},
                    target);
      curr = curr->next;
    }

    return;
  } else if (root->layout_direction == LAYOUT_HORIZ) {
    float width_per_child = usable_width / num_children;

    struct DOMNodeList *curr = root->children;
    for (int i = 0; i < num_children; i++) {
      assert(curr != NULL);
      layout_helper(
          curr->node, width_per_child, usable_height,
          (Coords){.x = start_c.x + margin_width + i * width_per_child,
                   .y = start_c.y + margin_height},
          target);
      curr = curr->next;
    }

    return;
  } else if (root->layout_direction == LAYOUT_VERT) {
    float height_per_child = usable_height / num_children;

    struct DOMNodeList *curr = root->children;
    for (int i = 0; i < num_children; i++) {
      assert(curr != NULL);
      layout_helper(
          curr->node, usable_width, height_per_child,
          (Coords){.x = start_c.x + margin_width,
                   .y = start_c.y + margin_height + i * height_per_child},
          target);
      curr = curr->next;
    }

    return;
  }
}

void free_DOMTree(struct DOMNode *root) {
  if (root == NULL) {
    return;
  }

  struct DOMNodeList *head = root->children;

  while (head != NULL) {
    struct DOMNodeList *next = head->next;
    free_DOMTree(head->node);
    head = next;
  }

  free(root);
}

static int ll_len(struct DOMNodeList *head) {
  if (head == NULL) {
    return 0;
  }

  return 1 + ll_len(head->next);
}
