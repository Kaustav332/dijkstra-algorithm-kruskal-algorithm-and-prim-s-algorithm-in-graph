#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 1000

struct Edge {
    int source, destination, weight;
};

struct Graph {
    int num_vertices, num_edges;
    struct Edge edges[MAX_EDGES];
};

int compare_edges(const void* edge1, const void* edge2) {
    struct Edge* e1 = (struct Edge*) edge1;
    struct Edge* e2 = (struct Edge*) edge2;
    return e1->weight - e2->weight;
}

int find_parent(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        return vertex;
    }
    return find_parent(parent, parent[vertex]);
}

void union_sets(int parent[], int x, int y) {
    int parent_x = find_parent(parent, x);
    int parent_y = find_parent(parent, y);
    parent[parent_x] = parent_y;
}

void kruskal(struct Graph* graph) {
    int parent[graph->num_vertices];
    for (int i = 0; i < graph->num_vertices; i++) {
        parent[i] = -1;
    }

    qsort(graph->edges, graph->num_edges, sizeof(struct Edge), compare_edges);

    struct Edge mst[graph->num_vertices - 1];
    int mst_size = 0;

    for (int i = 0; i < graph->num_edges; i++) {
        struct Edge current_edge = graph->edges[i];
        int parent_x = find_parent(parent, current_edge.source);
        int parent_y = find_parent(parent, current_edge.destination);

        if (parent_x != parent_y) {
            mst[mst_size++] = current_edge;
            union_sets(parent, parent_x, parent_y);
        }

        if (mst_size == graph->num_vertices - 1) {
            break;
        }
    }

    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < mst_size; i++) {
        printf("(%d, %d) weight = %d\n", mst[i].source, mst[i].destination, mst[i].weight);
    }
}

int main() {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    printf("Enter number of vertices: ");
    scanf("%d", &graph->num_vertices);

    printf("Enter number of edges: ");
    scanf("%d", &graph->num_edges);

    printf("Enter edges (source, destination, weight):\n");
    for (int i = 0; i < graph->num_edges; i++) {
        scanf("%d%d%d", &graph->edges[i].source, &graph->edges[i].destination, &graph->edges[i].weight);
    }

    kruskal(graph);

    return 0;
}
