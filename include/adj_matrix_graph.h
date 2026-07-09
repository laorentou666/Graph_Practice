#ifndef ADJ_MATRIX_GRAPH_H
#define ADJ_MATRIX_GRAPH_H

#include "scenic_graph.h"

typedef struct {
    char names[MAX_SCENIC_SPOTS][MAX_SCENIC_NAME];
    int paths[MAX_SCENIC_SPOTS][MAX_SCENIC_SPOTS];
    int vertexCount;
    int edgeCount;
} AdjMatrixGraph;

void adj_matrix_create(AdjMatrixGraph *graph);
int adj_matrix_add_spot(AdjMatrixGraph *graph, const char *name);
int adj_matrix_add_path(AdjMatrixGraph *graph, const char *from, const char *to, int distance);
void adj_matrix_display_graph(const AdjMatrixGraph *graph);
void adj_matrix_display_spots(const AdjMatrixGraph *graph);

#endif
