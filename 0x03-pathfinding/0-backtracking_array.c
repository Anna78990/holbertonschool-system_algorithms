#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
#include "pathfinding.h"

queue_t *createQueue(void)
{
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	queue->front = NULL;
	queue->back = NULL;
	return (queue);
}

void enqueue(queue_t* queue, void* ptr) {
    queue_node_t* newNode = (queue_node_t*)malloc(sizeof(queue_node_t));
    newNode->ptr = ptr;
    newNode->next = NULL;

    if (queue->back == NULL) {
        queue->front = newNode;
	queue->back = newNode;
    } else {
        queue->back->next = newNode;
        newNode->prev = queue->back;
        queue->back = newNode;
    }
}

void* dequeue(queue_t* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    void* ptr = queue->front->ptr;
    queue_node_t* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->back = NULL;
    } else {
        queue->front->prev = NULL;
    }

    free(temp);
    return ptr;
}

int isValidMove(char** map, int rows, int cols, int x, int y) 
{
	return (x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] == '0');
}

//dont forget put the current ptr into ptr
void backtrackingHelper(char** map, int rows, int cols, int cur_x, int cur_y,
		point_t target, int** visited, queue_t* path)
{
	if (visited[cur_x][cur_y] == 1 && (isValidMove(map, rows, cols, cur_x, cur_y + 1)
				+ isValidMove(map, rows, cols, cur_x + 1, cur_y) +
				isValidMove(map, rows, cols, cur_x, cur_y - 1) +
				isValidMove(map, rows, cols, cur_x - 1, cur_y)) < 3)
		path =  dequeue(path);
	else if (visited[cur_x][cur_y] == 0)
	{
		visited[cur_x][cur_y] = 1;
		point_t* point = (point_t*)malloc(sizeof(point_t));
		point->x = cur_x;
		point->y = cur_y;
		enqueue(path, point);
		printf("Checking coordinates [%d, %d]\n", point->x, point->y);
	}
	if (cur_x == target.x && cur_y == target.y)
		return;

	if (isValidMove(map, rows, cols, cur_x, cur_y + 1))
		backtrackingHelper(map, rows, cols, cur_x, cur_y + 1, target, visited, path);
	else if (isValidMove(map, rows, cols, cur_x + 1, cur_y))
		backtrackingHelper(map, rows, cols, cur_x + 1, cur_y, target, visited, path);
	else if (isValidMove(map, rows, cols, cur_x, cur_y - 1))
		backtrackingHelper(map, rows, cols, cur_x, cur_y - 1, target, visited, path);
	else if (isValidMove(map, rows, cols, cur_x - 1, cur_y))
		backtrackingHelper(map, rows, cols, cur_x - 1, cur_y, target, visited, path);
}

queue_t* backtracking_array(char** map, int rows, int cols, point_t const* start, point_t const* target) {
    queue_t* path = createQueue();

    int** visited = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        visited[i] = (int*)calloc(cols, sizeof(int));
    }

    visited[start->x][start->y] = 1;

    point_t current;
    current.x = start->x;
    current.y = start->y;
    point_t* point = (point_t*)malloc(sizeof(point_t));
    point->x = current.x;
    point->y = current.y;
    enqueue(path, point);

    backtrackingHelper(map, rows, cols, start->x, start->y, *target, visited, path);

    // Free the visited array
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);

    return path;
}

