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
 * get_last_node - Retrieves the last node in the heap
 * @heap: Pointer to the heap
 *
 * Return: Pointer to the last node, or NULL if the heap is empty
 */
binary_tree_node_t *get_last_node(heap_t *heap)
{
	binary_tree_node_t *current;

	if (heap == NULL || heap->root == NULL)
		return (NULL);

	current = heap->root;
	while (current->right != NULL)
		current = current->right;
	if (current->left != NULL)
		current = current->left;
	return (current);
}

/**
 * heapify_down - Restores the heap property by heapifying down
 * @heap: Pointer to the heap
 * @node: Pointer to the node to start heapifying down from
 */
void heapify_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest, *left, *right;

	if (heap == NULL || node == NULL)
		return;

	smallest = node;
	left = node->left;
	if (left != NULL && heap->data_cmp(left->data, smallest->data) < 0)
		smallest = left;

	right = node->right;
	if (right != NULL && heap->data_cmp(right->data, smallest->data) < 0)
		smallest = right;

	if (smallest != node)
	{
		swap_node_data(node, smallest);
		heapify_down(heap, smallest);
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
	binary_tree_node_t *last_node;

	if (heap == NULL || heap->root == NULL)
		return (NULL);

	extracted_data = heap->root->data;
	heap->root->data = last_node->data;
	last_node = get_last_node(heap);
	if (last_node->parent != NULL)
	{
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
	}

	heapify_down(heap, heap->root);

	free(last_node);

	heap->size--;

	return (extracted_data);
}
