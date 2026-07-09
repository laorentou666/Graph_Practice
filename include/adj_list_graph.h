#ifndef ADJ_LIST_GRAPH_H
#define ADJ_LIST_GRAPH_H

#include "scenic_graph.h"

typedef struct AdjListEdge {
    int to;
    int distance;
    struct AdjListEdge *next;
} AdjListEdge;

typedef struct {
    char name[MAX_SCENIC_NAME];
    AdjListEdge *firstEdge;
} AdjListVertex;

typedef struct {
    AdjListVertex vertices[MAX_SCENIC_SPOTS];
    int vertexCount;
    int edgeCount;
} AdjListGraph;

void adj_list_create(AdjListGraph *graph);
void adj_list_destroy(AdjListGraph *graph);
int adj_list_add_spot(AdjListGraph *graph, const char *name);
int adj_list_add_path(AdjListGraph *graph, const char *from, const char *to, int distance);
void adj_list_display_graph(const AdjListGraph *graph);
void adj_list_display_spots(const AdjListGraph *graph);

#endif
