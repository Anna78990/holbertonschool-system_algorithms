#include "graphs.h"

/**
 * graph_create - allocate memory of graph_t structure
 *
 * Return: pointer to memory if it succeed, otherwise NULL
 */
graph_t *graph_create(void)
{
	graph_t *graph = malloc(sizeof(*graph));

	if (!graph)
		return (NULL);
	graph->vertices = NULL;
	return (graph);
}
