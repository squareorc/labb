//15.	Write a Program to accept a graph (directed or undirected) from user and represent it with Adjacency Matrix and perform BFS and DFS traversals on it.

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int adj[MAX][MAX], visited[MAX], n;

void createGraph(int directed) {
    int i, j, edges, src, dest;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (source destination):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d%d", &src, &dest);
        adj[src][dest] = 1;
        if (!directed)
            adj[dest][src] = 1;
    }
}

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0, i, v;
    for (i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS Traversal: ");
    while (front < rear) {
        v = queue[front++];
        printf("%d ", v);
        for (i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void dfsUtil(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);
    for (i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i])
            dfsUtil(i);
    }
}

void dfs(int start) {
    int i;
    for (i = 0; i < n; i++)
        visited[i] = 0;
    printf("DFS Traversal: ");
    dfsUtil(start);
    printf("\n");
}

int main() {
    int directed, start;
    printf("Enter 0 for undirected graph, 1 for directed graph: ");
    scanf("%d", &directed);
    createGraph(directed);

    printf("Enter starting vertex for traversals: ");
    scanf("%d", &start);

    bfs(start);
    dfs(start);

    return 0;
}