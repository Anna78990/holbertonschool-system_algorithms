#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts the two nodes of
 *				the priority queue and insert a new one
 * @priority_queue: pointer to the priority queue to extract from
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_node;
	symbol_t *symbol1, *symbol2, *new_symbol;
	size_t new_freq;

	if (priority_queue == NULL || priority_queue->root == NULL)
		return (NULL);

	node1 = heap_extract(priority_queue);
	if (node1 == NULL)
		return (NULL);

	node2 = heap_extract(priority_queue);
	if (node2 == NULL)
	{
		free(node1);
		return (NULL);
	}

	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;

	new_freq = symbol1->freq + symbol2->freq;
	new_symbol = symbol_create(-1, new_freq);
	if (new_symbol == NULL)
	{
		free(node1);
		free(node2);
		return (NULL);
	}

	new_node = binary_tree_node(NULL, new_symbol);
	if (new_node == NULL)
	{
		free(node1);
		free(node2);
		symbol_free(new_symbol);
		return (NULL);
	}

	new_node->left = node1;
	new_node->right = node2;
	node1->parent = new_node;
	node2->parent = new_node;

	if (!heap_insert(priority_queue, new_node))
	{
		free(node1);
		free(node2);
		binary_tree_delete(new_node, symbol_free);
		return (NULL);
	}

	return (new_node);
}
