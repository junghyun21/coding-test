// 백준허브는 실행 결과가 가장 빠른 코드를 커밋해주기 때문에 직접 올림!!
// 전위 순회 결과 바탕으로 트리를 생성하고
// 생성한 트리를 후위 순회했기 때문에 시간초과가 발생했다고 판단
// 그러나 scanf() 부분에서 EOF를 받지 못하여 시간초과가 되었던 것 같음
// while(scanf("%d", &key))를 while(scanf("%d", key) != EOF)로 변경하였더니 잘 돌아감

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

TreeNode *createNode(int key);
TreeNode *insert(TreeNode *root, int key);
void printPostorder(TreeNode *root);

int main()
{
    TreeNode *root = NULL;
    int key;

    // 트리 생성
    // 전위 순회는 루트를 먼저 방문하기 때문에 트리의 루트는 처음에 들어온 값으로 지정됨
    // 루트 이후의 값부터는 어떤 값이 들어오든, 루트를 기준으로 트리가 생성됨
    while(scanf("%d", &key) != EOF)
        root = insert(root, key);

    printPostorder(root);

    return 0;
}

TreeNode *createNode(int key)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

    newNode->key = key;
    newNode->left = newNode->right = NULL;

    return newNode;
}

TreeNode *insert(TreeNode *root, int key)
{
    if(root == NULL)
        return createNode(key);

    if(key < root->key)
        root->left = insert(root->left, key);
    else if(key > root->key)
        root->right = insert(root->right, key);
    
    return root;
}

void printPostorder(TreeNode *root)
{
    if(root != NULL){
        printPostorder(root->left);
        printPostorder(root->right);
        printf("%d\n", root->key);
    }
}
