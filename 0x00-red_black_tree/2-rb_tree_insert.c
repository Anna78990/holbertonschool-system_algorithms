#include <stdlib.h>
#include "rb_trees.h"

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);

/**
 * rotate_left - Perform a left rotation on a node
 * @node: Pointer to the node
 */
static void rotate_left(rb_tree_t **node)
{
	rb_tree_t *pivot = (*node)->right;

	if (pivot != NULL)
	{
		(*node)->right = pivot->left;
		if (pivot->left != NULL)
			pivot->left->parent = *node;

		pivot->parent = (*node)->parent;
		if ((*node)->parent != NULL)
		{
			if (*node == (*node)->parent->left)
				(*node)->parent->left = pivot;
			else
				(*node)->parent->right = pivot;
		}

		pivot->left = *node;
		(*node)->parent = pivot;

		*node = pivot;
	}
}

/**
 * rotate_right - Perform a right rotation on a node
 * @node: Pointer to the node
 */
static void rotate_right(rb_tree_t **node)
{
	rb_tree_t *pivot = (*node)->left;

	if (pivot != NULL)
	{
		(*node)->left = pivot->right;
		if (pivot->right != NULL)
			pivot->right->parent = *node;

		pivot->parent = (*node)->parent;
		if ((*node)->parent != NULL)
		{
			if (*node == (*node)->parent->left)
				(*node)->parent->left = pivot;
			else
				(*node)->parent->right = pivot;
		}

		pivot->right = *node;
		(*node)->parent = pivot;

		*node = pivot;
	}
}

/**
 * rb_tree_insert - Inserts a value into a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @value: Value to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node, *parent, *grandparent, *uncle;

	/* Create new node */
	node = malloc(sizeof(rb_tree_t));
	if (node == NULL)
		return NULL;

	node->n = value;
	node->color = RED;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	/* Insert node into the Red-Black Tree */
	if (*tree == NULL)
	{
		/* Empty tree, make the new node the root */
		*tree = node;
		node->color = BLACK;
		return node;
	}

	/* Find the appropriate position to insert the node */
	parent = NULL;
	grandparent = NULL;
	uncle = NULL;
	node->parent = *tree;

	while (node->parent != NULL)
	{
		if (value == node->parent->n)
		{
			/* Value already exists, ignore */
			free(node);
			return NULL;
		}
		else if (value < node->parent->n)
		{
			parent = node->parent;
			node->parent = parent->left;
		}
		else
		{
			parent = node->parent;
			node->parent = parent->right;
		}

		if (node->parent != NULL && node->parent->color == RED)
		{
			if (parent->left == node->parent)
			{
				grandparent = parent->parent;
				uncle = grandparent->right;
			}
			else
			{
				grandparent = parent->parent;
				uncle = grandparent->left;
			}

			if (uncle != NULL && uncle->color == RED)
			{
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				node = grandparent;
			}
			else
			{
				if (parent->left == node && grandparent->left == parent)
				{
					rotate_right(&grandparent);
					parent->color = BLACK;
					grandparent->color = RED;
				}
				else if (parent->right == node && grandparent->right == parent)
				{
					rotate_left(&grandparent);
					parent->color = BLACK;
					grandparent->color = RED;
				}
				else if (parent->left == node && grandparent->right == parent)
				{
					rotate_right(&parent);
					node = node->right;
				}
				else if (parent->right == node && grandparent->left == parent)
				{
					rotate_left(&parent);
					node = node->left;
				}

				parent = node->parent;
				parent->color = BLACK;
				grandparent = parent->parent;
				grandparent->color = RED;

				if (parent->left == node)
					rotate_right(&grandparent);
				else
					rotate_left(&grandparent);
			}

			return node;
		}
	}

	return node;
}

