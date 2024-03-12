// 자신의 위치 기준에서 왼쪽에 위치한 사람들 중 자신보다 크거나 같은 사람의 수 구함
#include <stdio.h>

#define MAX_PEOPLE 500000

typedef struct Element{
    int cnt; 
    int height;
}Element;

void push(int height, int cnt);
int peek(Element *item); // 정상적으로 가져왔으면 1, 아니면 0
int pop(Element *item); // 정상적으로 삭제했으면 1, 아니면 0

Element stack[MAX_PEOPLE];
int top = -1;

int main()
{
    Element temp;
    int i, n, height, cnt;
    long long answer = 0;

    scanf("%d", &n);

    while(n--){
        scanf("%d", &height);

        cnt = 1;
        
        // 키가 더 큰 사람이 다음에 서있으면
        // 이 사람 이후의 사람들은 이 전 사람들과 쌍을 이룰 수 없기 때문에 pop
        while(peek(&temp) && temp.height <= height){
            // 왼쪽에 위치한 사람들 중 자신보다 크거나 같은 사람의 개수
            answer += temp.cnt;

            // 만약에 top에 위치한 사람과 동일한 키의 사람이 있다면
            // 새로 들어오는 사람이 이룰 수 있는 쌍의 개수 = top에 위치한 사람보다 크거나 같은 사람 + top에 위치한 사람
            if(temp.height == height)
                cnt += temp.cnt;
            
            // 새로 들어올 사람보다 키가 작거나 같은 사람은 스택에서 삭제
            pop(&temp);
        }

        // 스택에 비어있지 않다면, 새로 들어온 사람의 왼쪽에 위치한 사람 중 가장 작은 사람
        // 즉, 본인 다음으로 큰 사람과의 쌍을 지어줌
        if(peek(&temp))
            ++answer;

        push(height, cnt); 
    }

    printf("%lld\n", answer);

    return 0;
}

void push(int height, int cnt)
{
    stack[++top].height = height;
    stack[top].cnt = cnt;
}

int peek(Element *item)
{
    if(top == -1)
        return 0;
    
    *item = stack[top];
    return 1;
}

int pop(Element *item)
{
    if(top == -1)
        return 0;

    *item = stack[top--];
    return 1;
}