#include <string>
#include <vector>

using namespace std;

string solution(string my_string, string overwrite_string, int s) {
    string answer = "";
    
//     answer = my_string.substr(0, s) + overwrite_string;
    
//     if(overwrite_string.length() + s < my_string.length())
//     {
//         answer += my_string.substr(overwrite_string.length() + s, my_string.length());
//     }
    
    // replace(치환될 문자열의 시작 위치, 치환할 길이, 치환할 문자열)
    answer = my_string.replace(s, overwrite_string.length(), overwrite_string);
    
    return answer;
}