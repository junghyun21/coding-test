#include <string>
#include <stack>

using namespace std;

bool isCorrect(string s) {
    stack<char> stack;
    for(const auto &c : s) {
        if(c == '(') {
            stack.push(c);
        }   
        else if(c == ')'){
            if(stack.empty() || stack.top() != '(') { 
                return false;
            }
            else {
                stack.pop();
            }
        }
        else if(c == '{') {
            stack.push(c);
        }
        else if(c == '}') {
            if(stack.empty() || stack.top() != '{') { 
                return false;
            }
            else {
                stack.pop();
            }
        }
        else if(c == '[') {
            stack.push(c);
        }
        else if(c == ']') {
            if(stack.empty() || stack.top() != '[') { 
                return false;
            }
            else {
                stack.pop();
            }
        }
    }
        
    return stack.empty();
}

int solution(string s) {
    int answer = 0;
    
    for(int i = 0; i < s.size(); ++i) {
        if(isCorrect(s))
            ++answer;
    
        s = s.substr(1) + s[0];
    }
    
    return answer;
}