#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdio.h>

#define SPOT_NAME_LEN 64
#define SPOT_DESC_LEN 128
#define NO_PATH -1

/* 景点链表结点：用于保存景点基本信息并满足“显示景点链表”要求 */
typedef struct SpotNode {
    int id;
    char name[SPOT_NAME_LEN];
    char description[SPOT_DESC_LEN];
    struct SpotNode *next;
} SpotNode;

/* 邻接矩阵图结构 */
typedef struct GraphMatrix {
    int capacity;          /* 当前矩阵容量 */
    int vertex_count;      /* 当前景点数量 */
    int directed;          /* 0 表示无向图，1 表示有向图 */
    int **matrix;          /* 邻接矩阵：NO_PATH 表示不连通，对角线为 0 */
    SpotNode *spots;       /* 景点链表头指针 */
} GraphMatrix;

GraphMatrix *graph_create(int initial_capacity, int directed);
void graph_destroy(GraphMatrix *graph);

int graph_add_spot(GraphMatrix *graph, const char *name, const char *description);
int graph_add_path(GraphMatrix *graph, const char *from_name, const char *to_name, int distance);

int graph_find_spot_index(const GraphMatrix *graph, const char *name);
SpotNode *graph_find_spot(const GraphMatrix *graph, const char *name);

void graph_display_spots(const GraphMatrix *graph);
void graph_display_matrix(const GraphMatrix *graph);
void graph_display(const GraphMatrix *graph);

#endif
