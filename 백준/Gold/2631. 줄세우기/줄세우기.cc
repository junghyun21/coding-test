#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> num;
    int n;

    cin >> n;

    num.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> num[i];
    }

    vector<int> DP(n, 1);
    int max_cnt = DP[0];

    for(int i = 1; i < n; ++i) {
        int temp = 0;
        for(int j = i - 1; j >= 0; --j) {
            if(num[i] > num[j]) {
                temp = max(temp, DP[j]);
            }
        }
        DP[i] += temp;
        
        max_cnt = max(max_cnt, DP[i]);
    }

    cout << n - max_cnt << endl;

    return 0;
}