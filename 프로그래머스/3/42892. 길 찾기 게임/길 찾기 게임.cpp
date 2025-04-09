#include <vector>
#include <algorithm>

using namespace std;

// 이진 트리에서 사용할 노드
struct Node {
    int idx, x, y;
    Node *left = nullptr;
    Node *right = nullptr;
    
    Node(int idx, int x, int y) : idx(idx), x(x), y(y) {}
};

class BinaryTree{
private:
    Node *root = nullptr;
    
    // 1. y좌표가 큰 순서대로 정렬
    // 2. y좌표가 같으면, x좌표가 작은 순서대로 정렬
    static bool compareNode(Node *a, Node *b) {
        if(a->y == b->y)
            return a->x < b->x;
        return a->y > b->y;
    }
    
    // 새 노드 추가
    Node *addNode(Node *currNode, Node *newNode) {
        if(currNode == nullptr)
            return newNode;
        
        if(newNode->x < currNode->x)
            currNode->left = addNode(currNode->left, newNode);
        else
            currNode->right = addNode(currNode->right, newNode);
        
        return currNode;
    }
    
    // 전위 순회
    void pre(Node *node, vector<int> &answer) {
        if(node != nullptr) {
            answer.push_back(node->idx);
            pre(node->left, answer);
            pre(node->right, answer);
        }
        
        return;
    }
    
    // 후위 순회
    void post(Node *node, vector<int> &answer) {
        if(node != nullptr) {
            post(node->left, answer);
            post(node->right, answer);
            answer.push_back(node->idx);
        }
        
        return;
    }
    
public:
    BinaryTree() : root(nullptr) {}
    
    void buildTree(vector<vector<int>> &nodeInfo) {
        vector<Node *> nodes;
        
        // 각 노드의 정보를 저장
        for(int i = 0; i < nodeInfo.size(); ++i) {
            nodes.push_back(new Node(i + 1, nodeInfo[i][0], nodeInfo[i][1]));
        }
        
        // 노드 정렬 -> 정렬 후 반드시 첫번째 요소는 루트 노드
        sort(nodes.begin(), nodes.end(), compareNode);
        
        // 이진 트리 생성
        for(Node *node : nodes) {
            root = addNode(root, node);
        }
    }
    
    // 전위 순회
    vector<int> preorder() {
        vector<int> answer;
        pre(root, answer);
        
        return answer;
    }
    
    // 후위 순회
    vector<int> postorder() {
        vector<int> answer;
        post(root, answer);
        
        return answer;
    }
};

vector<vector<int>> solution(vector<vector<int>> nodeInfo) {
    BinaryTree tree;
    
    // 이진트리 생성
    tree.buildTree(nodeInfo);
    
    // 순회 결과 반환
    vector<int> preAnswer = tree.preorder();
    vector<int> postAnswer = tree.postorder();
    
    return {preAnswer, postAnswer};
}