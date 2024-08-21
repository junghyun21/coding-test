#include <stdio.h>

#define MAP_MAX (100+2)

int map[MAP_MAX][MAP_MAX][MAP_MAX];
int M, N, H; // 가로, 세로, 높이
int tomato_cnt;

typedef struct node {
    int h, r, c;
    int day;
}t_node;

int wp, rp;
t_node Queue[MAP_MAX * MAP_MAX * MAP_MAX];

t_node read_queue(void) {
    return Queue[rp++];
}

void write_queue(int h, int r, int c, int day) {
    map[h][r][c] = 1;  // 방문표시
    Queue[wp].h = h;
    Queue[wp].r = r;
    Queue[wp].c = c;
    Queue[wp].day = day;
    wp++;
}

// 앞, 뒤, 왼, 오른, 위, 아래
int dh[] = {0, 0, 0, 0, -1, 1};
int dr[] = {-1, 1, 0, 0, 0, 0};
int dc[] = {0, 0, -1, 1, 0 ,0};

// 익은 토마토(1)를 큐에 넣자
void insert_tomato(void) {
    int i, j, k;
    
    tomato_cnt = 0;  // 익지 않은 토마토의 개수
    for (k = 1; k <= H; k++) {         // 높이
        for (i = 1; i <= N; i++) {     // 세로
            for (j = 1; j <= M; j++) { // 가로
                switch (map[k][i][j]) {
                case 0:
                    tomato_cnt++;
                    break;
                case 1:
                    write_queue(k, i, j, 0);
                    break;
                }                
            }
        }
    }
}

void print_data(void) {
    int i, j, k;
    for (k = 1; k <= H; k++) {         // 높이
        for (i = 1; i <= N; i++) {     // 세로
            for (j = 1; j <= M; j++) { // 가로
                printf("%d ", map[k][i][j]);
            }
            printf("\n");
        }
    }
}

int solve(void) {
    t_node currNode;
    int h, r, c;

    // Queue에 익은 토마토를 넣는 것
    wp = rp = 0;
    insert_tomato();

    // 모든 토마토가 익은 상태이면 0 반환
    if (tomato_cnt == 0) return 0;
    
    // 하나씩 꺼내서 인접을 찾아, 익지않은 토마토이면 Queue에 넣는것
    while(wp != rp){
        currNode = read_queue();

        for (int i = 0; i < 6; i++) {
            h = currNode.h + dh[i];
            r = currNode.r + dr[i];
            c = currNode.c + dc[i];

            if (map[h][r][c] != 0)
                continue;

            write_queue(h, r, c, currNode.day + 1);
        }

    }

    return currNode.day;
}

void init_map(void) {
    int k, i, j;
    for (k = 0; k <= H+1; k++) {         // 높이
        for (i = 0; i <= N+1; i++) {     // 세로
            for (j = 0; j <= M+1; j++) { // 가로
                map[k][i][j] = -1;
            }
        }
    }
}

// 처음부터 다 익어 있다 (0)
// 익지 않고 남은 토마토가 있다 (-1)
// 모두 익는데 X일이 걸린다 (X)
// 1. 익은 토마토   2. 익지 않은 토마토
void input_data(void) {
    int i, j, k;    
    (void)scanf("%d %d %d", &M, &N, &H);
    init_map();
    for (k = 1; k <= H; k++) {         // 높이
        for (i = 1; i <= N; i++) {     // 세로
            for (j = 1; j <= M; j++) { // 가로
                (void)scanf("%d", &map[k][i][j]);
            }
        }
    }
}

// 익지 않은 토마토가 있는지 확인
int check_tomato(){
    int i, j, k;  

    for (k = 1; k <= H; k++) {         // 높이
        for (i = 1; i <= N; i++) {     // 세로
            for (j = 1; j <= M; j++) { // 가로
                if(!map[k][i][j])
                    return -1;
            }
        }
    }

    return 0;
}

int main(void) {
    int day;

    input_data();

    day = solve();

    if(check_tomato() < 0)
        day = -1;

    printf("%d\n", day);

    return 0;
}