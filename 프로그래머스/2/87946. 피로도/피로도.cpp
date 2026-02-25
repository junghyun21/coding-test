#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef struct node {
    int k;
    int cnt;
    vector<bool> visited;
} Node;

int solution(int k, vector<vector<int>> dungeons) {
    int answer = 0;    
    stack<Node> s;
    
    s.push({k, 0, vector<bool>(dungeons.size(), false)});
    
    while(!s.empty()) {
        auto [cur_k, cnt, visited] = s.top();
        s.pop();
        
        answer = max(answer, cnt);
        
        for(int i = 0; i < dungeons.size(); ++i) {
            if(!visited[i] && cur_k >= dungeons[i][0]) {
                vector<bool> new_visited = visited;
                new_visited[i] = true;
                
                s.push({cur_k - dungeons[i][1], cnt + 1, new_visited});
            }
        
        }
    }
    
    return answer;
}