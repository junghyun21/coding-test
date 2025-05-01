#include <unordered_set>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    string word;
    int cnt;
};

vector<string> select_word(vector<string> words, string word) {
    unordered_set<string> res;
    
    // word와 words[j]의 i번째 인덱스의 알파벳만 다른지 확인
    for(int i = 0; i < word.size(); ++i) {
        for(int j = 0; j < words.size(); ++j) {
            // j번째 알파벳 외의 모든 알파벳이 동일한지 확인
            // substr(pos, len): If pos == size(), the returned string is empty.
            if(word[i] != words[j][i] &&
               word.substr(0, i) == words[j].substr(0, i) && 
               word.substr(i + 1, words.size()) == words[j].substr(i + 1, words.size()))
                res.insert(words[j]);   
        }
    }
    
    vector<string> vec(res.begin(), res.end());
    
    return vec;
}

int solution(string begin, string target, vector<string> words) {
    unordered_set<string> s;
    queue<Node> q;
    
    q.push({begin, 0});
    
    int answer = 0;
    
    while(!q.empty()) {
        Node curr = q.front();
        q.pop();
        
        if(curr.word == target) {
            answer = curr.cnt;
            break;
        }
        
        // 이미 변경했었던 단어인 경우
        auto res = s.insert(curr.word);
        if(!res.second)
            continue;
        
        vector<string> vec = select_word(words, curr.word);
        for(const string &str : vec) {    
            q.push({str, curr.cnt + 1});
        }
    }
    
    return answer;
}