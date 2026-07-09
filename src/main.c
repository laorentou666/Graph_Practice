#include "adj_list_graph.h"
#include "adj_matrix_graph.h"

#include <stdio.h>

static void add_sample_spots_to_list(AdjListGraph *graph) {
    adj_list_add_spot(graph, "Entrance");
    adj_list_add_spot(graph, "Lake");
    adj_list_add_spot(graph, "Pavilion");
    adj_list_add_spot(graph, "Garden");
}

static void add_sample_paths_to_list(AdjListGraph *graph) {
    adj_list_add_path(graph, "Entrance", "Lake", 300);
    adj_list_add_path(graph, "Lake", "Pavilion", 180);
    adj_list_add_path(graph, "Pavilion", "Garden", 220);
    adj_list_add_path(graph, "Entrance", "Garden", 450);
}

static void add_sample_spots_to_matrix(AdjMatrixGraph *graph) {
    adj_matrix_add_spot(graph, "Entrance");
    adj_matrix_add_spot(graph, "Lake");
    adj_matrix_add_spot(graph, "Pavilion");
    adj_matrix_add_spot(graph, "Garden");
}

static void add_sample_paths_to_matrix(AdjMatrixGraph *graph) {
    adj_matrix_add_path(graph, "Entrance", "Lake", 300);
    adj_matrix_add_path(graph, "Lake", "Pavilion", 180);
    adj_matrix_add_path(graph, "Pavilion", "Garden", 220);
    adj_matrix_add_path(graph, "Entrance", "Garden", 450);
}

int main(void) {
    AdjListGraph listGraph;
    AdjMatrixGraph matrixGraph;

    adj_list_create(&listGraph);
    add_sample_spots_to_list(&listGraph);
    add_sample_paths_to_list(&listGraph);

    printf("=== Role A: adjacency list ===\n");
    adj_list_display_spots(&listGraph);
    adj_list_display_graph(&listGraph);
    printf("\n");

    adj_matrix_create(&matrixGraph);
    add_sample_spots_to_matrix(&matrixGraph);
    add_sample_paths_to_matrix(&matrixGraph);

    printf("=== Role B: adjacency matrix ===\n");
    adj_matrix_display_spots(&matrixGraph);
    adj_matrix_display_graph(&matrixGraph);

    adj_list_destroy(&listGraph);
    return 0;
}
