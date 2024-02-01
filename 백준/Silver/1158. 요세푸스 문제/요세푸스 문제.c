#include <stdio.h>
#include <stdlib.h>

int isQueueEmpty();
void enQueue(int num, int size);
int deQueue(int size); 

int *queue;
int front = -1;
int rear = -1;

int main()
{
    int i, n, k, num, size;

    scanf("%d %d", &n, &k);

    size = n + 1;
    queue = (int *)malloc(sizeof(int) * (size));

    // 1 ~ n까지 원소 삽입
    for(i = 0; i < n; i++)
        enQueue(i + 1, size);

    // 순열의 원소 순서대로 출력
    printf("<");
    while(!isQueueEmpty()){
        // 앞에 위치한 원소를 맨 뒤로 보냄
        for(i = 1; i < k; i++)
            enQueue(deQueue(size), size); 

        // k번째 원소 출력
        num = deQueue(size);

        if(isQueueEmpty())
            break;
        else
            printf("%d, ", num);
    }
    printf("%d>\n", num);

    return 0;
}

int isQueueEmpty()
{
    return front == rear;
}

void enQueue(int num, int size)
{
    rear = (rear + 1) % size;
    if(rear == front){
        fprintf(stderr, "Queue is full\n");
        exit(1);
    }
    queue[rear] = num;
}

int deQueue(int size)
{
    if(isQueueEmpty()){
        fprintf(stderr, "Queue is empty\n");
        exit(1);
    }
    front = (front + 1) % size;
    return queue[front];
}