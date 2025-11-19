#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "graph.h" 

// Loads all city names from a file 
CityList load_cities(const char *filename) {
    CityList list;
    list.cities = NULL;
    list.count = 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        return list; // returns empty list
    }

    char line[MAX_CITY_NAME];

    // Read each line of the file
    while (fgets(line, sizeof(line), fp)) {
        // Remove the newline at the end
        line[strcspn(line, "\n")] = '\0';

        // Allocate space for one more city
        char **new_array = realloc(list.cities, (list.count + 1) * sizeof(char*));
        if (!new_array) {
            printf("Memory allocation failed while loading cities.\n");
            fclose(fp);
            return list;
        }

        list.cities = new_array;

        // Allocate memory for storing the city name
        list.cities[list.count] = malloc(strlen(line) + 1);
        if (!list.cities[list.count]) {
            printf("Memory allocation failed for city name.\n");
            fclose(fp);
            return list;
        }

        // Copy the city name into the array
        strcpy(list.cities[list.count], line);

        list.count++;
    }

    fclose(fp);
    return list;
}

// Frees all memory used by CityList
void free_city_list(CityList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->cities[i]);
    }
    free(list->cities);

    // Reset values
    list->cities = NULL;
    list->count = 0;
}

// Reads the distances file and adds edges to the graph
void load_distances(const char *filename, Graph *graph, CityList *cities) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening distances file: %s\n", filename);
        return;
    }

    char city1[MAX_CITY_NAME];
    char city2[MAX_CITY_NAME];
    int weight;

    // Each line should look like: cityA cityB distance
    while (fscanf(fp, "%s %s %d", city1, city2, &weight) == 3) {

        // Find the index for each city
        int idx1 = find_city_index(cities, city1);
        int idx2 = find_city_index(cities, city2);

        // If either city doesn't exist, skip the line
        if (idx1 == -1 || idx2 == -1) {
            continue;
        }

        // Add the connection to the graph
        add_edge(graph, idx1, idx2, weight);
    }

    fclose(fp);
}
