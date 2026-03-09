#include <iostream>
#include <vector>

using namespace std;

vector<int> parents;
vector<int> rankData;

bool unionSet(int x, int y);
int find(int x);

int main() {
    vector<pair<int, int>> line;
    int res = 0;
    int n, m;
    
    cin >> n >> m;

    line.resize(m);

    for(int i = 0; i < m; ++i) {
        cin >> line[i].first >> line[i].second;
    }

    parents.resize(n);
    rankData.resize(n, 0);

    for(int i = 0; i < n; ++i) {
        parents[i] = i;
    }

    for(int i = 0; i < m; ++i) {
        if(unionSet(line[i].first, line[i].second) == false) {
            res = i + 1;
            break;
        }
    }

    cout << res << endl;

    return 0;
}

bool unionSet(int x, int y) {
    int root1 = find(x);
    int root2 = find(y);

    if(root1 == root2) {
        return false;
    }

    if(rankData[root1] < rankData[root2]) {
        parents[root1] = root2;
    }
    else if(rankData[root1] > rankData[root2]) {
        parents[root2] = root1;
    }
    else {
        parents[root2] = root1;
        ++rankData[root1];
    }

    return true;
}

int find(int x) {
    if(parents[x] != x) {
        parents[x] = find(parents[x]);
    }

    return parents[x];
}