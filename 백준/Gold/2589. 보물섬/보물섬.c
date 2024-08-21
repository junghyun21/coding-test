#include <stdio.h>
#include <stdlib.h>

#define MAX_MAP (50 + 2)

typedef struct _Item{
    int r;
    int c;
} Item;

Item queue[MAX_MAP * MAX_MAP];
int front; 
int rear;

char map[MAX_MAP][MAX_MAP]; // 보물 지도
int distance[MAX_MAP][MAX_MAP]; // 최단 거리
int R, C; // 세로, 가로
int max_time; // 가장 오래 걸리는 시간 

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void input_data(); // 입력 값(map, R, C) 저장
void init_distance(); // distance 내의 요소들을 모두 0으로 초기화
void solve(int r, int c); // 각 요소들을 방문하며 거리 측정 및 max_time 추출
int is_empty(); // 큐가 비어있는지 확인
int is_full(); // 큐가 꽉 차있는지 확인
void enqueue(int r, int c); // 마지막에 값 저장
Item dequeue(); // 가장 먼저 저장된 값 삭제

int main()
{
    input_data();

    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            // 육지인 경우에만 BFS 진행
            if(map[i][j] == 'L'){
                init_distance();
                solve(i, j);
            }
        }
    }

    printf("%d\n", max_time);

    return 0;
}

void input_data()
{
    scanf("%d %d", &R, &C);
    for(int i = 1; i <= R; i++){
        scanf("%s", map[i] + 1);
    }
}

void init_distance()
{
    // distance[i][j] = 0: map[i][j]에 해당하는 값은 방문한 적이 없는 곳
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            distance[i][j] = 0;
        }
    }
}

void solve(int r, int c)
{
    Item curr;
    int new_r, new_c;
    int i;

    front = -1;
    rear = -1;

    // 0은 방문한적이 없음을 나타냄
    // 1로 올려주고 시작 -> 최종값에서 1을 빼줘야함
    enqueue(r, c);
    distance[r][c] = 1;

    while(!is_empty()){
        curr = dequeue();

        for(i = 0; i < 4; i++){
            new_r = curr.r + dr[i];
            new_c = curr.c + dc[i];

            // 육지가 아닌 경우에는 이동 불가
            if(map[new_r][new_c] != 'L')
                continue;

            // 방문한 적이 있는 경우 중 최소값으로 갱신할 수 있는 경우에만 진행
            // -> 이는 현재 루트가 아닌 다른 루트에서 방문한 적이 있는 경우임
            if(distance[new_r][new_c] && distance[new_r][new_c] - 1 <= distance[curr.r][curr.c])
                continue;

            enqueue(new_r, new_c);

            distance[new_r][new_c] = distance[curr.r][curr.c] + 1;
            max_time = (distance[new_r][new_c] > max_time + 1) ? distance[new_r][new_c] - 1 : max_time;
        }
    }
}

int is_empty()
{
    return (front == rear);
}

int is_full()
{
    return (rear == (MAX_MAP * MAX_MAP) - 1);
}

void enqueue(int r, int c)
{
    if(is_full()){
        fprintf(stderr, "queue is full!\n");
        exit(1);
    }

    ++rear;
    queue[rear].r = r;
    queue[rear].c = c;
}

Item dequeue()
{
    if(is_empty()){
        fprintf(stderr, "queue is empty!\n");
        exit(1);
    }

    return queue[++front];
}