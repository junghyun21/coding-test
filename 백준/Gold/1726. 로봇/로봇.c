#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int r; // 행
    int c; // 열
    int d; // 방향
    struct Node *next;
} Node;

typedef struct Queue{
    Node *front;
    Node *rear;
} Queue;

Queue queue;

int **map; // 공장 내 궤도맵
int ***visit; // 최소 방문 횟수
int M, N; // 세로, 가로
int sR, sC, sD; // 출발 지점 및 방향
int eR, eC, eD; // 도착 지점 및 방향

void inputData(); // 데이터 입력
void initMap(); // map 배열 생성 및 초기화
void initVisit(); // visit 배열 생성 및 초기화
void freeAll(); // 메모리 해제
void solve();
int countTurn(int cD, int nD); // 방향 회전 횟수

int isEmpty(); // 큐가 비어있는 상태인지 확인
void enQueue(int r, int c, int d); // 큐 뒤에 노드 추가
Node deQueue(); // 큐 앞의 노드 삭제

void error(char *message); // 에러 메시지 출력 후, 비정상 종료

void printQueue(); // 디버깅
void printVisit(); // 디버깅

int main()
{
    int ans;
    int i;

    inputData();
    solve();

    ans = visit[eR][eC][0];
    for(i = 1; i < 5; i++){
        ans = (ans < visit[eR][eC][i]) ? ans : visit[eR][eC][i];
    }
    printf("%d\n", ans);
    freeAll();

    return 0;
}

void inputData()
{
    int i, j;

    // 직사각형의 세로 및 가로 길이
    scanf("%d %d", &M, &N);

    initMap();
    initVisit();

    // 공장 내 궤도 설치 상태
    for(i = 1; i <= M; i++){
        for(j = 1; j <= N; j++){
            scanf("%d", &map[i][j]);
        }
    }

    // 시작 및 도착 지점 정보
    scanf("%d %d %d", &sR, &sC, &sD);
    scanf("%d %d %d", &eR, &eC, &eD);
}

void initMap()
{
    int i, j;

    // 생성
    map = (int **)malloc(sizeof(int *) * (M + 2));
    for(i = 0; i < M + 2; i++){
        map[i] = (int *)malloc(sizeof(int) * (N + 2));
    }

    // map을 1(로봇이 다닐 수 없는 길)로 초기화
    for(i = 0; i < M + 2; i++){
        for(j = 0; j < N + 2; j++){
            map[i][j] = 1;
        }
    }
}

void initVisit()
{
    int i, j, k;

    // 생성
    visit = (int ***)malloc(sizeof(int **) * (M + 2));
    for(i = 0; i < M + 2; i++){
        visit[i] = (int **)malloc(sizeof(int *) * (N + 2));
        for(j = 0; j < N + 2; j++){
            // 0번 인덱스는 사용하지 않음
            // 1(동) 2(서) 3(남) 4(북)
            visit[i][j] = (int *)malloc(sizeof(int) * 5);
        }
    }

    // 초기화
    for(i = 0; i < M + 2; i++){
        for(j = 0; j < N + 2; j++){
            for(k = 0; k < 5; k++){
                visit[i][j][k] = 0x7fffffff;
            }
        }
    }
}

void freeAll()
{
    int i, j;

    // map 초기화
    for(i = 0; i < M + 2; i++){
        free(map[i]);
    }
    free(map);

    // visit 초기화
    for(i = 0; i < M + 2; i++){
        for(j = 0; j < N + 2; j++){
            free(visit[i][j]);
        }
        free(visit[i]);
    }
    free(visit);
}

