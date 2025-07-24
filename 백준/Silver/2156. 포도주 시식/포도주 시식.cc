#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int ONE_DRINK = 0;
constexpr int TWO_DRINK = 1;
constexpr int NO_DRINK = 2;

int main() {
    int N;
    cin >> N;

    vector<int> drinks(N);
    for(int i = 0; i < N; ++i) {
        cin >> drinks[i];
    }

    vector<vector<int>> sum(3, vector<int>(N)); // 0행: 연속하지 않게 마심, 1행: 연속하게 마심, 2행: 마시지 않음
    sum[ONE_DRINK][0] = drinks[0];
    sum[TWO_DRINK][0] = drinks[0];
    sum[NO_DRINK][0] = 0;

    int ans = drinks[0];

    for(int i = 1; i < N; ++i) {
        if(i < 2) {
            sum[ONE_DRINK][i] = drinks[i];
            sum[TWO_DRINK][i] = drinks[i - 1] + drinks[i];
            sum[NO_DRINK][i] = max(sum[ONE_DRINK][i - 1], sum[TWO_DRINK][i - 1]);
        }
        else {
            sum[ONE_DRINK][i] = drinks[i] + sum[NO_DRINK][i - 1];
            sum[TWO_DRINK][i] = drinks[i] + drinks[i - 1] + sum[NO_DRINK][i - 2];
            sum[NO_DRINK][i] = max(sum[NO_DRINK][i - 1], max(sum[ONE_DRINK][i - 1], sum[TWO_DRINK][i - 1]));
        }

        ans = max(ans, max(sum[NO_DRINK][i], max(sum[ONE_DRINK][i], sum[TWO_DRINK][i])));
    }

    cout << ans << endl;

    return 0;
}