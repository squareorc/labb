//18.	Write a Program to implement Dijkstra’s algorithm to find shortest distance between two nodes of a user defined graph. Use Adjacency Matrix/List to represent a graph.

#include <stdio.h>
#include <limits.h>

#define MAX 100

int minDistance(int dist[], int sptSet[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int graph[MAX][MAX], int n, int src, int dest) {
    int dist[MAX];
    int sptSet[MAX];

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        if (u == -1) break;
        sptSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    if (dist[dest] == INT_MAX)
        printf("No path exists between node %d and node %d\n", src, dest);
    else
        printf("Shortest distance between node %d and node %d is %d\n", src, dest, dist[dest]);
}

int main() {
    int n, graph[MAX][MAX];
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    int src, dest;
    printf("Enter source node (0 to %d): ", n-1);
    scanf("%d", &src);
    printf("Enter destination node (0 to %d): ", n-1);
    scanf("%d", &dest);

    dijkstra(graph, n, src, dest);

    return 0;
}