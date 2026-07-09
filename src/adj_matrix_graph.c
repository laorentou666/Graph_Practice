#include "adj_matrix_graph.h"

#include <stdio.h>
#include <string.h>

static void copy_name(char *target, const char *source) {
    strncpy(target, source, MAX_SCENIC_NAME - 1);
    target[MAX_SCENIC_NAME - 1] = '\0';
}

static int find_spot(const AdjMatrixGraph *graph, const char *name) {
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (strcmp(graph->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void adj_matrix_create(AdjMatrixGraph *graph) {
    if (graph == NULL) {
        return;
    }

    graph->vertexCount = 0;
    graph->edgeCount = 0;
    for (int i = 0; i < MAX_SCENIC_SPOTS; ++i) {
        graph->names[i][0] = '\0';
        for (int j = 0; j < MAX_SCENIC_SPOTS; ++j) {
            graph->paths[i][j] = (i == j) ? 0 : GRAPH_NO_PATH;
        }
    }
}

int adj_matrix_add_spot(AdjMatrixGraph *graph, const char *name) {
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
    copy_name(graph->names[index], name);
    for (int i = 0; i < graph->vertexCount; ++i) {
        graph->paths[index][i] = GRAPH_NO_PATH;
        graph->paths[i][index] = GRAPH_NO_PATH;
    }
    graph->paths[index][index] = 0;
    return index;
}

int adj_matrix_add_path(AdjMatrixGraph *graph, const char *from, const char *to, int distance) {
    if (graph == NULL || from == NULL || to == NULL || distance <= 0) {
        return 0;
    }

    int fromIndex = find_spot(graph, from);
    int toIndex = find_spot(graph, to);
    if (fromIndex < 0 || toIndex < 0 || fromIndex == toIndex) {
        return 0;
    }

    if (graph->paths[fromIndex][toIndex] == GRAPH_NO_PATH) {
        ++graph->edgeCount;
    }
    graph->paths[fromIndex][toIndex] = distance;
    graph->paths[toIndex][fromIndex] = distance;
    return 1;
}

void adj_matrix_display_spots(const AdjMatrixGraph *graph) {
    if (graph == NULL) {
        return;
    }

    printf("Spot linked list: ");
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("[%d]%s", i, graph->names[i]);
        if (i + 1 < graph->vertexCount) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void adj_matrix_display_graph(const AdjMatrixGraph *graph) {
    if (graph == NULL) {
        return;
    }

    printf("Adjacency matrix graph: %d spots, %d paths\n", graph->vertexCount, graph->edgeCount);
    printf("%12s", "");
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%12s", graph->names[i]);
    }
    printf("\n");

    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%12s", graph->names[i]);
        for (int j = 0; j < graph->vertexCount; ++j) {
            if (graph->paths[i][j] == GRAPH_NO_PATH) {
                printf("%12s", "INF");
            } else {
                printf("%12d", graph->paths[i][j]);
            }
        }
        printf("\n");
    }
}
