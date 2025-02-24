#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    
    answer.reserve(10000);
    
    for(auto i = numbers.begin(); i < numbers.end() - 1; i++) {
        for(auto j = i + 1; j < numbers.end(); j++){
            answer.push_back(*i + *j);
        }
    }
    
    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());
    
    return answer;
}