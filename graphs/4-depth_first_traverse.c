#include "graphs.h"

/**
 * depth_first_search - traverse graph
 * @vertex: pointer vertex node
 * @visited: array to search if it is visited or not
 * @action: pointer to function
 * @depth: current depth
 * @max_depth: max depth
 */

void depth_first_search(vertex_t *vertex, int *visited,
		void (*action)(const vertex_t *vertex, size_t depth), size_t depth,
		size_t *max_depth)
{
	edge_t *e;

	if (!vertex || visited[vertex->index] == 1)
		return;
	visited[vertex->index] = 1;
	action(vertex, depth);
	if (depth > *max_depth)
		*max_depth = depth;
	depth++;
	for (e = vertex->edges; e; e = e->next)
		depth_first_search(e->dest, visited, action, depth, max_depth);
}

/**
 * depth_first_traverse - free the graph memories
 * @graph: pointer to graph
 * @action: pointer to function to use
 *          v: pointer to vertex
 *          depth: depth of vertex
 *
 * Return: maximum of depth, 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t depth_max;

	if (!graph || !action || !graph->nb_vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (0);
	depth_max = 0;
	depth_first_search(graph->vertices, visited, action, 0, &depth_max);
	free(visited);
	return (depth_max);
}
