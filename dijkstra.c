#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define virt 5

int minDistance(int dist[], int sptSet[]) {
   int min = INT_MAX, min_index;

   for (int v = 0; v < virt; v++)
      if (sptSet[v] == 0 && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}

void printSolution(int dist[]) {
   printf("Vertex \t Distance from Source\n");
   for (int i = 0; i < virt; i++)
      printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(int graph[virt][virt], int src) {
   int dist[virt];     
   int sptSet[virt];   
   for (int i = 0; i < virt; i++)
      dist[i] = INT_MAX, sptSet[i] = 0;

   dist[src] = 0;

   for (int count = 0; count < virt - 1; count++) {
      int u = minDistance(dist, sptSet);

      sptSet[u] = 1;

      for (int v = 0; v < virt
; v++) {
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
      }
   }

   printSolution(dist);
}

int main() {
   int graph[virt][virt];

   printf("Enter the adjacency matrix of the graph:\n");
   for (int i = 0; i < virt; i++) {
      for (int j = 0; j < virt
; j++) {
         scanf("%d", &graph[i][j]);
      }
   }

   int src;
   printf("Enter the source vertex: ");
   scanf("%d", &src);

   dijkstra(graph, src);

   return 0;
}
