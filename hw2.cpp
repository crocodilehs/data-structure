#include <iostream>
#define MAX_SIZE 100

using namespace std;

typedef struct {
    int row;
    int col;
    int dir;
} element;
element stack[MAX_SIZE];

typedef struct {
    int vert;
    int horiz;
} offsets;

int top = 0;
void push(element item);
element pop();
void path(int** maze, int mazerow, int mazecol);

int main() {
    int i, j, row, col;
    cin >> row >> col;
    int** maze = (int**)malloc(sizeof(int*) * (row + 2));
    for (i = 0; i < row + 2; i++) {
        maze[i] = (int*)malloc(sizeof(int) * (col + 2));
    }
    for (i = 1; i <= row; i++) {
        for (j = 1; j <= col; j++)
            cin >> maze[i][j];
    }
    for (i = 0; i < row + 2; i++) {
        maze[i][0] = 1;
        maze[i][col + 1] = 1;
    }
    for (j = 0; j < col + 2; j++) {
        maze[0][j] = 1;
        maze[row + 1][j] = 1;
    }
    path(maze, row, col);
    return 0;
}
void push(element item) {
    stack[++top] = item;
}
element pop() {
    return stack[top--];
}
void path(int** maze, int mazerow, int mazecol) {
    int row, col, found = 0, dir, next_row, next_col;
    int exitrow = mazerow, exitcol = mazecol;
    int mark[10][10]={0};
    element position;
    offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                       {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
    mark[1][1] = 1;
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 0;
    while (top > -1 && !found) {
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 8 && !found) {
            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz;
            if (next_row == exitrow && next_col == exitcol) {
                found = 1;
            } else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = next_row;
                col = next_col;
                dir = 0;
            } else {
                dir++;
            }
        }
    }
    if (found) {
        for (int i = 0; i <= top; i++) {
            cout << stack[i].row << " " << stack[i].col << "\n";
        }
        cout << row << " " << col << "\n";
        cout << exitrow << " " << exitcol << "\n";
    }
}
/*
3 3
0 1 1
0 1 1
1 0 0
*/
/*output
1 1
2 1
3 2
3 3
*/
/*
5 5
0 1 0 1 1
1 0 1 0 0
0 1 1 1 1
1 0 1 0 1
1 1 0 1 0
*/
/*output
1 1
2 2
3 1
4 2
5 3
4 4
5 5
*/