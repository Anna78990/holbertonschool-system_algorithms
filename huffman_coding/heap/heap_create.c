#include "heap.h"

/**
 * heap_create - Creaate new heap
 *
 * @data_cmp: pointer to function to use
 *
 * Return: pointer to the created heap or NULL if it fails
 */

heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new = malloc(sizeof(heap_t));

	if (!new)
		return (NULL);
	new->data_cmp = data_cmp;
	new->root = NULL;
	new->size = 0;
	return (new);

}
