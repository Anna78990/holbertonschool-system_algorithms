#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

void binary_tree_print(const binary_tree_node_t *, int (*)(char *, void *));
void _heap_delete(heap_t *heap, void (*)(void *));

/**
 * int_cmp - Compares two integers
 *
 * @p1: First pointer
 * @p2: Second pointer
 *
 * Return: Difference between the two strings
 */
int int_cmp(void *p1, void *p2)
{
	int *n1, *n2;

	n1 = (int *)p1;
	n2 = (int *)p2;
	return (*n1 - *n2);
}

/**
 * print_int - Stores a string in a buffer
 *
 * @buffer: Buffer to store the string
 * @data: Pointer to the string
 *
 * Return: Number of bytes written in buffer
 */
int print_int(char *buffer, void *data)
{
	int *n;

	n = (int *)data;
	return (sprintf(buffer, "(%03d)", *n));
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	heap_t *heap;
	int array[] = {
		34, 2, 45, 23, 76
	};
	size_t size = sizeof(array) / sizeof(array[0]);
	size_t i;
	binary_tree_node_t *node;
	int *extracted;

	heap = heap_create(int_cmp);
	if (heap == NULL)
	{
		fprintf(stderr, "Failed to create the heap\n");
		return (EXIT_FAILURE);
	}
	for (i = 0; i < size; ++i)
	{
		node = heap_insert(heap, &(array[i]));
		if (node == NULL)
		{
			fprintf(stderr, "Failed to insert a node\n");
			return (EXIT_FAILURE);
		}
	}
	binary_tree_print(heap->root, print_int);
	printf("Heap size: %lu\n\n", heap->size);

	extracted = (int *)heap_extract(heap);
	printf("Extracted: %d\n", *extracted);
	binary_tree_print(heap->root, print_int);
	printf("Heap size: %lu\n", heap->size);

	_heap_delete(heap, NULL);
	return (EXIT_SUCCESS);
}
