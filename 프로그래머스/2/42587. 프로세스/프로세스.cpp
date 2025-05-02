#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    
    queue<int> q;
    for(int i = 0; i < priorities.size(); ++i) {
        q.push(i);
    }
    
    vector<int> sort_priorities(priorities.begin(), priorities.end());    
    sort(sort_priorities.begin(), sort_priorities.end(), greater<int>());
    
    int idx = 0;
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        
        if(priorities[curr] == sort_priorities[idx]) {
            ++answer;
            ++idx;
            
            if(curr == location) {
                break;
            }
        }
        else {
            q.push(curr);
        }
    }
    
    return answer;
}