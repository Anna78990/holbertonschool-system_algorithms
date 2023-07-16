#include <stdlib.h>
#include "huffman.h"

/**
 * huffman_tree - Builds the Huffman tree
 * @data: Array of data
 * @freq: Array of frequencies
 * @size: Size of the arrays
 * Return: Pointer to the root node of the Huffman tree,
 *         or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *heap = NULL;
	binary_tree_node_t *node = NULL;

	if (!data || !freq || !size)
		return (NULL);

	heap = huffman_priority_queue(data, freq, size);
	if (!heap)
		return (NULL);

	while (heap->size > 1)
	{
		if (!huffman_extract_and_insert(heap))
			return (NULL);
	}
	node = heap->root->data;
	heap_delete(heap, NULL);
	return (node);
}
