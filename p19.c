//19.	Write a Program to implement Kruskal’s algorithm to find minimum spanning tree of a user defined graph. Use Adjacency Matrix/ List to represent a graph.

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void union_set(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int main() {
    int n, adj[MAX][MAX], i, j, k = 0, mincost = 0, edge_count = 0;
    Edge edges[MAX * MAX], mst[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 if no edge):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    // Collect all edges
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (adj[i][j] != 0) {
                edges[k].u = i;
                edges[k].v = j;
                edges[k].w = adj[i][j];
                k++;
            }
        }
    }

    // Sort edges by weight
    for (i = 0; i < k - 1; i++) {
        for (j = 0; j < k - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Initialize parent array
    for (i = 0; i < n; i++)
        parent[i] = i;

    // Kruskal's algorithm
    for (i = 0; i < k && edge_count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int set_u = find(u);
        int set_v = find(v);

        if (set_u != set_v) {
            mst[edge_count++] = edges[i];
            mincost += edges[i].w;
            union_set(set_u, set_v);
        }
    }

    printf("Edges in Minimum Spanning Tree:\n");
    for (i = 0; i < edge_count; i++)
        printf("%d -- %d == %d\n", mst[i].u, mst[i].v, mst[i].w);

    printf("Minimum Cost = %d\n", mincost);

    return 0;
}