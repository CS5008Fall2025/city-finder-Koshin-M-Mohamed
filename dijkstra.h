#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

// This struct holds the result of running Dijkstra:
// the total distance AND the path we took to get there.
typedef struct {
    int distance;   // total shortest distance
    int *path;      // list of vertex indices in order
    int pathSize;   // how many cities are in the path
} PathResult;

// Runs Dijkstra's algorithm starting at 'start' going to 'end'.
// Returns a PathResult struct with distance + full path.
// If no path exists, distance will be -1.
PathResult dijkstra(Graph *graph, int start, int end);

// Frees the memory used inside a PathResult struct
void free_path_result(PathResult *res);

#endif
