#include <stdio.h>
#include <stdlib.h>

#define MAX_TEST 40 + 1

int dp[MAX_TEST][2]; // 0과 1을 호출한 횟수를 저장할 배열

void fibonacci(int n);

int main()
{
    int T; // 테스트 케이스 개수
    int n;

    scanf("%d", &T);

    while (T--){
        scanf("%d", &n);

        fibonacci(n);
        
        // f(n)인 경우
        printf("%d %d\n", dp[n][0], dp[n][1]);
    }
    
    return 0;
}

void fibonacci(int n)
{
    // 0열과 1열 중 하나라도 0이 아닌 경우: 값이 채워진 경우
    if(dp[n][0] || dp[n][1])
        return;

    if(n == 0){
        dp[n][0] = 1;
    }
    else if(n == 1){
        dp[n][1] = 1;
    }
    else{
        fibonacci(n - 1);
        fibonacci(n - 2);

        dp[n][0] = dp[n - 1][0] + dp[n - 2][0];
        dp[n][1] = dp[n - 1][1] + dp[n - 2][1];
    }

    return;
}