#include <stdio.h>
#include <stdlib.h>

#define MAX (1000000 + 1)

typedef struct Node {
    int prevIdx; // 이전역
    int nextIdx; // 다음역
} Node;

Node list[MAX];
int headIdx;
int tailIdx;

void insertNode(int i);
int insertNodeAt(int i, int j, char c);
int deleteNodeAt(int i, char c);

void printList(); // 디버깅

int main()
{
    int i, j; // 고유 번호
    int *res; // 결과 값을 저장할 배열
    int N, M; // 역의 개수와 공사 횟수
    char str[3]; // 명령어 (BN, BP, CP, CN)
    int k;

    scanf("%d %d", &N, &M);

    res = (int *)malloc(sizeof(int) * M);

    // 공사하기 이전의 역 고유 번호 입력 및 연결리스트에 삽입
    while(N--){
        scanf("%d", &i);
        insertNode(i);
    }

    // 공사 내역 입력 받고 결과값 배열에 저장
    for(k = 0; k < M; k++){
        scanf("%s", str);

        if(str[0] == 'B'){
            scanf("%d %d", &i, &j);
            res[k] = insertNodeAt(i, j, str[1]);
        }
        else if(str[0] == 'C'){
            scanf("%d", &i);
            res[k] = deleteNodeAt(i, str[1]);
        }
    }

    // 결과값 출력
    for(k = 0; k < M; k++){
        printf("%d\n", res[k]);
    }

    free(res);

    return 0;
}

void insertNode(int i)
{
    // 빈 리스트인 경우
    if(!headIdx){
        headIdx = i;
        tailIdx = i;
        list[i].prevIdx = i;
        list[i].nextIdx = i;
    }
    // 빈 리스트가 아닌 경우
    else{
        list[tailIdx].nextIdx = i;
        list[headIdx].prevIdx = i;
        list[i].prevIdx = tailIdx;
        list[i].nextIdx = headIdx;

        tailIdx = i;
    }
}

int insertNodeAt(int i, int j, char c)
{
    int res;

    // i 다음에 j를 설립하는 경우
    if(c == 'N'){
        res = list[i].nextIdx;

        list[j].prevIdx = i;
        list[j].nextIdx = list[i].nextIdx;
        list[i].nextIdx = j;
        list[res].prevIdx = j;
    }
    // i 이전에 j를 설립하는 경우
    else if(c == 'P'){
        res = list[i].prevIdx;

        list[j].prevIdx = list[i].prevIdx;
        list[j].nextIdx = i;
        list[i].prevIdx = j;
        list[res].nextIdx = j;
    }

    return res;
}

int deleteNodeAt(int i, char c)
{
    int res;

    // i 다음역을 폐쇄하는 경우
    if(c == 'N'){
        res = list[i].nextIdx;
    }
    // i 이전역을 폐쇄하는 경우
    else if(c == 'P'){
        res = list[i].prevIdx;
    }

    list[list[res].nextIdx].prevIdx = list[res].prevIdx;
    list[list[res].prevIdx].nextIdx = list[res].nextIdx;

    list[res].nextIdx = 0;
    list[res].prevIdx = 0; 

    return res;
}

void printList()
{
    int idx = headIdx;

    do{
        printf("%d(%d, %d) ", idx, list[idx].prevIdx, list[idx].nextIdx);
        idx = list[idx].nextIdx;
    } while(idx != headIdx);

    printf("\n");
}