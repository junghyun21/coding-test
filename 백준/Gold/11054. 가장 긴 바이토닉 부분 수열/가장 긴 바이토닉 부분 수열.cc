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

    // 증가 수열 개수 카운트
    vector<int> incre(N);
    for(int i = 0; i < N; ++i) {
        for(int j = i - 1; j >= 0; --j) {
            if(A[i] > A[j]) {
                incre[i] = max(incre[i], incre[j] + 1);
            }
        }
    }

    // 감소 수열 개수 카운트
    vector<int> decre(N);
    for(int i = N - 1; i >= 0; --i) {
        for(int j = i + 1; j < N; ++j) {
            if(A[i] > A[j]) {
                decre[i] = max(decre[i], decre[j] + 1);
            }
        }
    }

    // 부분 수열 개수 카운트
    int answer = 0;
    for(int i = 0; i < N; ++i) {
        answer = max(answer, incre[i] + decre[i] + 1);
    }

    cout << answer << endl;

    return 0;
}