#include "nary_trees.h"


void free_child(nary_tree_t *tree, nary_tree_t *root)
{
    nary_tree_t *nxt, *chld;

    if (tree == NULL)
    {
        free(root);
    	return;
    }
    if (tree->children)
        chld = tree->children;
    if (tree->next)
        nxt = tree->next;
    free(tree);
    if (chld)
        free_child(chld, root);
    if (nxt)
        free_child(nxt, root);
}

void nary_tree_delete(nary_tree_t *tree)
{
    free_child(tree, tree);
}
