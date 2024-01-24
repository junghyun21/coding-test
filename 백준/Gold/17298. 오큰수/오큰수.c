#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Element{
    int idx;
    int num;
}Element;

typedef struct Stack{
    Element data;
    struct Stack *link;
}Stack;

void push(Stack **top, int idx, int num);
void pop(Stack **top, Element *item);
int peek(Stack *top, Element *item);

int main()
{
    Stack *top = NULL;
    Element temp;
    int *nge;
    int n, num, i;

    // 수열의 크기 입력 받기
    scanf("%d", &n);
    nge = (int *)malloc(n * sizeof(int));

    // 수열의 원소 입력 받아 오큰수 구하기
    for(i = 0; i < n; i++){
        scanf("%d", &num);

        // 빈 리스트가 아닌 동안 반복 (peek == false은 top이 없는 경우)
        while(peek(top, &temp)){
            // 새로 들어오는 수얼(오른쪽에 있는 수열)이 더 큰 경우
            if(temp.num < num){
                pop(&top, &temp); // 햔제 top에 있는 원소 삭제
                nge[temp.idx] = num; // 해당 원소가 들어온 순서(인덱스)에 맞게 오큰수 저장
            }
            else
                break;
        }

        push(&top, i, num);
    }

    // 스택에 남은 원소들의 오큰수는 모두 -1 (오큰수가 존재하지 않음)
    while(peek(top, &temp)){
        pop(&top, &temp); // 햔제 top에 있는 원소 삭제
        nge[temp.idx] = -1; // 해당 원소가 들어온 순서(인덱스)에 맞게 오큰수 저장
    }

    // 오큰수 출력
    for(i = 0; i < n; i++)
        printf("%d ", nge[i]);
    printf("\n");

    return 0;        
}

// 원소 삽입
void push(Stack **top, int idx, int num)
{
    Stack *newNode;
    newNode = (Stack *)malloc(sizeof(*newNode));

    newNode->data.idx = idx;
    newNode->data.num = num;
    newNode->link = *top;

    *top = newNode;
}

// 원소 삭제
void pop(Stack **top, Element *item)
{
    Stack *temp = *top;

    // 빈 스택일 때
    if(!temp){
        fprintf(stderr, "삭제 불가\n");
        exit(1);
    }
    else{
        *top = temp->link;
        free(temp);
    }
}

// 스택 내 top에 위치한 원소를 item에 저장
// 빈 스택인 경우 false 반환, 그렇지 않은 경우 true 반환
int peek(Stack *top, Element *item)
{
    if(top == NULL)
        return FALSE;
    else
        *item = top->data;

    return TRUE;
}