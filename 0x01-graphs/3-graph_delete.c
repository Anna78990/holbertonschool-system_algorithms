#include "graphs.h"


/**
 * edge_delete - free the edge memories
 * @edges: pointer to the top of edges
 *
 * Return: always nothing
 */
void edge_delete(edge_t *edges)
{
	edge_t *p_edge = edges, *next;

	while (p_edge)
	{
		next = p_edge->next;
		free(p_edge);
		p_edge = next;
	}
}


/**
 * graph_delete - free the graph memories
 * @graph: pointer to graph
 *
 * Return: always nothing
 */
void graph_delete(graph_t *graph)
{
	vertex_t *p_vertex, *next;

	if (graph)
		p_vertex = graph->vertices;
	else
		return;

	while (p_vertex)
	{
		if (p_vertex->edges)
			edge_delete(p_vertex->edges);
		next = p_vertex->next;
		free(p_vertex->content);
		free(p_vertex);
		p_vertex = next;
	}
	free(graph);
}
