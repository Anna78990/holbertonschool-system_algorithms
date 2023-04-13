#include "graphs.h"

/**
 * pop - free the head node of vertex nodes
 * @head: double pointer to head node
 *
 * Return: Nothing
 */
void pop(node_vertex **head)
{
	node_vertex *tmp;

	if (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

/**
 * push - push new node into vertex nodes
 * @head: double pointer to head node
 * @tail: pointer to tail node
 * @vertex: pointer to node to be added
 *
 * Return: new node, NULL on failure
 */
node_vertex *push(node_vertex **head, node_vertex *tail, vertex_t *vertex)
{
	node_vertex *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);
	new->node = vertex;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		tail->next = new;
	return (new);
}

/**
 * breadth_first_search - traverse graph using breath-first algorithm
 * @vertex: pointer vertex node to be visited
 * @array_depth: array of depths of vertecices
 * @action: function pointer to be called for each visited vertex
 *
 * Return: maximum depth reached, 0 on failure
 */
size_t breadth_first_search(vertex_t *vertex, int *array_depth,
		void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth;
	node_vertex *head, *tail;
	edge_t *e;

	depth = 1;
	array_depth[vertex->index] = depth;
	action(vertex, 0);
	head = NULL;
	e = vertex->edges;
	if (!e)
		return (0);
	do {
		if (e)
		{
			if (!array_depth[e->dest->index])
			{
				tail = push(&head, tail, e->dest);
				if (!tail)
					return (0);
				array_depth[tail->node->index] = depth;
			}
			e = e->next;
		}
		else
		{
			depth = array_depth[head->node->index] + 1;
			for (e = head->node->edges; e && array_depth[e->dest->index];
					e = e->next)
				;
			action(head->node, array_depth[head->node->index]);
			pop(&head);
		}
	} while (head);
	depth--;
	return (depth);
}

/**
 * breadth_first_traverse - goes through graph using breadth-first algorithm
 * @graph: pointer to graph to traverse
 * @action: function pointer to be called for each visited vertex
 *	    v: pointer to visited vertex
 *	    depth: depth of v
 *
 * Return: greatest vertex depth, 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	int *array_depth;
	size_t depth;

	if (!graph || !action || !graph->nb_vertices)
		return (0);
	array_depth = calloc(graph->nb_vertices, sizeof(int *));
	if (!array_depth)
		return (0);
	depth = breadth_first_search(graph->vertices, array_depth, action);
	free(array_depth);
	return (depth);
}
