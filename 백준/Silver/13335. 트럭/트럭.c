#include <stdio.h>
#include <stdlib.h>

#define NO_TRUCK 0

void enQueue(int weight);
int deQueue();
void enQueueBridge(int weight, int size);
int deQueueBridge(int size);
int isBridgeFull(int size);
int isBridgeEmpty();

// 다리 건너기 전 대기 큐
int *queue;
int front = -1;
int rear = -1;

// 다리 위의 대기 큐
int *bridgeQueue;
int bridgeFront = 0; 
int bridgeRear = 0;

int main()
{
    int n, w, l, i;
    int weight, totalWeight = 0;
    int sec = 0;

    scanf("%d %d %d", &n, &w, &l);
    
    queue = (int *)malloc(sizeof(int) * n); // 선형큐
    bridgeQueue = (int *)malloc(sizeof(int) * (w + 1)); // 원형큐

    while(n--){
        scanf("%d", &weight);
        enQueue(weight);
    }

    i = w;
    while(i--)
        enQueueBridge(NO_TRUCK, w + 1);

    // 트럭이 다리를 건너기 위해 대기하고 있는 큐 내에 트럭이 없을 때까지 반복
    while(front != rear){
        //printf("front: %d, rera: %d\n", front, rear);
        // 다리에 들어가려고 대기하고 있는 트럭 하나 가져옴
        weight = deQueue();
        // 만약 다리가 꽉찬 상태이면 맨 앞의 트럭 하나 빼기
        if(isBridgeFull(w + 1))
            totalWeight -= deQueueBridge(w + 1);

        
        // 가져온 트럭이 다리 큐에 들어갈 수 있는지 확인
        if(totalWeight + weight > l){ 
            --front;
            enQueueBridge(NO_TRUCK, w + 1);
            ++sec;
        }
        else{
            enQueueBridge(weight, w + 1);
            totalWeight += weight;
            ++sec;
        } 
    }

    // 다리 위에 남아있는 트럭들의 이동 시간도 계산
    while(!isBridgeEmpty()){
        deQueueBridge(w + 1);
        ++sec;
    }
    
    printf("%d\n", sec);

    return 0;
}

void enQueue(int weight)
{
    queue[++rear] = weight;
}

int deQueue()
{
    return queue[++front];
}

void enQueueBridge(int weight, int size)
{
    bridgeRear = (1 + bridgeRear) % size;
    bridgeQueue[bridgeRear] = weight;
}

int deQueueBridge(int size)
{
    bridgeFront = (1 + bridgeFront) % size;
    return bridgeQueue[bridgeFront];
}

int isBridgeFull(int size)
{
    return (bridgeRear + 1) % size == bridgeFront;
}

int isBridgeEmpty()
{
    return bridgeFront == bridgeRear;
}