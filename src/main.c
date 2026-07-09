#include "adj_list_graph.h"
#include "graph_matrix.h"

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

static int run_role_a(void) {
    AdjListGraph listGraph;

    adj_list_create(&listGraph);
    add_sample_spots_to_list(&listGraph);
    add_sample_paths_to_list(&listGraph);

    printf("=== Role A: adjacency list ===\n");
    adj_list_display_spots(&listGraph);
    adj_list_display_graph(&listGraph);
    printf("\n");

    adj_list_destroy(&listGraph);
    return 0;
}

static int run_role_b(void) {
    GraphMatrix *graph = graph_create(4, 0);
    if (graph == NULL) {
        printf("创建图失败：内存不足。\n");
        return 1;
    }

    printf("=== Role B: adjacency matrix ===\n");
    printf("B角色：基于邻接矩阵的景区路径规划系统\n");

    graph_add_spot(graph, "校门", "景区入口");
    graph_add_spot(graph, "湖心亭", "湖边观景点");
    graph_add_spot(graph, "樱花道", "春季赏花路线");
    graph_add_spot(graph, "观景台", "最高观景位置");
    graph_add_spot(graph, "游客中心", "咨询与休息区域");

    graph_add_path(graph, "校门", "湖心亭", 300);
    graph_add_path(graph, "校门", "游客中心", 150);
    graph_add_path(graph, "湖心亭", "樱花道", 220);
    graph_add_path(graph, "樱花道", "观景台", 480);
    graph_add_path(graph, "游客中心", "观景台", 520);
    graph_add_path(graph, "湖心亭", "观景台", 650);

    graph_display_spots(graph);
    graph_display_matrix(graph);
    graph_display(graph);

    graph_destroy(graph);
    return 0;
}

int main(void) {
    if (run_role_a() != 0) {
        return 1;
    }
    if (run_role_b() != 0) {
        return 1;
    }
    return 0;
}
