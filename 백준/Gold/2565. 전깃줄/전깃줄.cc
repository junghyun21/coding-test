#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    map<int, int> line;
    vector<int> arrive;
    int N;
    int A;
    int B;

    cin >> N;

    for(int i = 0; i < N; ++i) {
        cin >> A >> B;
        line[A] = B;
    }

    for(const auto &l : line) {
        arrive.push_back(l.second);
    }

    // DP (LIS)
    // 도착지(B)에서 대소 관계가 바뀌면 교점이 존재 -> 최장 길이의 증가하는 수열을 찾자
    vector<int> DP(N);
    int max_cnt = 0;
    for(int i = 0; i < N; ++i) {
        DP[i] = 1;
        
        for(int j = i - 1; j >= 0; --j) {
            if(arrive[i] > arrive[j]) {
                DP[i] = max(DP[i], DP[j] + 1);
            }
        }

        max_cnt = max(max_cnt, DP[i]);
    }

    cout << N - max_cnt << endl;

    return 0;
}