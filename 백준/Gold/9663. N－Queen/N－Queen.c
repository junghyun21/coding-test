#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queen{
    int row;
    int col;
}Queen;

Queen *stack;
int top = -1;
int cnt = 0;

void solveNQueens(int n);
bool isVaild(int n);
bool isFull(int n);
void push(int row, int col, int n);
void pop();

int main()
{
    int n, i;

    scanf("%d", &n);

    stack = (Queen *)malloc(n * sizeof(Queen));

    solveNQueens(n);

    printf("%d\n", cnt);

    return 0;
}

void solveNQueens(int n)
{
    if(isFull(n)){
        ++cnt;
    }
    else{
        int row, col;

        for(row = top + 1, col = 0; col < n; col++){
            push(row, col, n);

            if(isVaild(n))
                solveNQueens(n);
            pop();
        }
    }

    return;
}

bool isVaild(int n)
{
    int i;

    // 같은 열에는 둘 수 없음
    for(i = 0; i < top; i++)
        if(stack[top].col == stack[i].col)
            return false;
    
    // 같은 대각선에는 둘 수 없음
    for(i = 1; i <= top; i++){
        
        if(stack[top].col - i >= 0 && stack[top - i].col == stack[top].col - i)
            return false;
        if(stack[top].col + i < n && stack[top - i].col == stack[top].col + i)
            return false;
    }
    
    return true;
}

bool isFull(int n)
{
    if(top >= n - 1)
        return true;
    else
        return false;
}

bool isEmpty()
{
    if(top == -1)
        return true;
    else
        return false;
}

void push(int row, int col, int n)
{
    if(isFull(n)){
        fprintf(stderr, "stack is full\n");
        exit(1);
    }
    else{
        ++top;
        stack[top].row = row;
        stack[top].col = col;
    }
}

void pop()
{
    if(isEmpty()){
        fprintf(stderr, "stack is empty\n");
        exit(1);
    }
    else{
        --top;
    }
}