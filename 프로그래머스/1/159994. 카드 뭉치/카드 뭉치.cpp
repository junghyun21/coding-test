#include <string>
#include <vector>
#include <queue>

using namespace std;

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {    
    // 카드 뭉치 내 카드를 순서대로 담을 큐 생성 및 초기화
    queue<string> first;
    queue<string> second;
    for(const string &s : cards1) first.push(s);
    for(const string &s : cards2) second.push(s);
    
    // 목표하는 단어 배열
    queue<string> target;
    for(const string &s : goal) target.push(s);
    
    // 목표하는 단어 배열 생성 가능 여부 확인
    while(!target.empty() ) {
        if(!first.empty() && first.front() == target.front()) first.pop();
        else if(!second.empty() && second.front() == target.front()) second.pop();
        else break;
            
        target.pop();
    }
    
    return target.empty() ? "Yes" : "No";
}