void solve()
{
    Node currNode; // 읽어온 노드
    int cR, cC, cD; // 현재 읽어온 노드의 행, 열, 방향
    int nR, nC, nD; // 이동할 공간(새로 추가할 노드)의 행, 열, 방향
    int tR, tC, tD; // 임시로 저장한 행, 열, 방향
    int cnt; // 이동할 공간에 도착했을 때 총 움직인 횟수
    int turnCnt; // 회전 횟수
    int i, j;

    // 동(1), 서(2), 남(3), 북(4)
    int dr[] = {0, 0, 0, 1, -1};
    int dc[] = {0, 1, -1, 0, 0};

    // 시작 지점과 종료 지점이 동일한 경우
    if(sR == eR && sC == eC){
        visit[eR][eC][eD] = countTurn(sD, eD);
        return;
    }

    // 시작 지점을 큐에 넣음
    enQueue(sR, sC, sD);
    visit[sR][sC][sD] = 0;

    while(!isEmpty()){
        //printVisit();
        //printQueue();
        currNode = deQueue();
        cR = currNode.r;
        cC = currNode.c;
        cD = currNode.d;

        for(nD = 1; nD < 5; nD++){
            // 이동 횟수 카운트
            cnt = visit[cR][cC][cD] + countTurn(cD, nD) + 1;
            
            // 직선으로 최대 3칸 이동 가능
            for(i = 1; i <= 3; i++){
                nR = cR + (dr[nD] * i);
                nC = cC + (dc[nD] * i);

                // 로봇이 갈 수 없는 길(1)인 경우: 더 이상 이동하지 않음
                if(map[nR][nC])
                    break;

                // printf("cnt: %d visit[%d][%d]: %d\n", cnt, nR, nC, visit[nR][nC]);

                // 최단거리가 아닌 경우: 이동하지 않음
                if(cnt >= visit[nR][nC][nD])
                    continue;

                // 도착 지점에 도달한 경우: 방향 전환 후, 더 이상 이동하지 않음 (큐 삽입 x)
                if(nR == eR && nC == eC){
                    turnCnt = countTurn(nD, eD);
                    // printf("turnCnt: %d\n", turnCnt);
                    visit[nR][nC][nD] = (cnt + turnCnt < visit[nR][nC][nD]) ? cnt + turnCnt : visit[nR][nC][nD];
                    break;
                }

                visit[nR][nC][nD] = cnt;
                enQueue(nR, nC, nD);
            }
        }
    }   
}

int countTurn(int cD, int nD)
{
    if (cD == nD) return 0;
    if ((cD == 1 && nD == 2) || (cD == 2 && nD == 1)) return 2;
    if ((cD == 3 && nD == 4) || (cD == 4 && nD == 3)) return 2;
    return 1;
}

int isEmpty()
{
    return (queue.front == NULL); 
}

void enQueue(int r, int c, int d)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if(newNode == NULL){
        error("메모리를 할당할 수 없습니다.");
    }

    // 새로 생성한 노드 초기화
    newNode->r = r;
    newNode->c = c;
    newNode->d = d;
    newNode->next = NULL;

    // 큐가 비어있는 상태: front와 rear는 newNode 가리킴
    if(isEmpty()){
        queue.front = newNode;
        queue.rear = newNode;
    }
    // 큐가 비어있지 않은 상태: rear의 다음에 newNode 추가
    else{
        queue.rear->next = newNode;
        queue.rear = newNode;
    }
}

Node deQueue()
{
    Node *deleteNode = queue.front;
    Node temp = *deleteNode;

    // 큐가 비어있는 상태: 에러 처리
    if(isEmpty()){
        error("큐가 비어있습니다.");
    }

    temp = *deleteNode;
    queue.front = queue.front->next;
    // 삭제할 원소가 마지막 원소인 경우: rear가 가리키는 값도 NULL이 됨
    if(queue.front == NULL){
        queue.rear = NULL;
    }
    free(deleteNode);

    return temp;
}

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void printQueue()
{
    Node *temp = queue.front;

    while(temp != NULL){
        printf("(%d %d %d) ", temp->r, temp->c, temp->d);
        temp = temp->next;
    }
    printf("\n");
}

void printVisit()
{
    int i, j;

    for(i = 1; i <= M; i++){
        for(j = 1; j <= N; j++){
            if(visit[i][j][0] == 0x7fffffff)
                printf("%-3d", -1);
            else
                printf("%-3d", visit[i][j][0]);
        }
        printf("\n");
    }
}