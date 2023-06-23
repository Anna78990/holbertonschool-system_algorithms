#include "nary_trees.h"

/**
 * print_traverse - print n-ary tree recursively
 * @root: pointer to root of the tree
 * @d: depth
 * @action: pointer of function to print
 * Return: depth
 */
size_t print_traverse(nary_tree_t const *root, size_t d,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	nary_tree_t *child;

	if (!root)
		return (d);

	action(root, d);
	if (root->children)
	{
		child = root->children;
		while (child)
		{
			print_traverse(child, d + 1, action);
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

	return (print_traverse(root, d, action));
}
