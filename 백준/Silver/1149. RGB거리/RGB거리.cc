#include <iostream>
#include <vector>

using namespace std;

struct Color {
    int R;
    int G;
    int B;
};

int main()
{
    int N; // 집의 수
    cin >> N;
    
    vector<Color> price(N); // 집을 칠하는 비용
    for(int i = 0; i < N; ++i) {
        cin >> price[i].R >> price[i].G >> price[i].B;
    }

    vector<Color> sum(N); // 누적합
    sum[0].R = price[0].R;
    sum[0].G = price[0].G;
    sum[0].B = price[0].B;

    for(int i = 1; i < N; ++i) {
        sum[i].R = price[i].R + min(sum[i - 1].G, sum[i - 1].B); // R
        sum[i].G = price[i].G + min(sum[i - 1].R, sum[i - 1].B); // G
        sum[i].B = price[i].B + min(sum[i - 1].R, sum[i - 1].G); // B
    }

    cout << min(sum[N - 1].R, min(sum[N - 1].G, sum[N - 1].B)) << endl;

    return 0;
}