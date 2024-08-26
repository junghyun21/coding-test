#include <stdio.h>

#define MAX (7 + 1)

int N, M; // 1부터 N까지 자연수 중 중복없이 M개를 고른 수열
int ans[MAX];

void solve(int idx);

int main()
{
    scanf("%d %d", &N, &M);
    solve(0);
    return 0;
}

void solve(int idx)
{
    if(idx == M){
        for(int i = 0; i < M; i++){
            printf("%d ", ans[i]);
        }
        printf("\n");
        return;
    }

    for(int i = 1; i <= N; i++){
        ans[idx] = i;
        solve(idx + 1);
    }
}