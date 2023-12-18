#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

void print_huffman_codes(binary_tree_node_t *node, int bit);


/**
 * huffman_codes - Builds the Huffman tree and prints the Huffman codes
 *                 for each symbol
 * @data: Array of characters
 * @freq: Array of frequencies associated with each character
 * @size: Size of the arrays
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;

	if (!data || !freq || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	print_huffman_codes(root, 1);

	return (1);
}



/**
 * print_huffman_codes - Recursively prints the Huffman codes
 *                       for each symbol in the Huffman tree
 * @tree: tree to print
 * @bit: bit to convert a binary
 */
void print_huffman_codes(binary_tree_node_t *tree, int bit)
{
	symbol_t *symbol;

	if (!tree)
		return;
	symbol = tree->data;
	if (symbol->data != -1)
		printf("%c: %s\n", symbol->data, convert_to_bin(bit) + 1);
	else
	{
		print_huffman_codes(tree->left, bit << 1);
		print_huffman_codes(tree->right, (bit << 1) + 1);
	}
	free(symbol);
	free(tree);
}
