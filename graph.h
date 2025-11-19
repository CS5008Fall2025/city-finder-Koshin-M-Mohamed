#ifndef GRAPH_H
#define GRAPH_H

#include "parser.h"

// One edge in the graph. Basically a linked list node for the adjacency list.
typedef struct Edge {
    int to;            // which city this edge goes to index in the city list
    int weight;        // the distance between the two cities
    struct Edge *next; // next edge in the list
} Edge;

// Main graph structure. Each city has a list of edges connected to it.
typedef struct Graph {
    int numVertices; // total number of cities
    Edge **adjList;  // array of linked lists 
} Graph;

// Makes a graph with a certain number of cities 
Graph *create_graph(int numVertices);

// Add a connection between two cities (undirected, so it goes both ways)
void add_edge(Graph *graph, int from, int to, int weight);

// Free all memory used by the graph
void free_graph(Graph *graph);

// Helper function to find where a city is in the CityList (returns the index or -1)
int find_city_index(CityList *cities, const char *city);

#endif
