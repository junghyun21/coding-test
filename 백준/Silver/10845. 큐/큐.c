#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10000
#define MAX_COMMAND_SIZE 6

int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int isQueueFull();
int isQueueEmpty();
void enQueue(int x);
int deQueue();

int main()
{
    int n, x;
    char command[MAX_COMMAND_SIZE];

    scanf("%d", &n);

    while(n--){
        scanf("%s", command);

        if(!strcmp(command, "push")){
            scanf("%d", &x);
            enQueue(x);
        }
        else if(!strcmp(command, "pop")){
            printf("%d\n", deQueue());
        }
        else if(!strcmp(command, "size")){
            printf("%d\n", rear - front);
        }
        else if(!strcmp(command, "empty")){
            printf("%d\n", isQueueEmpty());
        }
        else if(!strcmp(command, "front")){
            if(isQueueEmpty())
                printf("-1\n");
            else
                printf("%d\n", queue[front + 1]);
        }
        else if(!strcmp(command, "back")){
            if(isQueueEmpty())
                printf("-1\n");
            else
                printf("%d\n", queue[rear]);
        }
        else{
            fprintf(stderr, "Invaild command\n");
            exit(1);
        }
    }

    return 0;
}

int isQueueFull()
{
    return rear == MAX_QUEUE_SIZE - 1;
}

int isQueueEmpty()
{
    return front == rear;
}

void enQueue(int x)
{
    if(isQueueFull()){
        fprintf(stderr, "Queue is empty\n");
        exit(1);
    }
    queue[++rear] = x;
}

int deQueue()
{
    if(isQueueEmpty()){
        return -1;
    }
    return queue[++front];
}