#include <stdio.h>

#define MAX 8

int N, M; // 1부터 N까지 자연수 중 중복없이 M개를 고른 수열
int input[MAX];
int ans[MAX];

void solve(int idx);

int main()
{
    int temp;

    scanf("%d %d", &N, &M);

    for(int i = 0; i < N; i++){
        scanf("%d", &input[i]);
    }

    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - i - 1; j++){
            if(input[j] == input[j + 1]){
                input[j] = 0;
            }
            else if(input[j] > input[j + 1]){
                temp = input[j];
                input[j] = input[j + 1];
                input[j + 1] = temp;
            }
        }
    }

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

    for(int i = 0; i < N; i++){
        if(!input[i]) continue;
        if(idx > 0 && ans[idx - 1] > input[i]) continue;

        ans[idx] = input[i];
        solve(idx + 1);
    }
}