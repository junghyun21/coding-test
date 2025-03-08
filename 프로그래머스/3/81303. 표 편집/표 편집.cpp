#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

// n: 처음 표의 행 개수
// k: 처음에 선택된 행의 위치
// cmd: 수행한 명령어들이 담긴 문자열 배열
string solution(int n, int k, vector<string> cmd) {
    vector<pair<int, int>> link(n); // <prev, next>
    stack<int> deleted;
    
    // 각 행의 이전/다음 행의 인덱스 초기화
    for(int i = 0; i < n; ++i)
        link[i] = {i - 1, i + 1};
    
    // 명령어(cmd) 기반으로 표의 행 선택/삭제/복구
    for(const string &s : cmd) {
        if(s[0] == 'U') {
            int x = stoi(s.substr(2));
            
            while(x-- && link[k].first != -1)
                k = link[k].first;
        }
        else if(s[0] == 'D') {
            int x = stoi(s.substr(2));
            
            while(x-- && link[k].second != n)
                k = link[k].second;
        }
        else if(s[0] == 'C') {
            int prevIdx = link[k].first;
            int nextIdx = link[k].second;
            
            deleted.push(k);
            
            if(prevIdx != -1) {
                link[prevIdx].second = nextIdx;
            }
            
            if(nextIdx != n) {
                link[nextIdx].first = prevIdx;
                k = nextIdx;
            }
            else {
                k = prevIdx;
            }  
        }
        else if(!deleted.empty()) {
            int idx = deleted.top();
            int prevIdx = link[idx].first;
            int nextIdx = link[idx].second;
            
            if(prevIdx != -1)
                link[prevIdx].second = idx;
            
            if(nextIdx != n)
                link[nextIdx].first = idx;
            
            deleted.pop();
        }
    }
    
    // 최종적으로 삭제된 것들은 모두 stack에 남아있음
    string answer(n, 'O');
    
    while(!deleted.empty()) {
        int idx = deleted.top();
        answer.at(idx) = 'X';
        
        deleted.pop();
    }
    
    return answer;
}