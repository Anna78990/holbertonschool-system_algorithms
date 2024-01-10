#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"

/**
 * backtracking - back track the map
 * @map: Map to backtrack
 * @rows: Size of row
 * @cols: Size of column
 * @target: Target coordinates
 * @x: X of the backtracking coordinates
 * @y: Y of the backtracking coordinates
 * @queue: queue to add the points
 * Return: 1 when the it is bloked, otherwise 0
 */
int backtracking(char **map, int rows, int cols, point_t const *target,
	int x, int y, queue_t *queue)
{
	point_t *point;
	queue_node_t *node;

	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] != '0')
		return (0);
	map[y][x] = '1';
	point = calloc(1, sizeof(*point));
	if (!point)
		exit(1);
	point->x = x;
	point->y = y;
	queue_push_front(queue, point);
	printf("Checking coordinates [%d, %d]\n", x, y);
	if (x == target->x && y == target->y)
		return (1);
	if (backtracking(map, rows, cols, target, x + 1, y, queue) ||
		backtracking(map, rows, cols, target, x, y + 1, queue) ||
		backtracking(map, rows, cols, target, x - 1, y, queue) ||
		backtracking(map, rows, cols, target, x, y - 1, queue))
		return (1);
	node = dequeue(queue);
	free(node);
	return (0);
}

/**
 * backtracking_array - find the path in the following order
 *			<right, down, left, up>
 * @map: map to search
 * @rows: the size of row
 * @cols: the size of column
 * @start: coordinate of the start
 * @target: coordinate of the target
 * Return: queue of coordinates of used path
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target)
{
	char **cpy_map;
	int i;
	point_t *point;
	queue_t *path = queue_create(), *rev = queue_create();

	cpy_map = malloc(rows * sizeof(char *));
	if (!cpy_map)
		exit(1);
	for (i = 0; i < rows; i++)
	{
		cpy_map[i] = malloc((cols + 1) * sizeof(char));
		if (!cpy_map[i])
			exit(1);
		strcpy(cpy_map[i], map[i]);
	}
	if (backtracking(cpy_map, rows, cols, target, start->x, start->y, path))
	{
		while ((point = dequeue(path)))
			queue_push_front(rev, point);
		free(path);
	}
	else
	{
		free(path);
		free(rev);
		rev = NULL;
	}
	for (i = 0; i < rows; i++)
		free(cpy_map[i]);
	free(cpy_map);
	return (rev);
}
