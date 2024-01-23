#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define COMMAND_SIZE 6

typedef struct Element{
    int key;
}Element;

Element *stack;
int capacity = 1;
int top = -1;

void push(Element item);
Element pop();
int isFull();
int isEmpty();
void stackFull();
Element stackEmpty();
void printTop();

int main()
{
    Element item;
    int n, x;
    char command[COMMAND_SIZE];

    stack = (Element *)malloc(sizeof(Element));

    scanf("%d", &n);

    while(n--){
        while(getchar() != '\n');
        scanf("%s", command);

        // push X는 스택에 X를 삽입
        if(!strcmp(command, "push")){
            scanf(" %d", &x);
            item.key = x;
            push(item);
        }
        // top에 위치한 정수 삭제 및 해당 정수 출력, 정수가 없는 경우에는 -1 출력
        else if(!strcmp(command, "pop")){
            item = pop();
            printf("%d\n", item.key);
        }
        // 스택에 들어있는 정수의 개수 출력
        else if(!strcmp(command, "size")){
            printf("%d\n", top + 1);
        }
        // 스택이 비어있으면 1, 아니면 0 출력
        else if(!strcmp(command, "empty")){
            if(isEmpty())
                printf("1\n");
            else
                printf("0\n");
        }
        // 스택의 가장 위에 있는 정수 출력, 정수가 없는 경우에는 -1 출력
        else if(!strcmp(command, "top")){
            if(isEmpty())
                printf("-1\n");
            else
                printf("%d\n", stack[top].key);
        }
        else{
            fprintf(stderr, "잘못된 명령어 입력\n");
            break;
        }
    }

    return 0;
}

void push(Element item)
{
    if(isFull())
        stackFull();
    
    stack[++top] = item;
}

Element pop()
{
    if(isEmpty())
        return stackEmpty();
    else
        return stack[top--];
}

int isFull()
{
    if(top >= capacity - 1)
        return TRUE;
    else    
        return FALSE;
}

int isEmpty()
{
    if(top == -1)
        return TRUE;
    else
        return FALSE;
}

void stackFull()
{
    capacity *= 2;
    stack = realloc(stack, capacity * sizeof(*stack));
}

Element stackEmpty()
{
    Element temp;
    temp.key = -1;
    return temp;
}