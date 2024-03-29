#include <stdlib.h>
#include <stdio.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);
void _rb_tree_delete(rb_tree_t *tree);

/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	rb_tree_t *root;
	rb_tree_t *node;

	root = NULL;
	node = rb_tree_insert(&root, 43);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 34);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 65);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 13);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 46);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 128);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 256);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 1);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 128);
	printf("Node should be nil -> %p\n", (void *)node);
	node = rb_tree_insert(&root, 624);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 780);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);

	return (0);
}
