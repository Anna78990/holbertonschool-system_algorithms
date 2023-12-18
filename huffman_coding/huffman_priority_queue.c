#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

void data_free(void *data);

/**
 * symbol_cmp - compare pointer s1 and s2
 * @s1: pointer to compare
 * @s2: pointer to compare
 * Return: if s1 is larger than s2 return 1, and -1 vice versa,
 *	   otherwise returns 0
 */
int symbol_cmp(void *s1, void *s2)
{
	symbol_t *sym1 = ((binary_tree_node_t *)s1)->data;
	symbol_t *sym2 = ((binary_tree_node_t *)s2)->data;

	return (sym1->freq - sym2->freq);
}


/**
 * huffman_priority_queue - Creates a priority queue
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of the arrays
 * Return: Pointer to the created min heap (priority queue),
 *	   or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	symbol_t *symbol;
	binary_tree_node_t *node, *node2;
	size_t i;

	if (!size || !data || !freq)
		return (NULL);
	priority_queue = heap_create(symbol_cmp);
	if (priority_queue == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (symbol == NULL)
		{
			heap_delete(priority_queue, data_free);
			return (NULL);
		}
		node = binary_tree_node(NULL, symbol);
		if (node == NULL)
		{
			data_free(symbol);
			heap_delete(priority_queue, data_free);
			return (NULL);
		}
		node2 = heap_insert(priority_queue, node);
		if (!node2)
		{
			heap_delete(priority_queue, data_free);
			return (NULL);
		}
	}

	return (priority_queue);
}


/**
 * data_free - free symbol
 * @data: data to free
 */
void data_free(void *data)
{
	free(((binary_tree_node_t *)data)->data);
	free(data);
}
