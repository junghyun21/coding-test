#include <iostream>
#include <vector>

using namespace std;

int binary_search(const vector<int> &LIS, const int &target)
{
    int start = 0;
    int end = LIS.size() - 1;

    while(start < end) {
        int mid = (start + end) / 2;

        if(LIS[mid] >= target) {
            end = mid;
        }
        else {
            start = mid + 1;
        }
    }

    return end;
}

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

    // LIS
    vector<int> LIS;
    LIS.push_back(nums[0]);
    for(int i = 1; i < A; ++i) {
        if(LIS.back() < nums[i]) {
            LIS.push_back(nums[i]);
        }
        else {
            int idx = binary_search(LIS, nums[i]);
            LIS[idx] = nums[i];
        }
    }

    cout << LIS.size() << endl;

    return 0;
}