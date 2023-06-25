#include "nary_trees.h"
#include <string.h>

/**
 * path_exists - check if the given path exists or not
 * @root: tree to check
 * @path: path to check
 * Return: if it existes 1, otherwise 0
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	int i;
	nary_tree_t const *ptr;

	if (!root)
		return (0);

	ptr = root;
	for (i = 0; path[i] != NULL; i++, ptr = ptr->children)
	{
		if (!ptr)
			return (0);
		for (; ptr != NULL; ptr = ptr->next)
		{
			if (strcmp(ptr->content, path[i]) == 0)
				break;
			if (!ptr->next)
				return (0);
		}
	}
	return (1);
}
