#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX (1000 + 1)

int queue[MAX_VERTEX];
int front;
int rear;

int adjMatrix[MAX_VERTEX][MAX_VERTEX];
int visit[MAX_VERTEX];
int N, M; // 정점 및 간선 개수

void inputData();
void bfs(int idx);

void enQueue(int idx);
int deQueue();
int isEmpty();

int main()
{
    int cnt;
    int i;

    inputData();

    for(i = 1, cnt = 0; i <= N; i++){
        if(visit[i]) continue;
        bfs(i);
        ++cnt;
    }

    printf("%d\n", cnt);

    return 0;
}   

void inputData()
{
    int u, v; // 간선의 양 끝점
    int i;

    scanf("%d %d", &N, &M);

    for(i = 0; i < M; i++){
        scanf("%d %d", &u, &v);

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }
}

void bfs(int idx)
{
    int i, j;
    
    front = -1;
    rear = -1;

    for(i = 1; i <= N; i++){
        if(visit[i] || !adjMatrix[idx][i]) continue;

        enQueue(i);
        visit[i] = 1;
    }
    
    while(!isEmpty()){
        i = deQueue();

        for(j = 1; j <= N; j++){
            if(visit[j] || !adjMatrix[i][j]) continue;

            enQueue(j);
            visit[j] = 1;
        }
    }
}

void enQueue(int idx)
{
    if(rear + 1 == MAX_VERTEX){
        fprintf(stderr, "queue is full\n");
        exit(1);
    }

    queue[++rear] = idx;
}

int deQueue()
{
    if(isEmpty()){
        fprintf(stderr, "queue is empty\n");
        exit(1);
    }

    return queue[++front];
}

int isEmpty()
{
    return (front == rear);
}