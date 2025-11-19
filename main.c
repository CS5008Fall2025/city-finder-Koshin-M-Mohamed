#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "graph.h"
#include "dijkstra.h"

#define MAX_INPUT_LEN 256

// Prints the help menu so I don't have to repeat it everywhere
void print_help() {
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
}

int main(int argc, char *argv[]) {

    // Make sure we get exactly 2 files: city list + distances
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <vertices> <distances>\n", argv[0]);
        return 1;
    }

    // Load the cities first
    CityList cityList = load_cities(argv[1]);

    // Create the graph and fill it with distances
    Graph *graph = create_graph(cityList.count);
    load_distances(argv[2], graph, &cityList);

    // Start screen
    printf("Welcome to the shortest path finder!\n");
    print_help();

    char buffer[MAX_INPUT_LEN];

    while (1) {
        printf("Where do you want to go today? ");

        // Read user input
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        // Strip newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // Empty input → invalid
        if (strlen(buffer) == 0) {
            printf("Invalid Command\n");
            print_help();
            continue;
        }

        // help
        if (strcmp(buffer, "help") == 0) {
            print_help();
            continue;
        }

        // exit
        if (strcmp(buffer, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        // list
        if (strcmp(buffer, "list") == 0) {
            for (int i = 0; i < cityList.count; i++) {
                printf("%s\n", cityList.cities[i]);
            }
            continue;
        }

        // Try to read 2 city names
        char city1[MAX_CITY_NAME], city2[MAX_CITY_NAME];
        if (sscanf(buffer, "%s %s", city1, city2) == 2) {

            int idx1 = find_city_index(&cityList, city1);
            int idx2 = find_city_index(&cityList, city2);

            // One or both cities not found
            if (idx1 == -1 || idx2 == -1) {
                printf("Invalid Command\n");
                print_help();
                continue;
            }

            // Run Dijkstra
            PathResult res = dijkstra(graph, idx1, idx2);

            if (res.distance == -1) {
                printf("Path Not Found...\n");
            } else {
                printf("Path Found...\n");
                for (int i = 0; i < res.pathSize; i++) {
                    printf("\t%s\n", cityList.cities[res.path[i]]);
                }
                printf("Total Distance: %d\n", res.distance);
            }

            free_path_result(&res);
            continue;
        }

        // Anything else is invalid
        printf("Invalid Command\n");
        print_help();
    }
    free_city_list(&cityList);
    free_graph(graph);

    return 0;
}
