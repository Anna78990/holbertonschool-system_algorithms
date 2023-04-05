#include "graphs.h"


int search_array(vertex_t *array, vertex_t *dest)
{
	int i = 0;

	for (; array[i]; i++)
	{
		if (array[i] == dest)
			return (0);
	}
	array[i] = dest;
	return (1);
}

size_t search_deadend(vertex_t *array, edge_t *edge, size_t size,
		void (*action)(const vertex_t *v, size_t depth))
{
	if (edge->next == NULL && search_array(array, edge->dest) == 0)
		return (depth);
	if (search_array(array, edge->dest) == 1)
	{
		traverse_action(edge->dest, depth);
		return (search_deadend(array, edge->dest->edges, depth + 1, &traverse_action));
	}
	if (edge->next != NULL && search_array(array, edge->dest) == 0)
                return (search_deadend(array, edge->next, depth, &traverse_action));
}
/**
 * graph_delete - free the graph memories
 * @graph: pointer to graph
 *
 * Return: always nothing
 */
size_t depth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t **array_dest;
	vertex_t *vertex = graph->vertices, *dest;
	edge_t *edge;
	size_t depth = 0, i = 0, max_depth = 0;

	if (graph->vertices == NULL)
		return (0);
	array_dest = (vertex_t **)malloc(sizeof(vertex_t) * graph->nb_vertices);
	while (vertex)
	{
		if (search_array(*array_dest, vertex) == 1)
			action(vertex, depth);
		if (vertex->edges)
			i = search_deadend(array, vertex->edges, depth + 1, &traverse_action);
		if (i > max_depth)
			max_depth = i;
		vertex = vertex->next;
	}

	free(array_dest);
	return (max_depth);
}
