#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

void binary_tree_print(const binary_tree_node_t *heap, int (*print_data)(char *, void *));
void heap_delete(heap_t *heap, void (*free_data)(void *));

/**
 * nested_print - Prints a symbol structure stored in a nested node
 *
 * @buffer: Buffer to print into
 * @data: Pointer to a node's data
 *
 * Return: Number of bytes written in buffer
 */
int nested_print(char *buffer, void *data)
{
	binary_tree_node_t *nested;
	symbol_t *symbol;
	int length;

	nested = (binary_tree_node_t *)data;
	symbol = (symbol_t *)nested->data;
	length = sprintf(buffer, "(%c/%lu)", symbol->data, symbol->freq);
	return (length);
}

/**
 * _free_nested - Frees a nested node
 *
 * @data: Data to be freed
 */
void _free_nested(void *data)
{
	binary_tree_node_t *nested;

	nested = (binary_tree_node_t *)data;
	if (nested->data)
		free(nested->data);
	free(nested);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	heap_t *priority_queue;
	char data[] = {
		'H', 'o', 'l', 'b', 'e', 'r', 't', 'o', 'n'
	};
	size_t freq[] = {
		4, 32, 5, 12, 68, 6, 11, 12, 1
	};
	size_t size = sizeof(data) / sizeof(data[0]);

	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
	{
		fprintf(stderr, "Failed to create priority queue\n");
		return (EXIT_FAILURE);
	}
	binary_tree_print(priority_queue->root, nested_print);

	heap_delete(priority_queue, &_free_nested);
	return (EXIT_SUCCESS);
}
