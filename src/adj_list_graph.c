#include "adj_list_graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void copy_name(char *target, const char *source) {
    strncpy(target, source, MAX_SCENIC_NAME - 1);
    target[MAX_SCENIC_NAME - 1] = '\0';
}

static int find_spot(const AdjListGraph *graph, const char *name) {
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (strcmp(graph->vertices[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

static AdjListEdge *find_edge(AdjListVertex *vertex, int to) {
    for (AdjListEdge *edge = vertex->firstEdge; edge != NULL; edge = edge->next) {
        if (edge->to == to) {
            return edge;
        }
    }
    return NULL;
}

static int insert_edge(AdjListVertex *vertex, int to, int distance) {
    AdjListEdge *edge = (AdjListEdge *)malloc(sizeof(AdjListEdge));
    if (edge == NULL) {
        return 0;
    }

    edge->to = to;
    edge->distance = distance;
    edge->next = vertex->firstEdge;
    vertex->firstEdge = edge;
    return 1;
}

void adj_list_create(AdjListGraph *graph) {
    if (graph == NULL) {
        return;
    }

    graph->vertexCount = 0;
    graph->edgeCount = 0;
    for (int i = 0; i < MAX_SCENIC_SPOTS; ++i) {
        graph->vertices[i].name[0] = '\0';
        graph->vertices[i].firstEdge = NULL;
    }
}

void adj_list_destroy(AdjListGraph *graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->vertexCount; ++i) {
        AdjListEdge *edge = graph->vertices[i].firstEdge;
        while (edge != NULL) {
            AdjListEdge *next = edge->next;
            free(edge);
            edge = next;
        }
        graph->vertices[i].firstEdge = NULL;
    }
    graph->vertexCount = 0;
    graph->edgeCount = 0;
}

int adj_list_add_spot(AdjListGraph *graph, const char *name) {
    if (graph == NULL || name == NULL || name[0] == '\0') {
        return -1;
    }

    int existing = find_spot(graph, name);
    if (existing >= 0) {
        return existing;
    }

    if (graph->vertexCount >= MAX_SCENIC_SPOTS) {
        return -1;
    }

    int index = graph->vertexCount++;
    copy_name(graph->vertices[index].name, name);
    graph->vertices[index].firstEdge = NULL;
    return index;
}

int adj_list_add_path(AdjListGraph *graph, const char *from, const char *to, int distance) {
    if (graph == NULL || from == NULL || to == NULL || distance <= 0) {
        return 0;
    }

    int fromIndex = find_spot(graph, from);
    int toIndex = find_spot(graph, to);
    if (fromIndex < 0 || toIndex < 0 || fromIndex == toIndex) {
        return 0;
    }

    AdjListEdge *forward = find_edge(&graph->vertices[fromIndex], toIndex);
    AdjListEdge *backward = find_edge(&graph->vertices[toIndex], fromIndex);
    if (forward != NULL && backward != NULL) {
        forward->distance = distance;
        backward->distance = distance;
        return 1;
    }

    if (forward == NULL && !insert_edge(&graph->vertices[fromIndex], toIndex, distance)) {
        return 0;
    }
    if (backward == NULL && !insert_edge(&graph->vertices[toIndex], fromIndex, distance)) {
        return 0;
    }

    if (forward == NULL && backward == NULL) {
        ++graph->edgeCount;
    }
    return 1;
}

void adj_list_display_spots(const AdjListGraph *graph) {
    if (graph == NULL) {
        return;
    }

    printf("Spot linked list: ");
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("[%d]%s", i, graph->vertices[i].name);
        if (i + 1 < graph->vertexCount) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void adj_list_display_graph(const AdjListGraph *graph) {
    if (graph == NULL) {
        return;
    }

    printf("Adjacency list graph: %d spots, %d paths\n", graph->vertexCount, graph->edgeCount);
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%s:", graph->vertices[i].name);
        AdjListEdge *edge = graph->vertices[i].firstEdge;
        if (edge == NULL) {
            printf(" no path");
        }
        while (edge != NULL) {
            printf(" -> %s(%dm)", graph->vertices[edge->to].name, edge->distance);
            edge = edge->next;
        }
        printf("\n");
    }
}
