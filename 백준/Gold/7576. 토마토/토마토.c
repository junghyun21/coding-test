#include <stdio.h>
#include <stdlib.h>

#define MAX (1000 + 2)

typedef struct _Item{
    int r;
    int c;
    int day;
} Item;

Item queue[MAX * MAX]; // 익은 토마토를 저장
int front = -1;
int rear = -1;

int M, N; // 가로 세로 높이
int tomato[MAX][MAX];
int unripeTomatoCnt; // 익지 않은 토마토 개수

int dr[] = {0, 0, -1, 1};
int dc[] = {-1, 1, 0, 0};

void initTomato();
int solve();
void insertTomato();
int isEmpty();
int isFull();
void enQueue(Item item);
Item deQueue();

// void printQueue()
// {
//     printf("[front] %d [rear] %d\n", front, rear);
//     for(int i = (front == -1) ? 0 : front; i <= rear; i++){
//         printf("(%d %d %d)\n", queue[i].r, queue[i].c, queue[i].day);
//     }
//     printf("\n");
// }

int main()
{
    int i, j;

    scanf("%d %d", &N, &M);

    initTomato();

    // insert tomato
    for(i = 1; i <= M; i++){
        for(j = 1; j <= N; j++){
            scanf("%d", &tomato[i][j]);
        }
    }

    printf("%d\n", solve());

    return 0;
}

void initTomato()
{
    int i, j;

    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++){
            tomato[i][j] = -1;
        }
    }
}

int solve()
{
    Item currItem;
    Item temp;
    int i;

    // 익은 토마토를 모두 큐에 넣어주기
    insertTomato();
    
    // 저장될 때부터 모든 토마토가 익어있는 상태이면 0 리턴
    if(!unripeTomatoCnt)
        return 0;

    // 큐가 비어있지 않을 동안 진행
    while(!isEmpty()){
        currItem = deQueue();

        temp.day = currItem.day + 1;
        for(i = 0; i < 4; i++){
            temp.r = currItem.r + dr[i];
            temp.c = currItem.c + dc[i];

            // 이미 익지 않은 상태에서만 진행
            if(!tomato[temp.r][temp.c]){
                tomato[temp.r][temp.c] = 1;
                enQueue(temp);
                unripeTomatoCnt--;
            }
        }
    }

    // 토마토가 모두 익지 않으면 -1 리턴
    if(unripeTomatoCnt)
        return -1;

    return currItem.day;
}

void insertTomato()
{
    Item temp;
    int i, j;

    for(i = 1; i <= M; i++){
        for(j = 1; j <= N; j++){
            switch(tomato[i][j]){
                // 토마토가 익지 않은 경우
                case 0:
                    unripeTomatoCnt++;
                    break;
                // 토마토가 익은 경우
                case 1:
                    temp.r = i;
                    temp.c = j;
                    temp.day = 0;
                    enQueue(temp);
                    break;
            }
        }
    }
}

int isEmpty()
{
    return (front == rear);
}  

int isFull()
{
    return (rear == (MAX * MAX) - 1);
}

void enQueue(Item item)
{
    if(isFull()){
        fprintf(stderr, "queue is full!\n");
        exit(1);
    }

    queue[++rear] = item;
}

Item deQueue()
{
    if(isEmpty()){
        fprintf(stderr, "queue is empty!\n");
        exit(1);
    }

    return queue[++front];
}