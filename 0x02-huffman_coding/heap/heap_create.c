#include "heap.h"

/**
 * heap_create - Creaate new heap
 *
 * @data_cmp: pointer to function to use
 *
 * Return: Difference between the two strings
 */

heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new = malloc(sizeof(new));

	if (!new)
		return (NULL);
	new->data_cmp = data_cmp;
	new->root = NULL;
	new->size = 0;
	return (new);

}
