#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, string> make_table(const vector<string> &record) {
    unordered_map<string, string> umap;
    
    for(const auto &r : record) {
        size_t pos1 = r.find(' ');
        size_t pos2 = r.find(' ', pos1 + 1);
        
        string action = r.substr(0, pos1);
        
        if(action == "Enter" || action == "Change") {
            string uid = r.substr(pos1 + 1, pos2 - (pos1 + 1));
            string nickname = r.substr(pos2 + 1);
            
            umap[uid] = nickname;
        }
    }
    
    return umap;
}

// record: 닉네임을 변경한 기록이 담긴 문자열 배열
// answer: 최종적으로 방을 개설한 사람이 보게 되는 메시지
vector<string> solution(vector<string> record) {
    vector<string> answer;
    auto umap = make_table(record);
    
    for(const auto &r : record) {
        size_t pos1 = r.find(' ');
        size_t pos2 = r.find(' ', pos1 + 1);
        
        string action = r.substr(0, pos1);
        string uid = r.substr(pos1 + 1, pos2 - (pos1 + 1));
        
        if(action == "Enter") answer.push_back(umap[uid] + "님이 들어왔습니다.");
        else if(action == "Leave") answer.push_back(umap[uid] + "님이 나갔습니다.");
    }
    
    return answer;
}