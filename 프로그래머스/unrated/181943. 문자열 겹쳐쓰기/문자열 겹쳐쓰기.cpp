#include <string>
#include <vector>

using namespace std;

string solution(string my_string, string overwrite_string, int s) {
    string answer = "";
    
    answer = my_string.substr(0, s) + overwrite_string;
    
    if(overwrite_string.length() + s < my_string.length())
    {
        answer += my_string.substr(overwrite_string.length() + s, my_string.length());
    }
    
    return answer;
}