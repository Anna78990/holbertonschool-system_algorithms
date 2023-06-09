#include "rb_trees.h"

/**
 * array_to_rb_tree - Builds a Binary Search Tree from an array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created R-B tree, or NULL on failure
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	size_t i;
	rb_tree_t *root = NULL;

	if (array == NULL || size == 0)
		return (NULL);

	for (i = 0; i < size; i++)
		rb_tree_insert(&root, array[i]);

	return (root);
}
