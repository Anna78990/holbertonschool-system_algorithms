#include "rb_trees.h"

/**
 * rb_tree_remove - Removes a node from a Red-Black tree
 * @root: Pointer to the root node of the tree
 * @n: Value to search and remove from the tree
 *
 * Return: Pointer to the new root of the tree after deletion
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *target, *successor;

	if (root == NULL)
		return (NULL);

	target = rb_tree_find(root, n);
	if (target == NULL)
		return (root);

	if (target->left && target->right)
	{
		successor = rb_tree_min(target->right);
		target->n = successor->n;
		target = successor;
	}
	rb_tree_t *child = target->left ? target->left : target->right;
	rb_tree_t *parent = target->parent;

	if (child)
		child->parent = parent;

	if (!parent)
		root = child;
	else if (target == parent->left)
		parent->left = child;
	else
		parent->right = child;

	if (target->color == BLACK)
		rb_tree_delete_fixup(root, child, parent);

	free(target);
	return (root);
}
