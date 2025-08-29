#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

const int INF = numeric_limits<int>::max();

int cal(const vector<vector<int>> &dist, const vector<int> &selected) {
    int res = 0;

    for(int i = 0; i < dist[0].size(); ++i) {
        int temp = INF;

        for(const int &s : selected) {
            temp = min(temp, dist[s][i]);
        }

        res += temp;
    }
    
    return res;
}

void dfs(const vector<vector<int>> &dist, vector<int> selected, const int &M, int &ans, int idx) {
    if(dist.size() - idx < M - selected.size()) {
        return;
    }

    if(selected.size() == M) {
        ans = min(ans, cal(dist, selected));
        return;
    }

    // idx 선택
    selected.push_back(idx);
    dfs(dist, selected, M, ans, idx + 1);
    selected.pop_back();

    // idx 미선택
    dfs(dist, selected, M, ans, idx + 1);

    return;
}

int main() {
    vector<vector<int>> city;
    vector<vector<int>> distance;
    vector<pair<int, int>> store;
    vector<pair<int, int>> house;
    vector<int> selected;
    int N, M;
    int ans;
    
    cin >> N >> M;
    
    city.resize(N, vector<int>(N));
    
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> city[i][j];

            if(city[i][j] == 1) {
                house.push_back({i, j});
            }
            else if(city[i][j] == 2) {
                store.push_back({i, j});
            }
        }
    }
    //--------------------------------
    distance.resize(store.size(), vector<int>(house.size()));

    for(int i = 0; i < store.size(); ++i) {
        for(int j = 0; j < house.size(); ++j) {
            distance[i][j] = abs(store[i].first - house[j].first) + abs(store[i].second - house[j].second);
        }
    }

    ans = INF;
    dfs(distance, vector<int>{}, M, ans, 0);

    cout << ans << endl;

    return 0;
}