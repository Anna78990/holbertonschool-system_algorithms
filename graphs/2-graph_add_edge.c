#include "graphs.h"

/**
 * search_content - search the vertex with given content
 * @root: pointer to top of vertices
 * @content: content to search
 *
 * Return: pointer on successe, NULL On failure
 */
vertex_t *search_content(vertex_t *root, const char *content)
{
	vertex_t *p_v = root;

	while (p_v)
	{
		if (!strcmp(p_v->content, content))
			return (p_v);
		p_v = p_v->next;
	}
	p_v = NULL;
	return (p_v);
}

/**
 * add_edge - add edge
 * @root: pointer to the top of vertices
 * @content: vertice content of the index which accept new edge
 * @dest: new edge to be related with the content
 *
 * Return: 1 on success, or 0 on failure. On failure
 */
int add_edge(vertex_t *root, const char *content, vertex_t *dest)
{
	vertex_t *p_vertex = root;
	edge_t *p_edge, *new;

	new = (edge_t *)malloc(sizeof(edge_t));
	if (!new)
		return (0);
	new->dest = dest;
	new->next = NULL;
	while (p_vertex)
	{
		if (!strcmp(p_vertex->content, content))
		{
			p_edge = p_vertex->edges;
			if (p_edge)
			{
				while (p_edge->next)
					p_edge = p_edge->next;
				p_edge->next = new;
			}
			else
				p_vertex->edges = new;
			p_vertex->nb_edges += 1;
			return (1);
		}
		p_vertex = p_vertex->next;
	}
	return (0);
}

/**
 * graph_add_edge - add edge
 * @graph: pointer to graph
 * @src: vertice content of the index which accept new edge
 * @dest: new edge to be related with the content
 * @type: UNIDIRECTIONAL or BIDIRECTIONAL
 *
 * Return: 1 on success, or 0 on failure. On failure
 */
int graph_add_edge(graph_t *graph, const char *src,
		const char *dest, edge_type_t type)
{
	vertex_t *head, *src_idx, *dest_idx;
	int check;

	if (graph == NULL || src == NULL || dest == NULL)
		return (0);
	head = graph->vertices;
	src_idx = search_content(head, src);
	head = graph->vertices;
	dest_idx = search_content(head, dest);
	if (src_idx == NULL || dest_idx == NULL)
		return (0);
	check = add_edge(head, src, dest_idx);
	if (check == 0)
		return (0);
	if (type == BIDIRECTIONAL)
		return (add_edge(head, dest, src_idx));

	return (1);
}
