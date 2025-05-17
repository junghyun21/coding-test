#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    // 수열의 크기
    int A;
    cin >> A;

    // 수열
    vector<int> nums(A);
    for(int i = 0; i < A; ++i) {
        cin >> nums[i];
    }

    // LIS 길이 구하기
    vector<int> dp(A, 1);
    for(int i = 1; i < A; ++i) {
        for(int j = 0; j < i; ++j) {
            if(nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;

    return 0;
}