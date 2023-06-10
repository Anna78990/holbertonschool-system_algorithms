#include "heap.h"

/**
 * search_node - find n-th node of tree
 * @node: pointer to root node
 * @n: index of node
 *
 * Return: pointer to specified node or NULL on error
 */
binary_tree_node_t *search_node(binary_tree_node_t *node, int n)
{
	int bit_idx, mask;

	if (!node || n < 0)
		return (NULL);

	for (bit_idx = 0; 1 << (bit_idx + 1) <=  n; ++bit_idx)
		;
	for (--bit_idx; bit_idx >= 0; --bit_idx)
	{
		mask = 1 << bit_idx;
		if (n & mask)
		{
			if (node->right)
				node = node->right;
			else
				break;
		}
		else
		{
			if (node->left)
				node = node->left;
			else
				break;
		}
	}
	return (node);
}


/**
 * extract_root - swaps data of root and last node in tree
 * @heap: pointer to heap to extract root from
 *
 * node containing original data of root will be freed
 *
 * Return: data of exactracted root node
 */
void *extract_root(heap_t *heap)
{
	binary_tree_node_t *node;
	void *data;

	node = find_parents(heap->root, 0, heap->size);
	if (node->left == NULL && node->right == NULL)
		node = node->parent;
	if (node->parent)
	{
		data = swap_nodes(heap->root, node);
		if (node->parent->left == node)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
	}
	else
	{
		data = heap->root->data;
		heap->root = NULL;
	}
	free(node);
	if (--heap->size == 0)
		heap->root = NULL;
	return (data);
}

/**
 * heap_extract - extract root value from binary heap and restore heap property
 * @heap: pointer to heap to extract from
 *
 * Return: pointer to data stored in extracted root node or NULL on error
 */
void *heap_extract(heap_t *heap)
{
	void *data;

	if (!heap)
		return (NULL);
	data = extract_root(heap);
	return (data);
}
