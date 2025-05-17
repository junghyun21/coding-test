#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1500002;
int T[MAX_N];
int P[MAX_N];
int MAX_P[MAX_N];

int main()
{
    int N;
    cin >> N;

    for(int i = 1; i <= N; ++i) {
        cin >> T[i] >> P[i];
    }

    for(int i = 1; i <= N; ++i) {
        int date = i + T[i];

        if(date <= N + 1) {
            MAX_P[date] = max(P[i] + MAX_P[i], MAX_P[date]);
        }
        
        MAX_P[i + 1] = max(MAX_P[i], MAX_P[i + 1]);
    }

    cout << MAX_P[N + 1] << endl;

    return 0;
}