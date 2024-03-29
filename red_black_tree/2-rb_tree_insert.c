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

	if (!right)
		return;
	node->right = right->left;

	if (right->left != NULL)
		right->left->parent = node;
	right->left = node;
	right->parent = node->parent;

	if (node->parent == NULL)
		*tree = right;
	else if (node == node->parent->left)
		node->parent->left = right;
	else
		node->parent->right = right;

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

	if (!left)
		return;

	node->left = left->right;
	if (left->right != NULL)
		left->right->parent = node;
	left->right = node;
	left->parent = node->parent;

	if (node->parent == NULL)
		*tree = left;
	else if (node == node->parent->right)
		node->parent->right = left;
	else
		node->parent->left = left;

	node->parent = left;
}

/**
 * rb_insert_case - Handles case 1 of Red-Black Tree insertion fixup
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @parent: Pointer to the parent node
 * @uncle: Pointer to the uncle node
 * @grandparent: Pointer to the grandparent node
 * @node: Pointer to the newly inserted node
 * Return: pointer to new node
 */
rb_tree_t *rb_insert_case(rb_tree_t **tree, rb_tree_t *parent,
		rb_tree_t *uncle, rb_tree_t *grandparent, rb_tree_t *node)
{
	if (uncle != NULL && uncle->color == RED)
	{
		uncle->color = BLACK;
		parent->color = BLACK;
		grandparent->color = RED;
		node = grandparent;
	}
	else
	{
		if (node == parent->left)
		{
			node = parent;
			rb_rotate_right(tree, node);
			parent = node->parent;
		}
		parent->color = BLACK;
		parent->parent->color = RED;
		rb_rotate_left(tree, parent->parent);
	}
	return (node);

}

/**
 * rb_insert_fixup - Fixes the Red-Black Tree properties after insertion
 * @tree: Double pointer to the root node of the Red-Black Tree
 * @node: Pointer to the newly inserted node
 */
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *parent, *grandparent, *uncle = NULL;

	while (node->parent && node->parent->color == RED)
	{
		parent = node->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left)
		{
			uncle = grandparent->right;
			if (uncle != NULL && uncle->color == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				grandparent->color = RED;
				node = grandparent;
			}
			else
			{
				if (node == parent->right)
				{
					node = node->parent;
					rb_rotate_left(tree, node);
					parent = node->parent;
				}
				parent->color = BLACK;
				parent->parent->color = RED;
				rb_rotate_right(tree, parent->parent);
			}
		}
		else
		{
			uncle = grandparent->left;
			node = rb_insert_case(tree, parent, uncle, grandparent, node);
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

	if (!tree)
		return (NULL);
	while (current != NULL)
	{
		parent = current;
		if (value < current->n)
			current = current->left;
		else if (value > current->n)
			current = current->right;
		else
			return (NULL);
	}

	new_node = rb_tree_node(parent, value, RED);
	if (new_node == NULL)
		return (NULL);

	if (parent == NULL)
	{
		new_node->color = BLACK;
		*tree = new_node;
		return (new_node);
	}
	if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	rb_insert_fixup(tree, new_node);

	return (new_node);
}
