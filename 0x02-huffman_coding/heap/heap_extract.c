#include <stdlib.h>
#include "heap.h"


/**
 * swap_node_data - Swaps the positions of two nodes in a binary heap
 * @node1: Pointer to the first node
 * @node2: Pointer to the second node
 */
void swap_node_data(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *tmp_data = node1->data;

	node1->data = node2->data;
	node2->data = tmp_data;
}


/**
 * heapify_down - Restores the heap property by heapifying down
 * @heap: Pointer to the heap
 */
void heapify_down(heap_t *heap)
{
	binary_tree_node_t *node, *child;

	node = heap->root;
	while (1)
	{
		if (node->left == NULL)
			break;
		if (node->right == NULL)
			child = node->left;
		else
		{
			if (heap->data_cmp(node->left->data,
						node->right->data) <= 0)
				child = node->left;
			else
				child = node->right;
		}
		if (heap->data_cmp(node->data, child->data) < 0)
			break;
		swap_node_data(node, child);
		node = child;
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: Pointer to the heap from which to extract the value
 *
 * Return: Pointer to the data that was stored in the root node of the heap,
 *		 or NULL if the function fails or the heap is NULL
 */
void *heap_extract(heap_t *heap)
{
	void *extracted_data;
	size_t bit;
	binary_tree_node_t *node;

	if (heap == NULL || heap->root == NULL)
		return (NULL);

	extracted_data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size--;
		return (extracted_data);
	}

	for (bit = 1; bit <= heap->size; bit <<= 1)
		;
	bit >>= 2;
	for (node = heap->root; bit > 0; bit >>= 1)
	{
		if (heap->size & bit)
			node = node->right;
		else
			node = node->left;
	}
	heap->root->data = node->data;
	if (node->parent->left == node)
		node->parent->left = NULL;
	else
		node->parent->right = NULL;

	free(node);
	heap->size--;
	heapify_down(heap);
	return (extracted_data);
}
