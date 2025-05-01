#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

bool all_arrived(const unordered_map<string, int> &left_cnt) {
    for(const auto &[key, value] : left_cnt) {
        if(value != 0) 
            return false;
    }
    
    return true;
}

bool find_path(const unordered_map<string, vector<string>> &airports,
               unordered_map<string, vector<bool>> visited,
               unordered_map<string, int> &left_cnt,
               vector<string> &answer,
               string arrive) {  
    // 더 이상 갈 곳이 없을 때, 모든 공항을 방문한 경우 true 리턴
    if(left_cnt[arrive] == 0) {
        if(all_arrived(left_cnt)) {
            answer.push_back(arrive);
            return true;
        }
            
        return false;
    }

    answer.push_back(arrive);
    --left_cnt[arrive];
    
    for(int i = 0; i < airports.at(arrive).size(); ++i) {
        if(visited[arrive][i])
            continue;
        
        visited[arrive][i] = true;
        
        if(find_path(airports, visited, left_cnt, answer, airports.at(arrive)[i]))
            return true;
        
        visited[arrive][i] = false;
    }
    
    answer.pop_back();
    ++left_cnt[arrive];
    
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    unordered_map<string, vector<string>> airports; // <출발 공항, 도착 가능한 공항 배열>
    unordered_map<string, vector<bool>> visited;    // 공항 방문 여부
    unordered_map<string, int> left_cnt;            // 출발한 공항에서 남은 도착 가능 공항 개수
    
    for(const auto &ticket : tickets) {
        airports[ticket[0]].push_back(ticket[1]);
        visited[ticket[0]].push_back(false);
        ++left_cnt[ticket[0]];
    }
    
    for(auto &[key, value] : airports) {
        sort(value.begin(), value.end());
    }
    
    find_path(airports, visited, left_cnt, answer, "ICN");
    
    return answer;
}