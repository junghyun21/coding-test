#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

typedef struct Node {
    unordered_set<int> neighbor;
    int cur;
    int wolf;
    int sheep;
} Node;

int solution(vector<int> info, vector<vector<int>> edges) {
    vector<vector<int>> adjList(info.size());
    for(int i = 0; i < edges.size(); ++i) {
        adjList[edges[i][0]].emplace_back(edges[i][1]);
    }
    
    queue <Node> q;
    q.push({unordered_set<int>(adjList[0].begin(), adjList[0].end()), 0, 0, 1});
    
    int answer = 0;
    
    while(!q.empty()) {
        Node node = q.front();
        q.pop();
        
        answer = (answer < node.sheep) ? node.sheep : answer;
        
        for(const int &next : node.neighbor) {
            int newWolf = node.wolf;
            int newSheep = node.sheep;
            
            (info[next] == 1) ? ++newWolf : ++newSheep;
            
            if(newWolf < newSheep) {
                unordered_set<int> newNeighbor = node.neighbor;
                
                newNeighbor.erase(next);
                newNeighbor.insert(adjList[next].begin(), adjList[next].end());
                
                q.push({newNeighbor, next, newWolf, newSheep});
            }
    
        }
    }
    
    
    return answer;
}