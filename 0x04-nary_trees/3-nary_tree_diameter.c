#include "nary_trees.h"


void max_depth(nary_tree_t const *node, size_t cur_d, size_t *max_d,
		nary_tree_t *deepest)
{
    if (depth > *max_d)
    {
        max_d = cur_d;
        deepest = node;
    }

    for (nary_tree_t *child = node->children; child != NULL; child = child->next)
        max_depth(child, cur_d + 1, max_d, deepest);
}

size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t max_depth = 0;
	nary_tree_t *deepest;

	max_depth(root, 0, max_depth, deepest);

}
