#include <vector>
#include <algorithm>

using namespace std;

// arr는 중복 값 없는, 길이가 1 이상인 배열
vector<int> solution(vector<int> arr, int divisor) {
    vector<int> answer;
    
    sort(arr.begin(), arr.end());
    
    for (const auto &e : arr) {
        if(e % divisor == 0) {
            answer.push_back(e);
        }
    }
    
    if(answer.size() == 0)
        answer.push_back(-1);
    
    return answer;
}