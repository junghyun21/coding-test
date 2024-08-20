#include <stdio.h>

#define MAX_STAIR 300 + 2

int main()
{
    int oneStep[MAX_STAIR] = {0, }; // 한 계단 밟은 경우
    int twoStep[MAX_STAIR] = {0, }; // 두 계단 밟은 경우
    int score[MAX_STAIR] = {0, }; // 입력 받은 계단의 개수
    int num; // 계단 개수
    int i;

    // 입력
    scanf("%d", &num);
    for(i = 1; i <= num; i++){
        scanf("%d", &score[i]);
    }

    // 메모이제이션(Memoization)
    oneStep[1] = score[1];
    if(num > 1){
        oneStep[2] = oneStep[1] + score[2];
        twoStep[2] = score[2];
    }
    if(num > 2){
        for(i = 3; i <= num; i++){
            oneStep[i] = twoStep[i - 1] + score[i];
            twoStep[i] = ((oneStep[i - 2] > twoStep[i - 2]) ? oneStep[i - 2] : twoStep[i - 2]) + score[i];
        }
    }

    printf("%d\n", (oneStep[num] > twoStep[num]) ? oneStep[num] : twoStep[num]);

    return 0;
}