#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 101

typedef struct
{
    int col;
    int row;
    int value;
} term;
term a[MAX_TERM], b[MAX_TERM], d[MAX_TERM];

void transpose(term b[], term bt[]);
void fasttranspose(term a[], term b[]);
void mmult(term a[], term b[], term d[]);
void storeSum(term d[], int *totald, int row, int column, int *sum);
int COMPARE(int a, int b);

int main()
{
    int m1 = 0, n1 = 0;
    int m2 = 0, n2 = 0;
    int counta = 1, countb = 1;
    int a1[MAX_TERM][MAX_TERM], b1[MAX_TERM][MAX_TERM];
    scanf("%d %d", &m1, &n1);
    for (int i = 0; i < m1; i++) //m1=row
    {
        for (int j = 0; j < n1; j++) //n1=col
        {
            scanf("%d", &a1[i][j]);
            if (a1[i][j] != 0)
            {
                a[counta].row = i;
                a[counta].col = j;
                a[counta].value = a1[i][j];
                counta++;
            }
        }
    }
    scanf("%d %d", &m2, &n2);
    for (int i = 0; i < m2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            scanf("%d", &b1[i][j]);
            if (b1[i][j] != 0)
            {
                b[countb].row = i;
                b[countb].col = j;
                b[countb].value = b1[i][j];
                countb++;
            }
        }
    }
    a[0].row = m1;
    a[0].col = n1;
    a[0].value = counta - 1;
    b[0].row = m2;
    b[0].col = n2;
    b[0].value = countb - 1;
    mmult(a, b, d);
    for (int i = 1; i <= d[0].value; i++)
    {
        printf("%d %d %d\n", d[i].row, d[i].col, d[i].value);
    }
}
void fasttranspose(term a[], term b[])
{
    int i, j, rowTerms[100] = {0}, startingPos[100] = {1};
    if (a[0].col > 0)
    {
        for (i = 0; i <= a[0].value; i++)
            rowTerms[a[i].col]++;
        for (i = 1; i < a[0].col; i++)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        for (i = 0; i <= a[0].value; i++)
        {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}
void mmult(term a[], term b[], term d[])
{
    int i, j, row = a[1].row, column, totald = 0;
    int row_begin = 1, sum = 0;
    term new_b[MAX_TERM];
    fasttranspose(b, new_b);
    a[a[0].value + 1].row = a[0].row;
    new_b[b[0].value + 1].row = b[0].col;
    new_b[b[0].value + 1].col = 0;
    for (i = 1; i <= a[0].value;)
    {
        sum = 0;
        column = new_b[1].row;
        for (j = 1; j <= b[0].value + 1;)
        {
            if (a[i].row != row)
            {
                storeSum(d, &totald, row, column, &sum);
                i = row_begin;
                for (; new_b[j].row == column; j++)
                    ;
                column = new_b[j].row;
            }
            else if (new_b[j].row != column)
            {
                storeSum(d, &totald, row, column, &sum);
                i = row_begin;
                column = new_b[j].row;
            }
            else
            {
                switch (COMPARE(a[i].col, new_b[j].col))
                {
                case 1: //a < b
                    i++;
                    break;
                case -1: //a > b
                    j++;
                    break;
                case 0:
                    sum += (a[i++].value * new_b[j++].value);
                    break;
                }
            }
        }
        for (; a[i].row == row; i++)
            ;
        row_begin = i;
        row = a[i].row;
    }
    d[0].row = a[0].row;
    d[0].col = b[0].col;
    d[0].value = totald;
}
void storeSum(term d[], int *totald, int row, int column, int *sum)
{
    if (*sum)
        if (*totald < MAX_TERM)
        {
            d[++*totald].row = row;
            d[*totald].col = column;
            d[*totald].value = *sum;
            *sum = 0;
        }
}
int COMPARE(int a, int b)
{
    if (a > b)
        return -1;
    else if (a == b)
        return 0;
    else if (a < b)
        return 1;
    else
        return 0;
}
/*
3 3
3 4 0
0 3 2
2 0 4
3 3
0 0 0
0 1 0
0 0 0
*/
/*out put
0 1 4
1 1 3 
*/