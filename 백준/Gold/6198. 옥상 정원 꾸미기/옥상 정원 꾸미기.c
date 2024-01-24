#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element{
    int height;
}Element;

typedef struct Stack *StackPointer;
typedef struct Stack{
    Element data;
    StackPointer link;
}Stack;

int top = -1;

void push(StackPointer *stackTop, int height); // 스택에 현재 건물 정보 저장
void pop(StackPointer *stackTop); // 현재 건물(top에 위치한 건물)을 스택에서 삭제
bool canSee(StackPointer stackTop, int height); // 현재 건물이 다음 건물을 내려다 볼 수 있으면 true 반환
bool peek(StackPointer stackTop, Element *item); // top에 위치한 원소를 item에 저장, NULL이면 false 반환

int main()
{
    StackPointer stackTop = NULL;
    Element temp;
    int n, height;
    long long answer = 0; // 빌딩이 내림차순으로 80000개가 있다면, answer의 값은 약 32억(79999+79998+...+1)

    scanf("%d", &n);

    while(n--){
        scanf("%d", &height);

        // 빈 스택이 아니고, 다음에 들어올 건물이 현재 건물보다 클 때 현재 건물 삭제
        while(peek(stackTop, &temp)){
            if(!canSee(stackTop, height))
                pop(&stackTop);
            else
                break;
        }
        
        push(&stackTop, height);

        // top: 현재 스택의 top에 위치한 건물을 내려다볼 수 있는 건문들의 개수
        // 이 위치에서 top은 무조건 0보다 크거나 같음
        answer += top;
    }

    printf("%lld\n", answer);

    return 0;
}

void push(StackPointer *stackTop, int height)
{
    StackPointer newNode;
    newNode = (StackPointer)malloc(sizeof(*newNode));

    newNode->data.height = height;
    newNode->link = *stackTop;

    *stackTop = newNode;

    ++top;
}

void pop(StackPointer *stackTop)
{
    StackPointer temp = *stackTop;

    // 빈 스택일 때
    if(!temp){
        fprintf(stderr, "삭제할 수 없음\n");
        exit(1);
    }
    else{
        *stackTop = temp->link;
        free(temp);

        --top;
    }
}

bool canSee(StackPointer stackTop, int height)
{
    if(stackTop->data.height > height)
        return true;
    else
        return false;
}

bool peek(StackPointer stackTop, Element *item)
{
    if(stackTop == NULL)
        return false;
    else{
        *item = stackTop->data;
        return true;
    }
}