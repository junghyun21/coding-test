#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

const int INF = numeric_limits<int>::max();

int main()
{
    // 용액의 수
    int N; 
    cin >> N;

    // 용액의 특성값
    vector<int> aqSol(N);
    for(int i = 0; i < N; ++i) {
        cin >> aqSol[i];
    }

    int min = INF;
    vector<int> answer;

    // 양 끝의 합이 양수이면 양수의 값을 줄이고, 음수이면 음수의 값을 줄임
    int front = 0;
    int back = N - 1;
    while(front < back) {
        int tmp = aqSol[front] + aqSol[back];
        if(abs(tmp) < min) {
            answer.assign({aqSol[front], aqSol[back]});
            min = abs(tmp);
        }

        if(tmp > 0) {
            --back;
        }
        else {
            ++front;
        }
    }

    cout << answer[0] << " " << answer[1] << endl;

    return 0;
}