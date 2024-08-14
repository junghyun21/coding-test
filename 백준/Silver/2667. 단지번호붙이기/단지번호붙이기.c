#include <stdio.h>
#include <stdlib.h>

#define N 25

typedef struct Node{
    int blockCnt;
    struct Node *prev;
    struct Node *next;
} Node;

int countBlocks(int row, int col, int n);
void insertNode(int blockCnt);
void printListCnt();
void printList();

Node *block;
char home[N][N];
char isVisit[N][N];

int main()
{
    int blockCnt;
    int n;
    int i, j;

    scanf("%d", &n);

    // 집의 수 입력 받음
    for(i = 0; i < n; i++){
        scanf("%s", home[i]);
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            blockCnt = 0;
            blockCnt = countBlocks(i, j, n);
            if(blockCnt)
                insertNode(blockCnt);
        }   
    }

    printListCnt();
    printList();

    return 0;
}

int countBlocks(int row, int col, int n)
{
    int cnt = 0;

    if(home[row][col] == '1' && !isVisit[row][col]){
        isVisit[row][col] = 1;
        ++cnt;

        // 왼쪽 방향
        if(row + 1 < n)
            cnt += countBlocks(row + 1, col, n); 
        
        // 오른쪽 방향
        if(row > 0)
            cnt += countBlocks(row - 1, col, n);

        // 아래쪽 방향
        if(col + 1 < n)
            cnt += countBlocks(row, col + 1, n);

        // 위쪽 방향
        if(col > 0)
            cnt += countBlocks(row, col - 1, n);
    }

    return cnt;
}

void insertNode(int blockCnt)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *temp = block;

    newNode->blockCnt = blockCnt;
    newNode->prev = NULL;
    newNode->next = NULL;

    // 첫번째 노드인 경우
    if(temp == NULL){
        block = newNode;
        return;
    }

    // 첫번째 삽입
    if(temp->blockCnt > blockCnt){
        newNode->next = temp;
        newNode->next->prev = newNode;
        block = newNode;
        return;
    }

    // 삽입 위치 찾기
    while(temp->next != NULL && temp->next->blockCnt <= blockCnt){
        temp = temp->next;
    }

    // 중간 삽입
    if(temp->next != NULL){
        newNode->next = temp->next;
        newNode->next->prev = newNode;
    }
    newNode->prev = temp;
    newNode->prev->next = newNode;
}

void printListCnt()
{
    Node *temp = block;
    int cnt = 0;

    while(temp != NULL){
        cnt++;
        temp = temp->next;
    }
    
    printf("%d\n", cnt);
}

void printList()
{
    Node *temp = block;

    while(temp != NULL){
        printf("%d\n", temp->blockCnt);
        temp = temp->next;
    }
}