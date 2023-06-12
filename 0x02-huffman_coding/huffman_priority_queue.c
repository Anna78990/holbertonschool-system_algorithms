#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

void symbol_free(void *data);
void binary_tree_delete(binary_tree_node_t *tree, void (*free_data)(void *));

/**
 * symbol_cmp - compare pointer s1 and s2
 * @s1: pointer to compare
 * @s2: pointer to compare
 * Return: if s1 is larger than s2 return 1, and -1 vice versa,
 *	   and returns 0 if neither is the case
 */
int symbol_cmp(void *s1, void *s2)
{
	symbol_t *sym1 = (symbol_t *)s1;
	symbol_t *sym2 = (symbol_t *)s2;

	if (sym1->freq < sym2->freq)
		return (-1);
	else if (sym1->freq > sym2->freq)
		return (1);
	else
		return (0);
}


/**
 * huffman_priority_queue - Creates a priority queue
 *			    (min heap) for Huffman coding
 * @data: Array of characters
 * @freq: Array of frequencies associated with each character
 * @size: Size of the arrays
 *
 * Return: Pointer to the created min heap (priority queue),
 *	   or NULL if it fails
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

	priority_queue = heap_create(symbol_cmp);
	if (priority_queue == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (symbol == NULL)
		{
			heap_delete(priority_queue, symbol_free);
			return (NULL);
		}

		node = binary_tree_node(NULL, symbol);
		if (node == NULL)
		{
			symbol_free(symbol);
			heap_delete(priority_queue, symbol_free);
			return (NULL);
		}

		if (heap_insert(priority_queue, node) == NULL)
		{
			binary_tree_delete(node, symbol_free);
			heap_delete(priority_queue, symbol_free);
			return (NULL);
		}
	}

	return (priority_queue);
}

/**
 * symbol_free - free symbol
 * @data: data to free
 */
void symbol_free(void *data)
{
	symbol_t *symbol = (symbol_t *)data;

	free(symbol);
}

/**
 * binary_tree_delete - delete given binary tree
 * @tree: root of tree
 * @free_data: function to free
 */
void binary_tree_delete(binary_tree_node_t *tree, void (*free_data)(void *))
{
	if (tree != NULL)
	{
		binary_tree_delete(tree->left, free_data);
		binary_tree_delete(tree->right, free_data);
		if (free_data != NULL)
			free_data(tree->data);
		free(tree);
	}
}
