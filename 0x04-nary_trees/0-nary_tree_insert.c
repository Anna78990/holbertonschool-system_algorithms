#include "nary_trees.h"
#include <string.h>
#include <stdlib.h>

/**
 * nary_tree_insert - inserts a node in a N-ary tree.
 * @parent: parent of the inserted node
 * @str: string of content in new node
 * Return: pointer to new node
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new, *child;

	if (str == NULL)
		return (NULL);

	new = (nary_tree_t *)malloc(sizeof(nary_tree_t));
	if (new == NULL)
		return (NULL);

	new->content = strdup(str);
	new->parent = parent;
	new->next = NULL;
	new->children = NULL;
	new->nb_children = 0;

	if (parent)
	{
		if (parent->children == NULL)
			parent->children = new;
		else
		{
			child = parent->children;
			while (child->next != NULL)
				child = child->next;
			child->next = new;
		}
		parent->nb_children += 1;
	}
	else
		parent = new;

	return (new);
}
