#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_CNT 21

int isQueueFull(int n);
void enQueue(int len, int n);
int deQueue(int n);
// int checkQueue(int len, int n);

int *queue;
int rear = 0;
int front = 0;

int main()
{
    char name[MAX_NAME_CNT];
    int cnt[MAX_NAME_CNT] = {0, };
    int n, k, size, len;
    long long pair = 0;

    scanf("%d %d", &n, &k);

    size = k + 2;
    queue = (int *)malloc(sizeof(int) * size);
    
    while(n--){
        scanf("%s", name);

        // 큐가 가득 찬 이후, 이름의 길이가 같은 쌍 찾기
        if(isQueueFull(size)){
            len = deQueue(size);
            pair += --cnt[len];
        }

        len = strlen(name);
        enQueue(len, size);
        ++cnt[len];
    }

    // 큐에 남은 이름들의 길이 비교
    while(front != rear){
        len = deQueue(size);
        pair += --cnt[len];

    }

    printf("%lld\n", pair);

    return 0;
}

int isQueueFull(int n)
{
    return front == (rear + 1) % n;
}

void enQueue(int len, int n)
{
    rear = (1 + rear) % n;
    queue[rear] = len;
}

int deQueue(int n)
{
    front = (1 + front) % n;
    return queue[front];
}

int checkQueue(int len, int n)
{
    int temp = (front + 1) % n;
    int pair = 0;

    while((temp + 1) % n != front && queue[temp] != -1){
        if(queue[temp] == len)
            ++pair;

        temp = (temp + 1) % n;
    }

    return pair;
}