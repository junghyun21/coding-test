// 연결리스트로 구현하는 경우, 값을 모두 입력 받은 이후에 자식과 부모노드를 연결할 수 있음 -> 비효율적일거 같다고 판단
// 각 노드는 차례대로 알파벳 대문자를 가진다는 점을 활용해보자
// 동적 배열을 활용해서 트리를 구현해보자
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode
{
    char data;
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

void preorder(treeNode *tree); // 전위 순회
void inorder(treeNode *tree); // 중위 순회
void postorder(treeNode *tree); // 후위 순회

int main()
{
    treeNode *tree; // 트리를 동적배열로 구현
    int i, n; // 노드의 개수
    char data, left, right; // 입력받을 알파벳
    int index;

    // 노드의 개수 == 베얄의 크기
    // A는 인덱스 0, B는 인덱스 1, ...
    scanf("%d", &n);
    tree = (treeNode *)malloc(n * sizeof(treeNode));

    // 각 노드들을 입력 받고, 트리 생성
    while(n--){
        scanf(" %c %c %c", &data, &left, &right);

        index = data - 'A';

        tree[index].data = data;
        if(left == '.')
            tree[index].left = NULL;
        else
            tree[index].left = tree + (left - 'A');
        if(right == '.')
            tree[index].right = NULL;
        else
            tree[index].right = tree + (right - 'A');
    }

    // 전위 순회
    preorder(tree);
    printf("\n");

    // 중위 순회
    inorder(tree);
    printf("\n");

    // 후위 순회
    postorder(tree);
    printf("\n");

    return 0;
}

void preorder(treeNode *tree)
{
    if(tree){
        printf("%c", tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void inorder(treeNode *tree)
{
    if(tree){
        inorder(tree->left);
        printf("%c", tree->data);
        inorder(tree->right);
    }
}

void postorder(treeNode *tree)
{
    if(tree){
        postorder(tree->left);
        postorder(tree->right);
        printf("%c", tree->data);
    }
}