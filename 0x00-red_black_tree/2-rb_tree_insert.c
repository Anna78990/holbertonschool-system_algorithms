#include <stdlib.h>
#include <stdio.h>
#include "rb_trees.h"

/**
 * rb_rotate_left - Performs a left rotation on a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @node: Pointer to the node to rotate
 */
void rb_rotate_left(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *right = node->right;

	node->right = right->left;

	if (right->left != NULL)
		right->left->parent = node;
	right->parent = node->parent;

	if (node->parent == NULL)
		*tree = right;
	else if (node == node->parent->left)
		node->parent->left = right;
	else
		node->parent->right = right;

	right->left = node;
	node->parent = right;
}

/**
 * rb_rotate_right - Performs a right rotation on a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @node: Pointer to the node to rotate
 */
void rb_rotate_right(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *left = node->left;

	node->left = left->right;

	if (left->right != NULL)
		left->right->parent = node;

	left->parent = node->parent;

	if (node->parent == NULL)
		*tree = left;
	else if (node == node->parent->right)
		node->parent->right = left;
	else
		node->parent->left = left;

	left->right = node;
	node->parent = left;
}


/**
 * rb_insert_case1 - Handles the case where the uncle is red
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @parent: Pointer to the parent node
 * @uncle: Pointer to the uncle node
 * @grandparent: Pointer to the grandparent node
 * @node: Pointer to the newly inserted node
 */
void rb_insert_case1(rb_tree_t **tree, rb_tree_t *parent, rb_tree_t *uncle, rb_tree_t *grandparent, rb_tree_t *node)
{
	uncle->color = BLACK;
	parent->color = BLACK;
	grandparent->color = RED;
	node = grandparent;
}

/**
 * rb_insert_case2 - Handles the case where the node is the right child of its parent
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @parent: Pointer to the parent node
 * @node: Pointer to the newly inserted node
 */
void rb_insert_case2(rb_tree_t **tree, rb_tree_t *parent, rb_tree_t *node)
{
	rb_rotate_left(tree, parent);
	node = parent;
}

/**
 * rb_insert_case3 - Handles the case where the node is the left child of its parent
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @parent: Pointer to the parent node
 * @grandparent: Pointer to the grandparent node
 * @node: Pointer to the newly inserted node
 */
void rb_insert_case3(rb_tree_t **tree, rb_tree_t *parent, rb_tree_t *grandparent, rb_tree_t *node)
{
	rb_rotate_right(tree, grandparent);
	parent->color = BLACK;
	grandparent->color = RED;
}

/**
 * rb_insert_fixup - Fixes the Red-Black Tree properties after insertion
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @node: Pointer to the newly inserted node
 */
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *node)
{
	while (node != *tree && node->color == RED && node->parent->color == RED)
	{
		rb_tree_t *parent = node->parent;
		rb_tree_t *grandparent = parent->parent;

		if (parent == grandparent->left)
		{
			rb_tree_t *uncle = grandparent->right;

			if (uncle != NULL && uncle->color == RED)
			{
				rb_insert_case1(tree, parent, uncle, grandparent, node);
			}
			else
			{
				if (node == parent->right)
				{
					rb_insert_case2(tree, parent, node);
					parent = node->parent;
				}
				rb_insert_case3(tree, parent, grandparent, node);
			}
		}
		else
		{
			rb_tree_t *uncle = grandparent->left;

			if (uncle != NULL && uncle->color == RED)
				rb_insert_case1(tree, parent, uncle, grandparent, node);
			else
			{
				if (node == parent->left)
				{
					rb_insert_case2(tree, parent, node);
					parent = node->parent;
				}
				rb_insert_case3(tree, parent, grandparent, node);
			}
		}
	}
	(*tree)->color = BLACK;
}


/**
 * rb_tree_insert - Inserts a value into a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @value: Value to be inserted
 *
 * Return: Pointer to the created node,
 *	   or NULL on failure or if value already exists
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *parent = NULL;
	rb_tree_t *current = *tree;
	rb_tree_t *new_node = NULL;

	while (current != NULL)
	{
		parent = current;

		if (value == current->n)
			return (NULL);

		if (value < current->n)
			current = current->left;
		else
			current = current->right;
	}

	new_node = rb_tree_node(parent, value, RED);
	if (new_node == NULL)
		return (NULL);

	if (parent == NULL)
		*tree = new_node;
	else if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	rb_insert_fixup(tree, new_node);

	return (new_node);
}
