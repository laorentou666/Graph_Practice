#include "graph_matrix.h"

#include <stdlib.h>
#include <string.h>

static void safe_copy(char *dest, size_t dest_size, const char *src) {
    if (dest_size == 0) {
        return;
    }
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

static int **alloc_matrix(int size) {
    int **matrix = (int **)malloc(sizeof(int *) * size);
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        matrix[i] = (int *)malloc(sizeof(int) * size);
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }

        for (int j = 0; j < size; ++j) {
            matrix[i][j] = (i == j) ? 0 : NO_PATH;
        }
    }

    return matrix;
}

static void free_matrix(int **matrix, int size) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

static int graph_expand(GraphMatrix *graph) {
    int old_capacity = graph->capacity;
    int new_capacity = old_capacity * 2;
    int **new_matrix = alloc_matrix(new_capacity);

    if (new_matrix == NULL) {
        return 0;
    }

    for (int i = 0; i < old_capacity; ++i) {
        for (int j = 0; j < old_capacity; ++j) {
            new_matrix[i][j] = graph->matrix[i][j];
        }
    }

    free_matrix(graph->matrix, old_capacity);
    graph->matrix = new_matrix;
    graph->capacity = new_capacity;
    return 1;
}

GraphMatrix *graph_create(int initial_capacity, int directed) {
    if (initial_capacity <= 0) {
        initial_capacity = 4;
    }

    GraphMatrix *graph = (GraphMatrix *)malloc(sizeof(GraphMatrix));
    if (graph == NULL) {
        return NULL;
    }

    graph->matrix = alloc_matrix(initial_capacity);
    if (graph->matrix == NULL) {
        free(graph);
        return NULL;
    }

    graph->capacity = initial_capacity;
    graph->vertex_count = 0;
    graph->directed = directed ? 1 : 0;
    graph->spots = NULL;
    return graph;
}

void graph_destroy(GraphMatrix *graph) {
    if (graph == NULL) {
        return;
    }

    SpotNode *cur = graph->spots;
    while (cur != NULL) {
        SpotNode *next = cur->next;
        free(cur);
        cur = next;
    }

    free_matrix(graph->matrix, graph->capacity);
    free(graph);
}

int graph_find_spot_index(const GraphMatrix *graph, const char *name) {
    if (graph == NULL || name == NULL) {
        return -1;
    }

    for (SpotNode *cur = graph->spots; cur != NULL; cur = cur->next) {
        if (strcmp(cur->name, name) == 0) {
            return cur->id;
        }
    }
    return -1;
}

SpotNode *graph_find_spot(const GraphMatrix *graph, const char *name) {
    if (graph == NULL || name == NULL) {
        return NULL;
    }

    for (SpotNode *cur = graph->spots; cur != NULL; cur = cur->next) {
        if (strcmp(cur->name, name) == 0) {
            return cur;
        }
    }
    return NULL;
}

int graph_add_spot(GraphMatrix *graph, const char *name, const char *description) {
    if (graph == NULL || name == NULL || name[0] == '\0') {
        return -1;
    }

    int existed = graph_find_spot_index(graph, name);
    if (existed != -1) {
        return existed;
    }

    if (graph->vertex_count >= graph->capacity && !graph_expand(graph)) {
        return -1;
    }

    SpotNode *node = (SpotNode *)malloc(sizeof(SpotNode));
    if (node == NULL) {
        return -1;
    }

    node->id = graph->vertex_count;
    safe_copy(node->name, SPOT_NAME_LEN, name);
    safe_copy(node->description, SPOT_DESC_LEN, description);
    node->next = NULL;

    if (graph->spots == NULL) {
        graph->spots = node;
    } else {
        SpotNode *tail = graph->spots;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }

    graph->vertex_count++;
    return node->id;
}

int graph_add_path(GraphMatrix *graph, const char *from_name, const char *to_name, int distance) {
    if (graph == NULL || distance <= 0) {
        return 0;
    }

    int from = graph_find_spot_index(graph, from_name);
    int to = graph_find_spot_index(graph, to_name);
    if (from == -1 || to == -1) {
        return 0;
    }

    graph->matrix[from][to] = distance;
    if (!graph->directed) {
        graph->matrix[to][from] = distance;
    }
    return 1;
}

void graph_display_spots(const GraphMatrix *graph) {
    if (graph == NULL) {
        return;
    }

    printf("\n========== 景点链表 ==========" "\n");
    if (graph->spots == NULL) {
        printf("当前没有景点。\n");
        return;
    }

    for (SpotNode *cur = graph->spots; cur != NULL; cur = cur->next) {
        printf("[%d] %s", cur->id, cur->name);
        if (cur->description[0] != '\0') {
            printf(" - %s", cur->description);
        }
        if (cur->next != NULL) {
            printf(" ->\n");
        } else {
            printf(" -> NULL\n");
        }
    }
}

void graph_display_matrix(const GraphMatrix *graph) {
    if (graph == NULL) {
        return;
    }

    printf("\n========== 邻接矩阵 ==========" "\n");
    printf("%-12s", "景点");
    for (SpotNode *cur = graph->spots; cur != NULL; cur = cur->next) {
        printf("%-12s", cur->name);
    }
    printf("\n");

    for (SpotNode *row = graph->spots; row != NULL; row = row->next) {
        printf("%-12s", row->name);
        for (SpotNode *col = graph->spots; col != NULL; col = col->next) {
            int value = graph->matrix[row->id][col->id];
            if (value == NO_PATH) {
                printf("%-12s", "∞");
            } else {
                printf("%-12d", value);
            }
        }
        printf("\n");
    }
}

void graph_display(const GraphMatrix *graph) {
    if (graph == NULL) {
        return;
    }

    printf("\n========== 景区路径图 ==========" "\n");
    printf("图类型：%s\n", graph->directed ? "有向图" : "无向图");
    printf("景点数量：%d\n", graph->vertex_count);

    int has_path = 0;
    for (SpotNode *from = graph->spots; from != NULL; from = from->next) {
        for (SpotNode *to = graph->spots; to != NULL; to = to->next) {
            int distance = graph->matrix[from->id][to->id];
            if (distance > 0) {
                if (!graph->directed && from->id > to->id) {
                    continue;
                }
                printf("%s --(%dm)-- %s\n", from->name, distance, to->name);
                has_path = 1;
            }
        }
    }

    if (!has_path) {
        printf("当前没有路径。\n");
    }
}
