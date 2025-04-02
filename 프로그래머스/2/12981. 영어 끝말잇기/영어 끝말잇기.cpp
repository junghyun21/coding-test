#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer(2, 0);
    unordered_set<string> uset;
    char old_ch = words[0][0];
    
    for(int i = 0; i < words.size(); ++i) {
        auto res = uset.insert(words[i]);
        
        // 끝말잇기 규칙에 어긋난 단어인 경우
        // 이미 나왔던 단어인 경우(uset에 삽입되지 않음)
        if(old_ch != words[i][0] || !res.second) {
            answer = {i % n + 1, i / n + 1};
            break;
        }
        
        old_ch = words[i][words[i].size() - 1];
    }

    return answer;
}