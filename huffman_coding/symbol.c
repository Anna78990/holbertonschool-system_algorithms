#include <stdlib.h>
#include "huffman.h"

/**
 * symbol_create - Creates a symbol_t data structure
 * @data: The data to be stored in the structure
 * @freq: The associated frequency
 *
 * Return: Pointer to the created structure, or NULL if it fails
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = malloc(sizeof(symbol_t));

	if (symbol == NULL)
		return (NULL);

	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
