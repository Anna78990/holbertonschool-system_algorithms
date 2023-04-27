#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * swap - swap two value
 * @parent : 1st value
 * @val_node : 2sd value
 */
void swap(int *parent, int *val_node)
{
	int tmp;

	tmp = *val_node;
	*val_node = *parent;
	*parent = tmp;
}

/**
 * find_parent - find the parent of the node to insert
 * @tree : tree to search
 * @index : index of the tree
 * @size : size of the tree
 *
 * Return: the parent of the node to insert
 */
binary_tree_node_t *find_parent(binary_tree_node_t  *tree, int index, int size)
{
	binary_tree_node_t  *left, *right;

	if (index == size)
		return (tree);

	if (index > size)
		return (NULL);

	left = find_parent(tree->left, 2 * index + 1, size);
	right = find_parent(tree->right, 2 * index + 2, size);

	if (left)
		return (left);
	else if (right)
		return (right);
	else
		return (NULL);

}

/**
 * insert_node - insert the node
 * @tree : tree into insert the node
 * @data : data of node
 * @size : size
 *
 * Return: tree
 */
binary_tree_node_t *insert_node(binary_tree_node_t *tree,
		void *data, size_t size)
{
	binary_tree_node_t *new;
	binary_tree_node_t *p;

	if (size > 1)
		p = find_parent(tree, 0, (size - 1) / 2);
	else
		p = tree;

	new = binary_tree_node(p, data);
	if (!new)
		return (NULL);
	if (!p->left)
		p->left = new;
	else
		p->right = new;
	return (new);

}


/**
 * heap_insert - insertion of heap
 *
 * @heap: heap to insert
 * @data: data to insert
 *
 * Return: New node
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t  *new;

	if (heap == NULL || data == NULL)
		return (NULL);
	if (!heap->root)
	{
		heap->size += 1;
		new = binary_tree_node(heap->root, data);
		heap->root = new;
		return (new);
	}
	new = insert_node(heap->root, data, heap->size);
	if (!new)
		return (NULL);
	if (new->parent->right == NULL && new->parent->data < new->data)
		swap(new->parent->data, new->data);
	heap->size += 1;
	return (new);
}
