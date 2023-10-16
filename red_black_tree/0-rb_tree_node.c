#include <stdlib.h>
#include "rb_trees.h"

/**
 * rb_tree_node - Creates a Red-Black Tree node.
 * @parent: Pointer to the parent node of the node to create.
 * @value: Value to put in the new node.
 * @color: Color of the node.
 *
 * Return: Pointer to the new node, or NULL on failure.
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node = malloc(sizeof(rb_tree_t));

	if (new_node == NULL)
		return (NULL);

	new_node->n = value;
	new_node->color	= color;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right	= NULL;

	return (new_node);
}
