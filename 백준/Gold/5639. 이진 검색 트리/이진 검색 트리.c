// 전위 순회 결과를 바탕으로 트리를 생성한 후, 이를 후위 순회하였더니 시간 초과
// 트리를 생성하지 말고 바로 후위 순회 결과를 출력해보자

#include <stdio.h>

#define MAX_NODE 10000

void postorder(int *keys, int start, int end);

int main()
{
    int keys[MAX_NODE], i;

    i = 0;
    while(scanf("%d", &keys[i++]) != EOF);

    i -= 2; // scanf() 실패 시에도 i 값은 증가하기 때문에, i가 마지막 인덱스 값을 가리키기 위해서는 2를 빼줘야함
    postorder(keys, 0, i);

    return 0;
}

void postorder(int *keys, int start, int end)
{
    if(start <= end){
        int x, i;

        i = start + 1;
        while(i <= end){
            if(keys[start] < keys[i])
                break;
            i++;
        }
        x = --i; // 왼쪽 서브트리가 끝나는 지점 (오른쪽 서브트리가 시작하는 지점이면, 존재하지 않는 인덱스일 수도 있음)

        postorder(keys, start + 1, x); // 왼쪽 서브트리
        postorder(keys, x + 1, end); // 오른쪽 서브트리
        printf("%d\n",keys[start]); // 루트
    }
        
    return;
}