#include <algorithm>
#include <vector>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;
    long long min_time = 1;
    long long max_time = (long long)*max_element(times.begin(), times.end()) * n;
    long long mid_time;
    
    while(min_time <= max_time) {
        mid_time = (min_time + max_time) / 2;
        
        long long person = 0;
        for(int i = 0; i < times.size() && person <= n; ++i) {
            person += mid_time / times[i]; // i 심사관이 특정 시간동안 처리할 수 있는 사람 수
        }
        
        // n명보다 많이 심사한 경우: 시간이 많이 남음
        // n명만큼 심사했더라도 시간이 남았을 수 있음
        if(person >= n) {
            answer = mid_time;
            max_time = mid_time - 1;
        }
        // n명 미만 심사한 경우: 시간이 부족함
        else {
            min_time = mid_time + 1;
        }
    }
    
    return answer;
}