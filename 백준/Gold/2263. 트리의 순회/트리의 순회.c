// 전위, 중위, 후위 순회의 특징을 이용하자
// 전위: 루트->왼->오, 중위: 왼->루트->오, 후위: 왼->오->루트
#include <stdio.h>

#define MAX_NODE 100000

void preorder(int, int, int, int);
void searchRoot(int, int *);

int inorder[MAX_NODE];
int postorder[MAX_NODE];

int main()
{
    int i, n;

    // 노드의 개수 입력 받기
    scanf("%d", &n);

    // 중위 순회 입력 받아 저장하기
    for(i = 0; i < n; i++) 
        scanf("%d", &inorder[i]);

    // 후위 순회 입력 받아 저장하기
    for(i = 0; i < n; i++) 
        scanf("%d", &postorder[i]);

    // 중위 순회 배열의 시작/끝 인덱스, 후위 순회 배열의 시작/끝 인덱스
    preorder(0, n - 1, 0, n - 1);
    printf("\n");

    return 0;
}

void preorder(int inStart, int inEnd, int postStart, int postEnd)
{
    if(inStart <= inEnd && postStart <= postEnd){
        int idx, leftsize, rightsize;

        // inorder[idx]: 루트 노드
        searchRoot(postorder[postEnd], &idx);
        
        // 왼쪽 및 오른쪽 서브트리의 노드 개수
        leftsize = idx - inStart;
        rightsize = inEnd - idx;

        printf("%d ", inorder[idx]); // 루트 처리
        preorder(inStart, idx - 1, postStart, postStart + leftsize - 1); // 왼쪽 서브트리에 대하여 전위순회
        preorder(idx + 1, inEnd, postStart + leftsize, postEnd - 1); // 오른쪽 서브트리에 대하여 전위순회
    }
}

void searchRoot(int root, int *rootIdx)
{
    int i = 0;

    while(1){
        if(inorder[i] == root){
            *rootIdx = i;
            return;
        }

        ++i;
    }
}