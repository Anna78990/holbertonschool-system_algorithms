#include "heap.h"
#include <string.h>


/**
 * convert_to_bin - converts a number to a custom base
 * @num: the number to convert
 * Return: pointer to string containing digits in new base
 */
char *convert_to_bin(long num)
{
	char *BITS = "01", *ptr;
	static char buf[66];

	ptr = &buf[sizeof(buf)];
	*--ptr = 0;
	do {
		*--ptr = BITS[num % 2];
		num /= 2;
	} while (num);
	return (ptr);
}

/**
 * heap_insert - inserts new node into min heap
 * @heap: pointer to heap structure
 * @data: pointer to data
 * Return: pointer to new node or NULL
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	size_t i;
	binary_tree_node_t *new_node, *node;
	char *bit;
	void *temp;

	if (!heap)
		return (NULL);
	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);
	heap->size += 1;
	if (!heap->root)
	{
		heap->root = new_node;
		return (new_node);
	}
	bit = convert_to_bin(heap->size);
	for (node = heap->root, i = 1; i < strlen(bit) - 1; i++)
	{
		if (bit[i] == '1')
			node = node->right;
		else
			node = node->left;
	}
	if (bit[i] == '1')
		node->right = new_node;
	else
		node->left = new_node;
	new_node->parent = node, node = new_node;
	while (node->parent &&
			heap->data_cmp(node->parent->data, node->data) > 0)
	{
		temp = node->data;
		node->data = node->parent->data;
		node->parent->data = temp;
		node = node->parent;
	}
	return (new_node);
}
