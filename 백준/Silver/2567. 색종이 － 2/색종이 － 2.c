#include <stdio.h>
#include <stdbool.h>

#define MAX 100
#define SIZE 10

int getRound(int row, int col);

bool paper[MAX][MAX];
bool isVisit[MAX][MAX];

int main()
{
    int col[MAX] = {0, }; // 열 (col)
    int row[MAX] = {0, }; // 행 (row)
    int round;
    int num;
    int i, j, k;

    // 색종이 수 입력
    scanf("%d", &num);

    // 색종이 위치 입력
    for(i = 0; i < num; i++){
        scanf("%d %d", &col[i], &row[i]);
    }

    // 색종이가 붙여진 위치를 true로 변경
    for(i = 0; i < num; i++){
        for(j = row[i]; j < SIZE + row[i]; j++){
            for(k = col[i]; k < SIZE + col[i]; k++){
                paper[j][k] = true;
            }
        }
    }
    
    // 둘레 계산
    for(i = 0, round = 0; i < num; i++){
        round += getRound(row[i], col[i]);
    }

    // 둘레 출력
    printf("%d\n", round);

    return 0;
}

int getRound(int row, int col)
{
    int round = 0;

    if(!isVisit[row][col]){
        isVisit[row][col] = true;
        
        // 위쪽 이동
        if(row > 0 && paper[row - 1][col])
            round += getRound(row - 1, col);
        else
            ++round;

        // 왼쪽 이동
        if(col > 0 && paper[row][col - 1])
            round += getRound(row, col - 1);
        else
            ++round;
        
        // 아래쪽 이동
        if(row < MAX - 1 && paper[row + 1][col])
            round += getRound(row + 1, col);
        else
            ++round;

        // 오른쪽 이동
        if(col < MAX - 1 && paper[row][col + 1])
            round += getRound(row, col + 1);
        else
            ++round;

    }

    return round;
}