#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct Node {
    int num;
    int sheep;
    int wolf;
    vector<int> adjList;
} Node;

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;
    
    vector<vector<int>> tree(info.size());
    for(const auto &edge : edges) 
        tree[edge[0]].push_back(edge[1]);
    
    queue<Node> q;
    q.push({0, 1, 0, tree[0]});
    
    while(!q.empty()) {
        Node curr = q.front();
        q.pop();
        
        answer = max(answer, curr.sheep);
        
        for(const int &neighbor : curr.adjList) {
            int sheep = curr.sheep;
            int wolf = curr.wolf;
            
            info[neighbor] ? ++wolf : ++sheep;
            
            if(wolf < sheep) {
                vector<int> adjList = curr.adjList;
                
                adjList.erase(remove(adjList.begin(), adjList.end(), neighbor), adjList.end());
                adjList.insert(adjList.end(), tree[neighbor].begin(), tree[neighbor].end());
                              
                q.push({neighbor, sheep, wolf, adjList});
            }        
        }
    }
    
    return answer;
}