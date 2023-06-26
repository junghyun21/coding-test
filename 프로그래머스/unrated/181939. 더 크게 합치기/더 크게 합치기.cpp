#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    int answer = 0;
    string str1, str2;
    int ab, ba;
    
    str1 = to_string(a) + to_string(b);
    str2 = to_string(b) + to_string(a);
    
    ab = stoi(str1);
    ba = stoi(str2);
    
    answer = ab > ba ? ab : ba;
    
    return answer;
}