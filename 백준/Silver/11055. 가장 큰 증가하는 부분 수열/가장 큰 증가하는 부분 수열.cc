#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> A(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    vector<int> DP(N);
    for(int i = 0; i < N; ++i) {
        DP[i] = A[i];

        for(int j = i - 1; j >= 0; --j) {
            if(A[i] > A[j]) {
                DP[i] = max(DP[j] + A[i], DP[i]);
            }
        }
    }

    cout << *max_element(DP.begin(), DP.end()) << endl;

    return 0;
}