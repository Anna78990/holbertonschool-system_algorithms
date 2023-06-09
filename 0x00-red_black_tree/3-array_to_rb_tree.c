#include "rb_trees.h"

/**
 * counter - count number of unique numbers
 *
 * @array: array to check
 * @size: size of the array
 * Return: number of unique numbers
 *
 */
size_t counter(const int *array, size_t size)
{
	size_t i, j, ctr;

	for (i = 0; i < size; i++)
	{
		if (i == 0)
			ctr++;
		else
		{
			for (j = 0; j < i; j++)
			{
				if (array[i] == array[j])
					break;
				if (j == (i - 1))
					ctr++;
			}
		}
	}
	return (ctr);
}

/**
 * valid_array - return correct array which contains only unique numbers
 * @array: array to check
 * @new_array: new array to make
 * @size: number of unique numbers in original array
 * Return: Nothing
 */

void valid_array(const int *array, int *new_array, size_t size)
{
	size_t i, j;

	for (i = 0; i < size; i++)
	{
		if (i == 0)
			new_array[i] = array[i];
		else
		{
			for (j = 0; j < i; j++)
			{
				if (array[i] == new_array[j])
					break;
				if (j == (i - 1))
					new_array[i] = array[i];
			}
		}
	}
}

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
	size_t new_size;
	int *new_array;

	if (array == NULL || size == 0)
		return (NULL);
	new_size = counter(array, size);
	new_array = (int *)malloc(new_size * sizeof(int));
	valid_array(array, new_array, new_size);

	for (i = 0; i < size; i++)
		rb_tree_insert(&root, new_array[i]);
	free(new_array);
	return (root);
}
