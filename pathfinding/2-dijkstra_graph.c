#include "pathfinding.h"

/**
 * _dijkstra - the rest of function dijkstra_graph
 * @j: last index
 * @queue: pointr to queue to add the node
 * @start: pointer to the starting vertex
 * @verts: pointer to the vertex
 * @from: pointer to indexes array
 * Return: 0 on success, 1 on faillure.
 */
int _dijkstra(ssize_t j, queue_t *queue, vertex_t const *start,
		vertex_t **verts, vertex_t **from)
{
	char *dup = NULL;

	if (j != -1)
	{
		for ( ; j != (ssize_t)start->index; j = from[j]->index)
		{
			dup = strdup(verts[j]->content);
			if (!dup)
			{
				return (1);
			}
			else
				queue_push_front(queue, dup);
		}
	}
	else
	{
		free(queue);
		queue = NULL;
	}
	free(from);
	free(verts);
	return (0);
}

/**
 * dijkstra_graph - find queue using dijkstra
 * @graph: pointer to graph
 * @start: pointer to starting vertex
 * @target: pointer to target vertex
 * Return: on success the queue, otherwise NULL
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	vertex_t *tmp, **from, **verts;
	edge_t *e;
	ssize_t i, d, j = -1;
	queue_t *queue = queue_create();
	int *cmp;

	if (!graph || !start || !target || !queue)
		return (NULL);
	from = calloc(graph->nb_vertices, sizeof(*from));
	cmp = calloc(graph->nb_vertices, sizeof(*cmp));
	verts = calloc(graph->nb_vertices, sizeof(*verts));
	if (!verts || !queue || !cmp || !from)
		return (NULL);
	for (tmp = graph->vertices; tmp; tmp = tmp->next)
		verts[tmp->index] = tmp, cmp[tmp->index] = INT_MAX;
	cmp[start->index] = 0, from[start->index] = NULL;
	while (j != (ssize_t)target->index)
	{
		for (d = INT_MAX, j = -1, i = 0; i < (ssize_t)graph->nb_vertices; i++)
			if (cmp[i] >= 0 && cmp[i] < d)
				d = cmp[i], j = i;
		if (j == -1)
			break;
		printf("Checking %s, distance from %s is %d\n",
			verts[j]->content, start->content, cmp[j]);
		for (e = verts[j]->edges; e; e = e->next)
		{
			if (cmp[j] + e->weight < cmp[e->dest->index] &&
					cmp[e->dest->index] >= 0)
			{
				cmp[e->dest->index] = cmp[j] + e->weight,
				from[e->dest->index] = verts[j];
			}
		}
		cmp[j] = -1;
	}
	free(cmp);
	if (_dijkstra(j, queue, start, verts, from))
		exit(1);
	return (queue);
}
