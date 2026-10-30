#include<stdio.h>
#include<limits.h>
#include<time.h>
#define INF 9999
void dj(int graph[30][30], int n, int src){
    int dist[30], visited[30];
    for(int i=0;i<n;i++){
        dist[i]=INF;
        visited[i]=0;
    }
    dist[src] = 0;
    for(int count =0;count<n-1;count++){
        int min = INF;
        int u = -1;
        for(int i = 0;i<n;i++){
            if(!visited[i] && dist[i] < min){
                min = dist[i];
                u = i;
            }
        }
        if(u==-1)
        break;
        visited[u] = 1;
        for(int v = 0; v<n;v++){
            if(!visited[v] && graph[u][v]!=0 && dist[u] + graph[u][v]<dist[v]){
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Djikstra Shortest Distances:\n");
    for(int i = 0;i<n;i++){
        printf("%d -> %d = %d\n", src, i, dist[i]);
    }
}
void bf(int graph[30][30], int n, int src){
    int dist[30];
    for(int i = 0;i<n;i++)
        dist[i] = INF;
    dist[src] = 0;
    for(int k = 0;k<n-1;k++){
        for(int u = 0;u<n;u++){
            for(int v = 0;v<n;v++){
                if(graph[u][v]!=0 && dist[u]!=INF && dist[u] + graph[u][v]<dist[v]){
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
    for(int u =0;u<n;u++){
        for(int v = 0;v<n;v++){
            if(graph[u][v]!=0 && dist[u]!=INF && dist[u] + graph[u][v]<dist[v]){
                printf("Negative Weight Cycle Found\n");
                return;
            }
        }
    }
    printf("Bellman-Ford Shortest Distances:\n");
    for(int i =0;i<n;i++){
            printf("%d -> %d = %d\n", src, i, dist[i]);
    }
}
int main(){
    int n,src;
    int graph[30][30];
    printf("Enter the number of vertices: ");
    scanf("%d",&n);
    printf("Enter adjacency Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
     printf("Enter source vertex: ");
    scanf("%d", &src);
    clock_t start, end;
    double dijkstraTime, bellmanTime;
    //Djikstra Time
    start = clock();
    dj(graph, n, src);
    end = clock();
    dijkstraTime =(double)(end - start) / CLOCKS_PER_SEC;
    start = clock();
    bf(graph, n, src);
    end = clock();
    bellmanTime =(double)(end - start) / CLOCKS_PER_SEC;
    printf("Dijkstra Time     = %.6f seconds\n",dijkstraTime);
    printf("Bellman-Ford Time = %.6f seconds\n",bellmanTime);
    return 0;
}