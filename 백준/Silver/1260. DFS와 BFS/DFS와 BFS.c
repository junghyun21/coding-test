// 인접 리스트로 구현
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX (1000 + 1)

typedef struct Node{
    int vertex;
    struct Node *link;
} Node;

typedef struct GraphType{
    int n; // 정점의 개수
    int start; // 탐색을 시작할 정점
    struct Node *listHead[MAX_VERTEX];
} GraphType;
GraphType graph;

int queue[MAX_VERTEX * MAX_VERTEX];
int front = -1;
int rear = -1;

int visit[MAX_VERTEX];
int dfsRes[MAX_VERTEX];
int bfsRes[MAX_VERTEX];

int dfsCnt;
int bfsCnt;

void inputData();
void insertNode(int u, int v); // 오름차순으로 저장
void initVisit();
void dfs(int vertex);
void bfs();
void enQueue(int vertex);
int deQueue();

void error(char *message);

int main()
{
    int i;

    inputData();

    dfs(graph.start);
    initVisit();
    bfs();

    for(i = 0; i < dfsCnt; i++){
        printf("%d ", dfsRes[i]);
    }
    printf("\n");

    for(i = 0; i < bfsCnt; i++){
        printf("%d ", bfsRes[i]);
    }
    printf("\n");

    return 0;
}

void inputData()
{
    int N, M, V; // 정점의 개수, 간선의 개수, 시작할 정점 번호
    int u, v; // 연결된 정점

    scanf("%d %d %d", &N, &M, &V);

    graph.n = N;
    graph.start = V;

    while(M--){
        scanf("%d %d", &u, &v);
        insertNode(u, v);
        insertNode(v, u);
    }
}

void insertNode(int u, int v)
{
    Node *newNode;
    Node *curr, *old;
    int i;

    newNode = (Node *)malloc(sizeof(Node));
    if(!newNode){
        error("can't malloc");
    }
    newNode->vertex = v;
    newNode->link = NULL;

    // 빈 연결 리스트일 때
    curr = graph.listHead[u];
    if(curr == NULL){
        graph.listHead[u] = newNode;
        return;
    }

    while(curr != NULL){
        // 이미 간선 정보가 존재하는 경우: 저장하지 않음
        if(curr->vertex == newNode->vertex){
            free(newNode);
            break;
        }

        // 오름차순으로 연결
        if(curr->vertex > newNode->vertex){
            // 맨 앞에 추가하는 경우
            if(curr == graph.listHead[u]){
                newNode->link = curr;
                graph.listHead[u] = newNode;
            }
            else{
                newNode->link = old->link;
                old->link = newNode;
            }
            
            break;
        } 

        old = curr;
        curr = curr->link;
    }

    // 가장 마지막에 저장되어야하는 경우
    if(curr == NULL){
        old->link = newNode;
    }
}

void initVisit()
{
    int i;

    for(i = 1; i <= graph.n; i++)
        visit[i] = 0;
}

void dfs(int vertex)
{
    Node *temp;

    if(visit[vertex])
        return;

    dfsRes[dfsCnt++] = vertex;
    visit[vertex] = 1;

    temp = graph.listHead[vertex];
    while(temp != NULL){
        dfs(temp->vertex);
        temp = temp->link;
    }

    return;
}

void bfs()
{
    Node *temp;
    int vertex;

    temp = graph.listHead[graph.start];
    while(temp != NULL){
        enQueue(temp->vertex);
        temp = temp->link;
    }

    visit[graph.start] = 1;
    bfsRes[bfsCnt++] = graph.start;

    while(front != rear){
        vertex = deQueue();

        if(visit[vertex]) continue;

        visit[vertex] = 1;
        bfsRes[bfsCnt++] = vertex;

        temp = graph.listHead[vertex];
        while(temp != NULL){
            if(!visit[temp->vertex])
                enQueue(temp->vertex);
            temp = temp->link;
        }

    }
}

void enQueue(int vertex)
{
    if(rear + 1 == MAX_VERTEX * MAX_VERTEX){
        error("queue is full");
    }
    queue[++rear] = vertex;
}

int deQueue()
{
    if(rear == front){
        error("queue is empty");
    }
    return queue[++front];
}

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}