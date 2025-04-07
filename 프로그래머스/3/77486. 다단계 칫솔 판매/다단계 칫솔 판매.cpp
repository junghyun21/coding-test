#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const string ROOT = "-";

void add_profit(const unordered_map<string, string> &parent_map, unordered_map<string, int> &profit_map, string child, int profit) {
    if(profit * 0.1 > 0 && child != ROOT) {
        int parent_profit = int(profit * 0.1);
        profit_map[child] += (profit - parent_profit);
        
        add_profit(parent_map, profit_map, parent_map.at(child), parent_profit);
    }
    
    return;
}

// enroll: 민호를 제외한 각 판매원의 이름을 담은 배열
// referral: enroll[i] 판매원이 참여시킨 판매원들의 이름(referral[i]), 없는 경우에는 "-"로 표시
// seller: amount[i]의 판매원 이름을 나열한 배열
// amount: 판매량 집계 데이터의 판매 수량을 나열한 배열 (이익 = 판매랑 * 100)
// -> 접근 방법: 자식이 누군지는 알 필요 x, 부모가 누군지 확인 후 부모의 이익를 늘려주면 됨
vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer; // 각 판매원이 득한 이익금을 나열한 배열
    unordered_map<string, int> profit_map; // <판매원, 이익>
    unordered_map<string, string> parent; // <자식(소개를 받은 사람), 부모(소개해준 사람)>
  
    // 각 판매원들을 순서대로 unordered_map에 저장
    // 각 자식(key)들의 부모(value) 저장
    for(int i = 0; i < enroll.size(); ++i) {
        profit_map[enroll[i]];
        parent[enroll[i]] = referral[i];
    }
    
    // 자식부터 위의 부모 순으로 올라가며 이익 분배
    for(int i = 0; i < seller.size(); ++i) {
        add_profit(parent, profit_map, seller[i], amount[i] * 100);
    }
    
    // 맵의 value를 vector에 저장
    for(int i = 0; i < enroll.size(); ++i) {
        answer.push_back(profit_map[enroll[i]]);
    }

    return answer;
}