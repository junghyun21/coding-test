#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int leftIdx;
    int rightIdx;
    int parentIdx;
    bool isPassed;
}Node;

void inorder(int *endIdx, int rootIdx); // 중위 순회
void similar_inorder(int endIdx, int rootIdx, int *cnt); // 유사 중위 순회

Node *tree;
bool isFinish;

int main()
{
    int n;
    int a, b, c;
    int endIdx;
    int cnt = 0;

    scanf("%d", &n);

    tree = (Node *)malloc(sizeof(Node) * (n + 1));

    while(n--){
        scanf("%d %d %d", &a, &b, &c);

        // 자식 노드 지정
        tree[a].leftIdx = b;
        tree[a].rightIdx = c;

        // 부모 노드 지정
        tree[b].parentIdx = a;
        tree[c].parentIdx = a;

        tree[a].isPassed = false;
    }
    tree[1].parentIdx = -1;

    // 루트 노드는 항상 1번 노드
    inorder(&endIdx, 1);
    similar_inorder(endIdx, 1, &cnt);

    printf("%d\n", cnt);

    return 0;
}

void inorder(int *endIdx, int rootIdx)
{
    if(rootIdx == -1)
        return;

    inorder(endIdx, tree[rootIdx].leftIdx);
    *endIdx = rootIdx;
    inorder(endIdx, tree[rootIdx].rightIdx);

    return;
}

void similar_inorder(int endIdx, int rootIdx, int *cnt)
{   
    int left = tree[rootIdx].leftIdx;
    int right = tree[rootIdx].rightIdx;
    int parent = tree[rootIdx].parentIdx;

    tree[rootIdx].isPassed = true;

    // 1. 현재 위치한 노드의 왼쪽 자식 노드가 존재하고 아직 방문하지 않았다면 이동
    if(left != -1 && !tree[left].isPassed){
        (*cnt)++;
        similar_inorder(endIdx, left, cnt);
    }
    // 2. 현재 위치한 노드의 오른쪽 자식 노드가 존재하고 아직 방문하지 않았다면 이동
    if(right != -1 && !tree[right].isPassed){
        (*cnt)++;
        similar_inorder(endIdx, right, cnt);
    }
    // 3. 현재 노드가 유사 중위 순회의 끝이라면, 유사 중위 순회 종료
    if(rootIdx == endIdx){
        isFinish = true;
        return;
    }

    // 4. 중위 순회의 끝이 아니라면, 부모노드로 이동
    if(!isFinish){
        if(tree[rootIdx].parentIdx != -1)
            (*cnt)++;
    }

    return;
}