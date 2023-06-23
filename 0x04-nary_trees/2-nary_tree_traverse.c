#include "nary_trees.h"

/**
 * print_traverse - print n-ary tree recursively
 * @root: pointer to root of the tree
 * @d: depth
 * @max_depth: pointer to rewrite depth max when it is bigger than d
 * @action: pointer of function to print
 * Return: depth
 */
size_t print_traverse(nary_tree_t const *root, size_t d, size_t *max_depth,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	nary_tree_t *child;

	if (!root)
		return (d);
	if (d > *max_depth)
		*max_depth = d;
	action(root, d);
	if (root->children)
	{
		child = root->children;
		while (child)
		{
			print_traverse(child, d + 1, max_depth, action);
			child = child->next;
		}
	}

	return (d);
}

/**
 * nary_tree_traverse - print given n-ary tree
 * @root: root of tree
 * @action: pointer of function to print
 * Return: depth of the tree
 */
size_t nary_tree_traverse(nary_tree_t const *root,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	size_t d = 0;
	size_t max_depth = 0;

	print_traverse(root, d, &max_depth, action);
	return (max_depth);
}
