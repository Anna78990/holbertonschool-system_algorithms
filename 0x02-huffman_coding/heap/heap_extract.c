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
    binary_tree_node_t *min;
    binary_tree_node_t *temp;

    while (1) {
        min = node;

        if (node->left != NULL && heap->data_cmp(node->left->data, min->data) < 0)
            min = node->left;

        if (node->right != NULL && heap->data_cmp(node->right->data, min->data) < 0)
            min = node->right;

        if (min != node) {
            temp = node->data;
            node->data = min->data;
            min->data = temp;
            node = min;
        } else {
            break;
        }
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
        return NULL;

    extracted_data = heap->root->data;

    if (heap->size == 1) {
        free(heap->root);
        heap->root = NULL;
        heap->size--;
        return extracted_data;
    }

    last_node = get_last_node(heap);
    heap->root->data = last_node->data;

    if (last_node->parent->left == last_node)
        last_node->parent->left = NULL;
    else
        last_node->parent->right = NULL;

    if (last_node->parent != heap->root)
        heapify_down(heap, last_node->parent);
    else
        heapify_down(heap, heap->root);

    free(last_node);

    heap->size--;

    return extracted_data;
}

