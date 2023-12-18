#include <stdio.h>
#define MAX 100

int i = 0;
int arr[100][3] = {0};
int top_s = 0, top_h = 0, leaf = 0;
int high[MAX][3] = {0}, stack[MAX]; //high存高度，stack存路徑
void btree(int node, int deep);
int SIZE(int arr[][3]);

int main()
{
    int c, j = 0;
    while (scanf("%d", &c) != EOF)
    {
        arr[i][j] = c;
        j++;
        if (j == 3)
        {
            j = 0;
            i++;
        }
    }
    if (arr[0][0] == 0)
    {
        printf("Tree is empty\n");
        return 0;
    }
    high[top_h][0] = arr[0][0];
    btree(0, 1);
    if (top_s != i)
        printf("Invalid tree");
    else
        printf("%d\n%d\n", SIZE(high), leaf);
    return 0;
}
void btree(int node, int deep) // 用遞迴找連結，存到arr的陣列變成樹的樣子
{
    int right = 1, left = 1;
    for (int j = 0; j < top_s; j++)
        if (stack[j] == node)
            return;
    stack[top_s++] = node;
    if (arr[node][1])
    {
        high[deep][1] = arr[node][1];
        top_h++;
    }
    if (arr[node][2])
    {
        high[deep][2] = arr[node][2];
        top_h++;
    }
    for (int k = node + 1; k < i; k++)
    {
        if (arr[node][1] && arr[node][1] == arr[k][0])
        {
            btree(k, deep + 1);
            right = 0;
        }
        if (arr[node][2] && arr[node][2] == arr[k][0])
        {
            btree(k, deep + 1);
            left = 0;
        }
    }
    if (arr[node][1] && right)
        leaf++;
    if (arr[node][2] && left)
        leaf++;
}
int SIZE(int arr[][3])
{
    int count = 0;
    for (int n = 0; n < 100; n++)
        if (arr[n][0] || arr[n][1] || arr[n][2])
            count++;
    return count;
}
/*
13 17 11
17 8 0
11 10 2
8 0 3
10 14 0
14 0 6
6 12 0
*/
/*
3 44 0
44 87 9
87 0 36
9 0 4
36 24 92
4 0 85
24 2 0
92 0 59
85 32 100
32 80 0
26 10 32
100 0 12
80 38 73
38 0 89
89 45 54
*/