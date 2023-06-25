#include "nary_trees.h"

/**
 * max - compare two integer
 * @a: first int
 * @b: second int
 * Return: bigger int
 */
int max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

/**
 * depthOfTree - mesure the depth of given tree
 * @root: root of given tree
 * Return: depth
 */
int depthOfTree(nary_tree_t const *root)
{
	int maxdepth;
	size_t i;
	nary_tree_t *ptr;

	if (!root)
		return (0);

	maxdepth = 0;
	ptr = root->children;
	for (i = 0; i < root->nb_children; ptr = ptr->next, i++)
		maxdepth = max(maxdepth, depthOfTree(ptr));

	return (maxdepth + 1);
}

/**
 * nary_tree_diameter - mesure the diameter of given n-th tree
 * @root: root of given tree
 * Return: diameter
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	int max1, max2, h, maxChildDia;
	size_t i;
	nary_tree_t *ptr, *ptr2;

	if (!root)
		return (0);

	max1 = 0, max2 = 0;
	ptr = root->children, ptr2 = root->children;
	for (i = 0; i < root->nb_children; ptr = ptr->next, i++)
	{
		h = depthOfTree(ptr);
		if (h > max1)
			max2 = max1, max1 = h;
		else if (h > max2)
			max2 = h;
	}

	maxChildDia = 0;
	for (i = 0; i < root->nb_children; ptr2 = ptr2->next, i++)
		maxChildDia = max(maxChildDia, nary_tree_diameter(ptr2));

	return (max(maxChildDia, max1 + max2 + 1));
}

