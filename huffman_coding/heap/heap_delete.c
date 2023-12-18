#include <stdlib.h>
#include "heap.h"

/**
 * delete_tree - Deallocates a binary tree
 * @node: Pointer to the current node
 * @free_data: Pointer to a function used to free the data in each node
 */
void delete_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node == NULL)
		return;

	delete_tree(node->left, free_data);
	delete_tree(node->right, free_data);

	if (free_data != NULL)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - Deallocates a heap
 * @heap: Pointer to the heap to delete
 * @free_data: Pointer to a function used to free the data in each node
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
		return;

	delete_tree(heap->root, free_data);

	free(heap);
}
