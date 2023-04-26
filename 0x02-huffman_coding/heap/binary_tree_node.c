#include "heap.h"

/**
 * binary_tree_node - Creaate new node
 *
 * @parent: pointer to parent
 * @data: pointer to data
 *
 * Return: pointer to the created node or NULL if it fails
 */

binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new = malloc(sizeof(binary_tree_node_t));

	if (!new)
		return (NULL);
	new->data = data;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;
	return (new);

}
