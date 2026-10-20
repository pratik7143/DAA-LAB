#include <stdio.h>
#define V 5
#define INF 9999
int minDistance(int dist[], int visited[]){
    int min = INF;
    int index = -1;
    for (int i = 0; i < V; i++)
    {
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}
void dijkstra(int graph[V][V], int source)
{
    int dist[V];
    int visited[V] = {0};
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[source] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        int u = minDistance(dist, visited);
        if (u == -1)
            break;
        visited[u] = 1;
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Vertex\tDistance from A\n");
    for (int i = 0; i < V; i++)
        printf("%c\t%d\n", 'A' + i, dist[i]);
}
int main()
{
    // A=0, B=1, C=2, D=3, E=4
    int graph[V][V] =
    {
        // A  B   C  D  E
        { 0, 10,  5, 0, 0 },  // A
        { 0,  0,  0, 1, 0 },  // B
        { 0,  3,  0, 9, 2 },  // C
        { 0,  0,  0, 0, 0 },  // D
        { 2,  0,  0, 6, 0 }   // E
    };
    dijkstra(graph, 0);   // A is the source
    return 0;
}
