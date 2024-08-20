#include <stdio.h>
#include <stdlib.h>

#define MAX_TEST 40 + 1


void fibonacci(int n);

int main()
{
    int dp[MAX_TEST][2]; // 0과 1을 호출한 횟수를 저장할 배열
    int T; // 테스트 케이스 개수
    int n; // 테스트 케이스
    int i;

    scanf("%d", &T);

    dp[0][0] = 1;
    dp[0][1] = 0;
    dp[1][0] = 0;
    dp[1][1] = 1;

    for(i = 2; i < MAX_TEST; i++){
        dp[i][0] = dp[i - 1][0] + dp[i - 2][0];
        dp[i][1] = dp[i - 1][1] + dp[i - 2][1];
    }

    while (T--){
        scanf("%d", &n);
        printf("%d %d\n", dp[n][0], dp[n][1]);
    }
    
    return 0;
}