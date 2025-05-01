#include <vector>

using namespace std;

int dfs(const vector<int> &numbers, const int &target, int res, int idx) {
    int temp = 0;
    
    if(idx < numbers.size()) {
        temp += dfs(numbers, target, res + numbers[idx], idx + 1);
        temp += dfs(numbers, target, res - numbers[idx], idx + 1);
        
        return temp;
    }

    return (res == target) ? 1 : 0;
}

// numbers: 사용할 수 있는 숫자가 담긴 배열 (순서를 바꾸지 않고 적절히 더하거나 뺌)
// target: 타겟 넘버
int solution(vector<int> numbers, int target) {    
    return dfs(numbers, target, 0, 0);
}