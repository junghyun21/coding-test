#include <unordered_map>
#include <vector>

using namespace std;

int solution(vector<vector<string>> clothes) {
    unordered_map<string, vector<string>> umap;
    int answer = 1;
    
    for(const auto &e : clothes) {
        umap[e[1]].push_back(e[0]);
    }
    
    for(const auto &e : umap) {
        answer *= (e.second.size() + 1);
    }
    --answer; // 아무것도 안입은 경우 제외

    return answer;
}