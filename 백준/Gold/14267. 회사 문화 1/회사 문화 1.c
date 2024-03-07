// 칭찬을 받을 때마다 DFS를 해주었더니, 시간 초과 발생
// 각 노드가 칭찬받은 횟수를 따로 저장해두었다가, DFS을 한 번 진행히고 이 때 횟수 구함

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100001

typedef struct ChildNode{
    int node;
    struct ChildNode *sibling;
}ChildNode;

typedef struct TreeNode{
    int childNum;
    struct ChildNode *child;
}TreeNode;

void linkParent(int parent, int child);
void plusCompliment(int node);

TreeNode tree[MAX_NODE];
int compliments[MAX_NODE];

int main()
{
    int n, m, node, w, i;

    // 회사의 직원 수(n), 칭찬 횟수(m) 입력
    scanf("%d %d", &n, &m);

    // 직원의 직속 상사의 번호(node)를 입력 받고
    // 직원과 직속 상사의 관계 생성
    scanf("%d", &node); // -1인 경우
    for(i = 2; i <= n; i++){
        scanf("%d", &node);
        linkParent(node, i);
    }

    // 직속 상사로부터 칭찬을 받은 직원 번호(node), 칭찬의 수치(w)를 입력 받고
    // 중위 순회를 통해 부하들의 칭찬 점수 조정
    while(m--){
        scanf("%d %d", &node, &w);
        compliments[node] += w;
    }
    plusCompliment(1); // 루트 노드부터 DFS 진행

    // 칭찬 받은 정도 출력
    for(i = 1; i <= n; i++)
        printf("%d ", compliments[i]);
    printf("\n");

    return 0;
}

void linkParent(int parent, int child)
{
    ChildNode *newChild = (ChildNode *)malloc(sizeof(ChildNode));

    newChild->node = child;
    newChild->sibling = NULL;

    if(tree[parent].childNum == 0){
        tree[parent].child = newChild;
    }
    else{
        newChild->sibling = tree[parent].child;
        tree[parent].child = newChild;
    }

    tree[parent].childNum++;

    return;
}

void plusCompliment(int node)
{
    ChildNode *temp = tree[node].child;
    
    while(temp != NULL){
        compliments[temp->node] += compliments[node];
        plusCompliment(temp->node);
        temp = temp->sibling;
    }
    
    return;
}