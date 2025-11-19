#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// Makes a graph with a certain number of cities 
Graph *create_graph(int numVertices) {
    Graph *graph = malloc(sizeof(Graph));
    if (!graph) {
        printf("Couldn't allocate memory for graph.\n");
        return NULL;
    }

    graph->numVertices = numVertices;

    // Allocate space for the adjacency list (one list per city)
    graph->adjList = malloc(numVertices * sizeof(Edge*));
    if (!graph->adjList) {
        printf("Couldn't allocate memory for adjacency list.\n");
        free(graph);
        return NULL;
    }

    // Initialize all lists to NULL (no edges yet)
    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Adds an edge from "from" → "to" with a certain weight
// Because the graph is undirected, we add it both ways
void add_edge(Graph *graph, int from, int to, int weight) {
    // Make the edge from -> to
    Edge *edge1 = malloc(sizeof(Edge));
    if (!edge1) {
        printf("Couldn't allocate memory for edge.\n");
        return;
    }
    edge1->to = to;
    edge1->weight = weight;
    edge1->next = graph->adjList[from];
    graph->adjList[from] = edge1;

    // Make the edge to from
    Edge *edge2 = malloc(sizeof(Edge));
    if (!edge2) {
        printf("Couldn't allocate memory for edge.\n");
        return;
    }
    edge2->to = from;
    edge2->weight = weight;
    edge2->next = graph->adjList[to];
    graph->adjList[to] = edge2;
}

// Frees all memory used by the graph
void free_graph(Graph *graph) {
    // Free each adjacency list
    for (int i = 0; i < graph->numVertices; i++) {
        Edge *curr = graph->adjList[i];
        while (curr) {
            Edge *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    // Free the array of lists, then the graph itself
    free(graph->adjList);
    free(graph);
}

// Matches a city name to its index in the CityList
// Returns -1 if the city doesn't exist
int find_city_index(CityList *cities, const char *city) {
    for (int i = 0; i < cities->count; i++) {
        if (strcmp(cities->cities[i], city) == 0) {
            return i;
        }
    }
    return -1; // not found
}
