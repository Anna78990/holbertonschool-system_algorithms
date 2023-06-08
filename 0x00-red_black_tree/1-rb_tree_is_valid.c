#include <stdlib.h>
#include "rb_trees.h"



/**
 * is_bst - check if the tree is a valid BST
 * @tree: pointer to node tree
 *
 * Return: 1 if tree is a valid Red-Black Tree, 0 otherwise.
 */
int is_bst(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (1);

	if (tree->left != NULL && tree->left->n >= tree->n)
		return (0);

	if (tree->right != NULL && tree->right->n <= tree->n)
		return (0);

	if (!is_bst(tree->left) || !is_bst(tree->right))
		return (0);

	return (1);
}

/**
 * no_adjacent_red_nodes - check if there are no adjacent red nodes
 * @tree: Pointer to the root node of the tree to check.
 *
 * Return: 1 if tree is a valid Red-Black Tree, 0 otherwise.
 */
int no_adjacent_red_nodes(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (1);

	if (tree->color == RED)
	{
		if ((tree->left != NULL && tree->left->color == RED) ||
			(tree->right != NULL && tree->right->color == RED))
			return (0);
	}

	if (!no_adjacent_red_nodes(tree->left) || !no_adjacent_red_nodes(tree->right))
		return (0);

	return (1);
}

/**
 * black_node_count - count the number of black nodes in a path
 * @tree: Pointer to the root node of the tree to check.
 *
 * Return: result of count
 */
int black_node_count(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	int count = 0;

	while (tree != NULL)
	{
		if (tree->color == BLACK)
			count++;

		tree = tree->left;
	}

	return (count);
}


/**
 * same_black_node_count - check if every path from root to a
 *			   NULL node has the same number of black nodes
 * @tree: poiter to node tree
 * Return: if it success return 0, otherwise 1
 */
int same_black_node_count(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (1);

	int left_count = black_node_count(tree->left);
	int right_count = black_node_count(tree->right);

	if (left_count != right_count)
		return (0);

	if (!same_black_node_count(tree->left) ||
			!same_black_node_count(tree->right))
		return (0);

	return (1);
}


/**
 * rb_tree_is_valid - Checks if a binary tree is a valid Red-Black Tree.
 * @tree: Pointer to the root node of the tree to check.
 *
 * Return: 1 if tree is a valid Red-Black Tree, 0 otherwise.
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	if (!is_bst(tree))
		return (0);

	if (tree->color != BLACK)
		return (0);

	if (!no_adjacent_red_nodes(tree))
		return (0);

	if (!same_black_node_count(tree))
		return (0);

	return (1);
}
