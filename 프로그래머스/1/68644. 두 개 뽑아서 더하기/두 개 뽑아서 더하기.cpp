#include <set>
#include <vector>

using namespace std;

vector<int> solution(vector<int> numbers) {
    set<int> sum; // 두 수의 합을 저장할 공간
    
    for(int i = 0; i < numbers.size(); i++) {
        for(int j = i + 1; j < numbers.size(); j++){
            sum.insert(numbers[i] + numbers[j]);
        }
    }
    
    vector<int> answer(sum.begin(), sum.end());
    
    return answer;
}