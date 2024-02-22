// 노드의 개수가 주어지므로, 동적 배열을 이용하여 트리의 노드 생성
// 각 노드들이 저장된 배열의 인덱스가 노드의 고유한 이름 (0 노드는 tree[0], 1 노드는 tree[1])
// 자식노드의 개수는 알 수 없으므로, 각 노드는 연결리스트로 자식노드의 인덱스를 가지고 있음 (childNode)
// 예를 들어 0번째 노드의 자식이 1, 2, 3, 4라면 0 -> 1-2-3-4 이런 형태로 자식 노드의 인덱스를 가리킴
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct childNode{
    int idx;
    struct childNode *sibling; // 형제 노드
}childNode;

typedef struct treeNode{
    bool isExist; // 배열을 통해 노드를 생성했기 때문에, 노드의 삭제 여부를 쉽게 확인하도록 하기 위함
    int parentIdx; // 부모 노드의 정보를 담고 있는 배열의 인덱스
    struct childNode *headChild;
    struct childNode *tailChild;
}treeNode;

void insertNode(treeNode *parent, int childIdx);
void deleteNode(treeNode **tree, int deleteIdx);
void deleteAllNode(treeNode **tree, int n);
int countingLeaf(treeNode *tree, int n); 

int main()
{
    treeNode *tree;
    int i, n; // 노드의 개수
    int node, leafCnt;

    // 노드의 개수를 입력받고, 노드들의 정보를 저장할 공간 생성 및 초기화
    scanf("%d", &n);
    tree = (treeNode *)malloc(n * sizeof(treeNode));
    for(i = 0; i < n; i++){
        tree[i].isExist = true;
        tree[i].parentIdx = -1;
        tree[i].headChild = NULL;
        tree[i].tailChild = NULL;
    }

    // 부모 노드가 가리키는 연결리스트(tree[node])에 자식 노드(tree[i]) 삽입
    for(i = 0; i < n; i++){
        scanf("%d", &node);
        
        // 부모 노드가 없는 경우 (루트노드인 경우)
        if(node == -1)
            continue;
        
        tree[i].parentIdx = node;
        insertNode(&tree[node], i);
    }

    // 삭제할 노드를 입력받고, 해당 노드 삭제
    // 삭제할 노드가 루트노드인 경우, 모든 노드 삭제
    scanf("%d", &node);
    if(tree[node].parentIdx == -1)
        deleteAllNode(&tree, n);
    else
        deleteNode(&tree, node);

    // 리프 노드 카운트
    // 노드가 존재하면서(isExist == true), 자식 노드가 없는(headChild == NULL) 노드의 개수 카운팅
    leafCnt = countingLeaf(tree, n);
    printf("%d\n", leafCnt);

    return 0;
}

// parent 노드가 자식 노드의 인덱스(childIdx) 정보를 연결리스트 형태로 가리킴
void insertNode(treeNode *parent, int childIdx)
{
    childNode *newNode = (childNode *)malloc(sizeof(childNode));
    newNode->idx = childIdx;
    newNode->sibling = NULL;

    // 연결 리스트가 비어있는 상태 (해당 노드는 아무 자식도 가지고 있지 않음)
    if(!parent->headChild){
        parent->headChild = parent->tailChild = newNode;
    }
    // 헤당 노드가 1개 이상의 자식노드를 가지고 있는 상태
    else{
        parent->tailChild->sibling = newNode;
        parent->tailChild = newNode;
    }
}

// 해당 노드와 그 노드의 자손 노드들 삭제
void deleteNode(treeNode **tree, int deleteIdx)
{
    childNode *node, *delete, *prev;
    int parentIdx;

    // 동적 배열로 트리 구현했기 때문에, 특정한 값으로 삭제되었음을 나타냄
    (*tree)[deleteIdx].isExist = false;

    // 자식 노드가 있는 경우
    // 재귀함수 호출
    if((*tree)[deleteIdx].headChild != NULL)
        while((node = (*tree)[deleteIdx].headChild) != NULL)
            deleteNode(tree, node->idx);

    // 부모 노드에 연결리스트로 저장된 자신의 인덱스 삭제
    parentIdx = (*tree)[deleteIdx].parentIdx;
    delete = (*tree)[parentIdx].headChild;
    prev = NULL;
    while(1){
        if(delete->idx == deleteIdx){
            // 자식 노드가 하나만 있는 경우
            if((*tree)[parentIdx].headChild == (*tree)[parentIdx].tailChild){
                (*tree)[parentIdx].headChild = NULL;
                (*tree)[parentIdx].tailChild = NULL;
            }
            else{
                // 삭제할 노드가 헤드노드인 경우
                if(prev == NULL)
                    (*tree)[parentIdx].headChild = (*tree)[parentIdx].headChild->sibling;
                else{
                    // 삭제할 노드가 꼬리노드인 경우
                    if(delete->sibling == NULL)
                        (*tree)[parentIdx].tailChild = prev;
                    prev->sibling = delete->sibling;
                }
            }
            free(delete);
            
            break;
        }
        prev = delete;
        delete = delete->sibling;
    }
    (*tree)[deleteIdx].parentIdx = -1;

    return;
}

void deleteAllNode(treeNode **tree, int n)
{
    childNode *delete;

    for(int i = 0; i < n; i++){
        (*tree)[i].isExist = false;
        (*tree)[i].parentIdx = -1;

        // 자식 노드가 저장된 인덱스의 연결리스트 모두 삭제
        while((delete = (*tree)[i].headChild) != NULL){
            (*tree)[i].headChild = (*tree)[i].headChild->sibling;
            free(delete);
        }
        (*tree)[i].tailChild = NULL;
    }
}
// 리프노드의 개수 카운팅
// 리프노드: 해당 노드가 존재하며(isExist == true), 자식 노드가 없음(headChild == NULL)
int countingLeaf(treeNode *tree, int n)
{
    int i, leafCnt = 0;

    for(i = 0; i < n; i++)
        if(tree[i].isExist && !tree[i].headChild)
            ++leafCnt;

    return leafCnt;
}