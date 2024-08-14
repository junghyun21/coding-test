#include <stdio.h>
#include <stdbool.h>

#define N 5
#define TOTAL (N * N)
#define DIAG_N 2
#define BINGO 3

int main()
{
    int idx[TOTAL + 1];
    int call[TOTAL + 1];
    int x[N] = {0, };
    int y[N] = {0, };
    int diag[DIAG_N] = {0, };
    int row;
    int col;
    int bingo;
    int num;
    int i;

    // 빙고 저장: 각 자연수들이 저장된 인덱스 저장
    for(i = 0; i < TOTAL; i++){
        scanf("%d", &num);
        idx[num] = i;
    }

    // 사회자가 숫자 부름
    for(i = 1; i <= TOTAL; i++){
        scanf("%d", &call[i]);
    }

    for(i = 1, bingo = 0; i < TOTAL; i++){
        row = idx[call[i]] / N;
        col = idx[call[i]] % N;

        // 가로 빙고
        if(++x[row] == N)
            ++bingo;

        // 세로 빙고
        if(++y[col] == N)
            ++bingo;

        // 대각선 빙고
        if(row == col && ++diag[0] == N)
            ++bingo;

        if(row + col == N - 1 && ++diag[1] == N)
            ++bingo;

        if(bingo >= BINGO)
            break;
    }

    printf("%d\n", i);

    return 0;
}