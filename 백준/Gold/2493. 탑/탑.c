#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Element{
    int tower;
    int height;
}Element;

typedef struct Stack *StackPointer;
typedef struct Stack{
    Element data;
    StackPointer link;
}Stack;

void push(StackPointer *top, int tower, int height);
void pop(StackPointer *top);
int isReceived(StackPointer top, int height);
int peek(StackPointer top, Element *item);

int main()
{
    StackPointer top = NULL;
    Element temp;
    int *tower;
    int n, i, isNull;

    // 탑의 개수 입력
    scanf("%d", &n);

    tower = (int *)malloc((n + 1) * sizeof(int));

    // 탑의 높이 입력받음
    tower[0] = -1;
    for(i = 1; i <= n; i++)
        scanf("%d", &tower[i]);

    // 발사한 레이저 신호를 어느 탑에서 수신하는지 확인
    for(i = 1; i <= n; i++){
        if(!(isNull = peek(top, &temp)) && !isReceived(top, tower[i])){
            pop(&top);
            i--;
            continue;
        }
        
        push(&top, i, tower[i]);

        if(isNull)
            tower[i] = 0;
        else
            tower[i] = temp.tower;
    }

    // 해당 탑에서 발사한 레이저 신호를 수신한 탑 출력
    for(i = 1; i <= n; i++)
        printf("%d ", tower[i]);
    printf("\n");

    return 0;
}

void push(StackPointer *top, int tower, int height)
{
    StackPointer newNode;
    newNode = (StackPointer)malloc(sizeof(*newNode));

    newNode->data.tower = tower;
    newNode->data.height = height;
    newNode->link = *top;

    *top = newNode;
}

void pop(StackPointer *top)
{
    StackPointer temp = *top;

    if(!temp){
        fprintf(stderr, "삭제할 수 있는 노드가 없음\n");
        exit(1);
    }
    else{
        *top = temp->link;
        free(temp);
    }
}

int isReceived(StackPointer top, int height)
{
    if(top->data.height > height)
        return TRUE;
    else
        return FALSE;
}

int peek(StackPointer top, Element *item)
{
    // 스택이 비어있을 때
    if(top == NULL)
        return TRUE;
    else{
        *item = top->data;
        return FALSE;
    }
}