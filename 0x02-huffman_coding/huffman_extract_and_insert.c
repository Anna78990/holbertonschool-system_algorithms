
#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes from the priority queue
 *                              and inserts a new one
 * @priority_queue: Pointer to the priority queue (min heap)
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_node;
	symbol_t *symbol1, *symbol2, *new_symbol;

	if (!priority_queue || priority_queue->size < 2)
		return (0);
	node1 = heap_extract(priority_queue);
	node2 = heap_extract(priority_queue);
	if (!node1 || !node2)
		return (0);

	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;

	new_symbol = symbol_create(-1, symbol1->freq + symbol2->freq);
	if (!new_symbol)
	{
		free(new_symbol);
		return (0);
	}
	new_node = binary_tree_node(NULL, new_symbol);
	if (!new_node)
	{
		free(new_symbol);
		return (0);
	}

	new_node->left = node1;
	new_node->right = node2;
	node1->parent = new_node;
	node2->parent = new_node;
	if (heap_insert(priority_queue, new_node) == NULL)
	{
		return (0);
	}

	return (1);
}

