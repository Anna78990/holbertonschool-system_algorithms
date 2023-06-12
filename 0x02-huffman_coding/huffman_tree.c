#include "huffman.h"


binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
    binary_tree_node_t *root;
    heap_t *priority_queue;

    if (data == NULL || freq == NULL || size == 0)
        return (NULL);

    priority_queue = huffman_priority_queue(data, freq, size);
    if (priority_queue == NULL)
        return (NULL);

    while (priority_queue->size > 1)
    {
        if (!huffman_extract_and_insert(priority_queue))
        {
            heap_delete(priority_queue, binary_tree_delete);
            return (NULL);
        }
    }

    root = priority_queue->root;
    free(priority_queue);

    return (root);
}
