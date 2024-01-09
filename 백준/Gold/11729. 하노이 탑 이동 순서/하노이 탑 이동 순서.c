#include <stdio.h>

void hanoi(int, int, int, int);

int main()
{
    int n;

    scanf("%d", &n);

    printf("%d\n", (1 << n) - 1);

    hanoi(n, 1, 2, 3);

    return 0;
}

void hanoi(int n, int start, int to, int end)
{
    if(n > 0){
        // 1단계: 가장 큰 원판을 제외한 모든 원판 start -> to 이동
        // 이 때 목적지 기둥(end)은 잠시 거쳐가는 경유 기둥(to)이 됨
        hanoi(n - 1, start, end, to);

        // 2단계: 가장 큰 원판 하나 남았을 때, 바로 start -> end 이동
        printf("%d %d\n", start, end);

        // 3단계: 가장 큰 원판을 제외한 모든 원판 to -> end 이동
        // 이 때 시작 기둥(start)은 잠시 거쳐가는 경유 기둥(to)이 됨
        hanoi(n - 1, to, start, end);
    }

    return;
}