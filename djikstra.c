#include <stdio.h>
#include <limits.h>
#define V 9
int minDistance(int dist[], int visited[])
{
    int min = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}
void dijkstra(int graph[V][V], int source)
{
    int dist[V];
    int visited[V];
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[source] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);
        if (u == -1)
            break;
        visited[u] = 1;
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Vertex\tShortest Distance from 0\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}
int main()
{
    int graph[V][V] =
    {
        {0,4,0,0,8,0,0,0,0},
        {4,0,8,0,11,0,0,0,0},
        {0,8,0,7,0,0,4,0,2},
        {0,0,7,0,0,0,14,9,0},
        {8,11,0,0,0,1,0,0,7},
        {0,0,0,0,1,0,2,0,6},
        {0,0,4,14,0,2,0,10,0},
        {0,0,0,9,0,0,10,0,0},
        {0,0,2,0,7,6,0,0,0}
    };

    dijkstra(graph, 0);
    return 0;
}