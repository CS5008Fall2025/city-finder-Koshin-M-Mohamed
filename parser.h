#ifndef PARSER_H
#define PARSER_H

// Forward declare Graph so we can use it without including graph.h
typedef struct Graph Graph;

#define MAX_CITY_NAME 200

// Holds all city names once we load them
typedef struct {
    char **cities;
    int count;
} CityList;

// Load list of cities from a file
CityList load_cities(const char *filename);

// Free memory from CityList
void free_city_list(CityList *list);

// Load distances and fill the graph with edges
void load_distances(const char *filename, Graph *graph, CityList *cities);

#endif