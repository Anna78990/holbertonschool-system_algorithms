#include "graphs.h"

/**
 * graph_add_vertex - allocate memory of graph_t structure
 * @graph: pointer to be added
 * @str: added string
 * Return: pointer to new vertex if it succeed, otherwise NULL
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	int ctr = 0;
	vertex_t *check = graph->vertices;
	vertex_t *new, *swp = NULL;

	if (check != NULL)
	{
		while (check)
		{
			ctr++;
			if (check->content == str)
				return (NULL);
			swp = check;
			check = check->next;
		}
	}
	new = (vertex_t *)malloc(sizeof(vertex_t));
	if (!new)
		return (NULL);
	new->content = strdup(str);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->index = (size_t)ctr;
	new->edges = NULL;
	new->nb_edges = 0;
	new->next = NULL;
	if (swp)
		swp->next = new;
	else
		graph->vertices = new;
	graph->nb_vertices += 1;
	return (new);
}
