#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// 슈얼레이스(신발끈) 공식
// 1. 모든 정점을 순서대로 순회하며 ((x(i) - x(0)) * (y(i + 1) - y(0)) - (x(i + 1) - x(0)) * (y(i) - y(0))) 값을 더하기
// 2. 절대값을 취하기
// 3. 2로 나누기
double cal_area(vector<pair<int, int>> &point) {
    double res = 0;
    int size = point.size() - 1;
    double x1, x2, y1, y2;
    int i;

    for(i = 1; i < size; ++i) {
        x1 = point[i].first - point[0].first;
        y1 = point[i].second - point[0].second;
        x2 = point[i + 1].first - point[0].first;
        y2 = point[i + 1].second - point[0].second;

        res += x1 * y2 - x2 * y1;
    }

    return abs(res) / 2;
}

int main()
{
    vector<pair<int, int>> point;
    int N, x, y;
    cin >> N;

    while(N--) {
        cin >> x;
        cin >> y;
        point.push_back({x, y});
    }

    cout << fixed << setprecision(1) << cal_area(point) << endl;

    return 0;
}