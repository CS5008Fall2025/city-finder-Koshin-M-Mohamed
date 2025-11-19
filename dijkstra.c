#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dijkstra.h"
#include "graph.h"

// Basic min-distance helper: just finds the unvisited node with the smallest distance.
// I'm not using a fancy priority queue because our graphs aren't huge,
// and this is easier to read/debug.
static int get_min_vertex(int *dist, int *visited, int n) {
    int min = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Builds the actual path by walking backwards through "prev".
// Returns a completely filled PathResult.
static PathResult build_path(int *prev, int start, int end, int distance) {
    PathResult res;
    res.distance = distance;

    // If distance is -1, no path exists
    if (distance == -1) {
        res.path = NULL;
        res.pathSize = 0;
        return res;
    }

    // Worst-case path length is every city
    int *temp = malloc(sizeof(int) * 1000); // Big temporary buffer
    int count = 0;

    int curr = end;
    while (curr != -1) {
        temp[count++] = curr;
        if (curr == start) break;
        curr = prev[curr];
    }

    // Reverse the path into a clean array
    res.pathSize = count;
    res.path = malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++) {
        res.path[i] = temp[count - 1 - i];
    }

    free(temp);
    return res;
}

// Frees the internal path array inside PathResult
void free_path_result(PathResult *res) {
    if (res->path != NULL) {
        free(res->path);
        res->path = NULL;
    }
    res->pathSize = 0;
    res->distance = -1;
}

// Main Dijkstra algorithm.
// This is the straightforward version we learned: keep arrays for dist,
// visited, and prev. Relax edges from the current smallest unvisited node.
PathResult dijkstra(Graph *graph, int start, int end) {
    int n = graph->numVertices;

    int *dist = malloc(sizeof(int) * n);
    int *visited = malloc(sizeof(int) * n);
    int *prev = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;   // Start with no known distance
        visited[i] = 0;      // Haven't visited anything yet
        prev[i] = -1;        // No previous node known
    }

    dist[start] = 0;

    // Main loop
    for (int i = 0; i < n; i++) {
        int u = get_min_vertex(dist, visited, n);
        if (u == -1) break; // No reachable vertices left

        visited[u] = 1;

        // Relax all edges from u
        Edge *edge = graph->adjList[u];
        while (edge != NULL) {
            int v = edge->to;
            int weight = edge->weight;

            if (!visited[v] && dist[u] != INT_MAX &&
                dist[u] + weight < dist[v]) {

                dist[v] = dist[u] + weight;
                prev[v] = u;
            }

            edge = edge->next;
        }
    }

    // If it can't reach 
    int finalDistance = (dist[end] == INT_MAX) ? -1 : dist[end];

    PathResult result = build_path(prev, start, end, finalDistance);

    // Clean up arrays
    free(dist);
    free(visited);
    free(prev);

    return result;
}
