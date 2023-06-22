#include "nary_trees.h"


/**
 * free_child - free tree children recursively
 * @tree: tree to free
 * @root: root of tree
 */
void free_child(nary_tree_t *tree, nary_tree_t *root)
{
	nary_tree_t *nxt = NULL, *chld = NULL;

	if (tree == NULL)
	{
		free(root->content);
		free(root);
		return;
	}
	if (tree->children)
		chld = tree->children;
	if (tree->next)
		nxt = tree->next;
	free(tree->content);
	free(tree);
	if (chld)
		free_child(chld, root);
	if (nxt)
		free_child(nxt, root);
}

/**
 * nary_tree_delete - free entire of given tree
 * @tree: tree to free
 */
void nary_tree_delete(nary_tree_t *tree)
{
	free_child(tree, tree);
}
