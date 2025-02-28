#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<double, int> &a, const pair<double, int> &b) {
    if(a.first == b.first)
        return a.second < b.second;
    
    return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> players(N + 1);     // 각 스테이지의 플레이어 수
    
    for(int i = 0; i < stages.size(); ++i) {
        ++players[stages[i] - 1];
    }
    
    vector<pair<double, int>> result(N);    // first: 실패율, second: 스테이지 번호
    double failRate;                        // 실패율
    double failedPlayers;                   // 스테이지에 도달했으나 아직 클리어하지 못한 플레이어 수
    double totalPlayers;                    // 스테이지에 도달한 플레이어 수
    
    totalPlayers = stages.size();
    
    // 실패율 = 스테이지에 도달했으나 아직 클리어하지 못한 플레이어의 수 / 스테이지에 도달한 플레이어 수
    for(int i = 0; i < N; ++i) {
        failedPlayers = players[i]; 
        
        if(totalPlayers == 0)
            failRate = 0;
        else
            failRate = failedPlayers / totalPlayers;
        
        result[i].first = failRate;
        result[i].second = i + 1;
        
        totalPlayers -= players[i];
    }
    
    sort(result.begin(), result.end(), cmp);
    
    vector<int> answer;
    for(const auto &e : result)
        answer.push_back(e.second);
    
    return answer;
}