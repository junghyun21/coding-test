#include <stack>
#include <string>

using namespace std;

int solution(string s)
{
    stack<char> stk;
    
    for(const auto &c : s) {
        if(stk.empty()) {
            stk.push(c);       
        } 
        else {
            if(c == stk.top()) stk.pop();
            else stk.push(c);
        }
    }

    return static_cast<int>(stk.empty());
}