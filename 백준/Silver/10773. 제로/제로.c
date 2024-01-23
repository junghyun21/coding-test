#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Element{
    int key;
}Element;

Element *stack;
int capacity = 1;
int top = -1;

void push(Element item);
void pop();
int isFull();
int isEmpty();
void stackFull();
void stackEmpty();
void printSum();

int main()
{
    Element item;
    int k, x;

    stack = (Element *)malloc(sizeof(Element));

    scanf("%d", &k);

    while(k--){
        scanf("%d", &x);

        if(x == 0){
            pop();
        }
        else{
            item.key = x;
            push(item);
        }
    }

    printSum();

    return 0;
}

void push(Element item)
{
    if(isFull())
        stackFull();

    stack[++top] = item;
}

void pop()
{
    if(!isEmpty())
        top--;
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

void printSum()
{
    int i, sum = 0;

    for(i = 0; i <= top; i++)
        sum += stack[i].key;

    printf("%d\n", sum);
}