#include "pathfinding.h"

/**
 * dfs - find path by using dfs
 * @vertex: current vertex to traverse
 * @target: target vertex
 * @visited: visited vertex index array
 * @path: queue to queue the vertices
 * Return: 1 if destination found else 0
 */
int dfs(vertex_t const *vertex, vertex_t const *target,
		char *visited, queue_t *path)
{
	char *city;
	edge_t *edge;
	queue_t *queue;

	if (visited[vertex->index])
		return (0);
	printf("Checking %s\n", vertex->content);
	visited[vertex->index] = 1;
	city = strdup(vertex->content);
	if (!city)
		exit(1);
	queue_push_front(path, city);
	if (vertex == target)
		return (1);
	for (edge = vertex->edges; edge; edge = edge->next)
	{
		if (dfs(edge->dest, target, visited, path))
			return (1);
	}
	queue = dequeue(path);
	free(queue);
	return (0);
}

/**
 * backtracking_graph - find path to the target vertex from the starting vertex
 *			by using backtracking
 * @graph: pointer to graph
 * @start: pointer to starting vertex
 * @target: pointer to target vertex
 * Return: queue of vertices of paths
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	queue_t *rev = NULL, *path;
	char *visited, *city;

	if (!graph || !start || !target)
		return (NULL);

	setbuf(stdout, NULL);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	path = queue_create();
	if (!visited || !path)
		exit(1);
	if (dfs(start, target, visited, path))
	{
		rev = queue_create();
		if (!rev)
			exit(1);
		for (city = dequeue(path); city; city = dequeue(path))
			if (!queue_push_front(rev, city))
				exit(1);
	}
	queue_delete(path);
	free(visited);
	return (rev);
}
