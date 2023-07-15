#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts the two nodes of
 *				the priority queue and insert a new one
 * @priority_queue: pointer to the priority queue to extract from
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	if (priority_queue == NULL || priority_queue->size < 2)
		return 0;

	binary_tree_node_t *node1 = heap_extract(priority_queue);
	binary_tree_node_t *node2 = heap_extract(priority_queue);

	if (node1 == NULL || node2 == NULL)
		return (0);

	symbol_t *symbol1 = (symbol_t *)node1->data;
	symbol_t *symbol2 = (symbol_t *)node2->data;

	size_t new_freq = symbol1->freq + symbol2->freq;

	symbol_t *new_symbol = symbol_create(-1, new_freq);
	if (new_symbol == NULL)
		return (0);

	binary_tree_node_t *new_node = binary_tree_node(NULL, new_symbol);
	if (new_node == NULL)
	{
		symbol_free(new_symbol);
		return (0);
	}

	new_node->left = node1;
	new_node->right = node2;
	node1->parent = new_node;  // Corrected assignment order
	node2->parent = new_node;  // Corrected assignment order

	if (!heap_insert(priority_queue, new_node))
	{
		binary_tree_delete(new_node, symbol_free);
		return (0);
	}

	return (1);
}
