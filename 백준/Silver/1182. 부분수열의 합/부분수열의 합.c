// 백트래킹 -> 시간 초과
#include <stdio.h>

#define MAX_NUM 20

int N, S; // 정수 개수 및 합
int input[MAX_NUM]; // 입력받은 정수
int cnt;

void inputData();
void solve(int sum, int idx);

int main()
{
    inputData();
    solve(0, 0);

    if(S == 0) --cnt; // 공집합의 0도 포함됨

    printf("%d\n", cnt);

    return 0;
}

void inputData()
{
    int i;

    scanf("%d %d", &N, &S);

    for(i = 0; i < N; i++){
        scanf("%d", &input[i]);
    }
}

void solve(int sum, int idx)
{
    // N개의 원소를 모두 거쳤는지 확인
    if(idx == N){
        if(sum == S){
            ++cnt;
        }
        return;
    }
    
    solve(sum, idx + 1); // idx에 해당하는 값을 더히지 않은 경우
    solve(sum + input[idx], idx + 1); // idx에 해당하는 값을 더한 경우
}