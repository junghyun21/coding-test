#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LEN 6

typedef struct QueueNode{
    int x;
    struct QueueNode *link;
}QueueNode;

typedef struct Queue{
    QueueNode *front;
    QueueNode *rear;
    int size;
}Queue;

Queue *queue;

void initQueue(); // 큐 초기화
void push(int x); // 큐의 마지막에 정수 x 삽입
int pop(); // 큐의 맨 앞 정수 삭제 후, 해당 정수 반환
int isEmpty(); // 큐가 비어있으면 1, 그렇지 않으면 0 반환

int main()
{
    int n, x;
    char command[MAX_COMMAND_LEN];

    queue = (Queue *)malloc(sizeof(Queue));
    initQueue();

    scanf("%d", &n);

    while(n--){
        scanf("%s", command);

        if(!strcmp(command, "push")){
            scanf("%d", &x);
            push(x);
            getchar();
        }
        else if(!strcmp(command, "pop")){
            if(isEmpty())
                printf("-1\n");
            else
                printf("%d\n", pop());
        }
        else if(!strcmp(command, "size")){
            printf("%d\n", queue->size);
        }
        else if(!strcmp(command, "empty")){
            printf("%d\n", isEmpty());
        }
        else if(!strcmp(command, "front")){
            if(isEmpty())
                printf("-1\n");
            else
                printf("%d\n", queue->front->x);
        }
        else if(!strcmp(command, "back")){
            if(isEmpty())
                printf("-1\n");
            else
                printf("%d\n", queue->rear->x);
        }
        else{
            fprintf(stderr, "잘못된 입력\n");
            break;
        }
    }

    return 0;
}

void initQueue()
{
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

void push(int x)
{
    QueueNode *newNode;
    newNode = (QueueNode *)malloc(sizeof(*newNode));

    newNode->x = x;
    newNode->link = NULL;

    if(isEmpty()){
        queue->front = newNode;
        queue->rear = newNode;
    }
    else{
        queue->rear->link = newNode;
        queue->rear = newNode;
    }

    queue->size++;
}

// 해당 함수 호출 전에, 큐가 비어있는 상태인지 확인 완료
int pop()
{
    QueueNode *deleteNode = queue->front;
    int deleteX = deleteNode->x;

    queue->front = queue->front->link;
    // 만약 삭제할 원소가 큐에서 남은 마지막 원소라면, rear 값도 조정 필요
    if(queue->front == NULL)
        queue->rear = NULL;
    
    free(deleteNode);

    queue->size--;
    
    return deleteX;
}

int isEmpty()
{
    return (queue->front == NULL);
}