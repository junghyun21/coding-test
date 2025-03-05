#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());
    stack<pair<int, int>> stk; // <price, insert_sec>
    int i;
    
    for(i = 0; i < prices.size(); ++i) {
        // 스택이 비어있지 않고, 가격이 떨어진 경우
        while(!stk.empty() && stk.top().first > prices[i]) {
            answer[stk.top().second] = i - stk.top().second;
            stk.pop();
        }
        
        stk.push({prices[i], i}); // 해당 가격(prices[i])이 기록된 초와 인덱스 값(i)이 동일
    }
    
    // 스택에 남아있는 값들 처리
    --i;
    while(!stk.empty()) {
        answer[stk.top().second] = i - stk.top().second;
        stk.pop();
    }
        
    return answer;
}