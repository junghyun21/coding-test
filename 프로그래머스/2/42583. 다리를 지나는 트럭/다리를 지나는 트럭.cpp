#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// bridge_length: 다리에 올라갈 수 있는 트럭의 최대 개수 (다리의 길이)
// weight: 다리가 견딜 수 있는 최대 무게
// truck_weights: 트럭 별 무게
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<pair<int, int>> bridge;   // <트럭 무게, 다리를 다 건넜을 때의 시간>
    int answer;                     // 모든 트럭이 지나갈 때 걸리는 최소 시간
    int time = 0;                   // 현재 시간
    int total_weight = 0;           // 다리 위의 트럭의 총 무게
    int idx = 0;                    // 현재 다리를 건너고 있는 트럭 중 가장 뒷쪽에 위치한 트럭의 인덱스
    
    while(idx < truck_weights.size()) {
        if(!bridge.empty()) {
            pair p = bridge.front();
            
            if(p.second <= time) {
                total_weight -= p.first;
                bridge.pop();
            }
        }
        
        if((bridge.size() < bridge_length) && (total_weight + truck_weights[idx] <= weight)) {
            bridge.push({truck_weights[idx], time + bridge_length});
            
            total_weight += truck_weights[idx++];
            ++time;
        }
        else {
            pair p = bridge.front();
            total_weight -= p.first;
            time = p.second;
            
            bridge.pop();
        }
    }
    
    answer = bridge.back().second + 1;
    
    return answer;
}