#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string, int> umap; // <완주한 사람 이름, 이름에 해당하는 사람 수>
    
    // 도착한 사람들을 
    for(const auto &c : completion) {
        ++umap[c]; // unordered_map에서 operator[]는 존재하지 않는 키에 대해 기본값으로 생성된 값을 삽입
    }
    
    for(const auto &p : participant) {
        answer = p;
        
        if(umap.find(p) != umap.end() && umap[p] > 0) --umap[p];
        else break;
    }
    
    return answer;
}