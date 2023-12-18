#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct
{
    int u;
    int v;
    int w;
} Edge;

void kruskal(Edge *E, int node, int edge);
int find(int u);
void UNION(int u, int v);
void bubblesort(Edge *arr, int a);

int parent[MAX], rank[MAX]; //parent記最上層的點

int main()
{
    int i, node, edge, u, v, w, total;
    Edge *E;
    scanf("%d", &total);
    while (total > 0)
    {
        scanf("%d %d", &node, &edge);
        E = (Edge *)malloc(edge * sizeof(Edge));
        for (i = 0; i < node; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
        for (i = 0; i < edge; i++)
        {
            scanf("%d %d %d", &u, &v, &w);
            E[i].u = u;
            E[i].v = v;
            E[i].w = w;
        }
        kruskal(E, node, edge);
        total--;
    }
    return 0;
}
void kruskal(Edge *E, int node, int edge)
{
    int i, j = 0, x, y, u, v, cost = 0;
    Edge *final = (Edge *)malloc((node - 1) * sizeof(Edge));
    bubblesort(E, edge - 1);
    for (i = 0; i < edge; i++) //輸入的全部的邊都要跑一次
    {
        if (j == node - 1)
            break;
        u = E[i].u;
        v = E[i].v;
        x = find(u);
        y = find(v);
        if (x != y)
        {
            final[j] = E[i];
            UNION(x, y);
            j++;
        }
    }
    for (i = 0; i < node - 1; i++) //n個點會有n-1個邊
        cost += final[i].w;
    printf("%d\n", cost);
}
void bubblesort(Edge *arr, int a) // 照權重排大小
{
    Edge temp;
    for (int i = 1; i <= a; i++)
    {
        for (int j = 0; j <= a - 1; j++)
        {
            if (arr[j].w > arr[j + 1].w)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int find(int u) // 找是否在同一個cycle中
{
    int i = 0, arr[MAX];
    while (u != parent[u])
    {
        arr[i] = u;
        u = parent[u];
        i++;
    }
    i--;
    while (i >= 0)
    {
        parent[arr[i]] = u;
        i--;
    }
    return u;
}
void UNION(int u, int v)
{
    int x, y;
    x = find(u);
    y = find(v);
    if (rank[x] < rank[y])
        parent[x] = y;
    else if (rank[y] < rank[x])
        parent[y] = x;
    else
    {
        parent[x] = y;
        rank[y]++;
    }
}
/*
1
4 4
0 1 3
0 2 3
0 3 1
1 3 1
*/
/*
2
3 3
0 1 1
1 2 2
2 0 3
4 5
0 1 1
1 2 2
2 3 3
3 1 4
0 2 0
*/