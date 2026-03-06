#include <iostream>
#include <vector>

using namespace std;

vector<int> city;

int find_root(int node) {
    if(city[node] != node) {
        city[node] = find_root(city[node]);
    }

    return city[node];
}

void link(int x, int y) {
    int xr = find_root(x);
    int yr = find_root(y);

    if(xr != yr) {
        city[yr] = xr;
    }
}

int main() {
    int N, M;

    cin >> N >> M;

    for(int i = 0; i < N; ++i) {
        city.push_back(i);
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            bool isLinked;

            cin >> isLinked;

            if(isLinked) {
                link(i, j);
            }
        }
    }

    vector<int> trip(M);
    for(int i = 0; i < M; ++i) {
        cin >> trip[i];
        --trip[i];
    }

    bool isPossible = true;
    int root = find_root(trip[0]);

    for(int i = 1; i < M; ++i) {
        if(root != find_root(trip[i])) {
            isPossible = false;
            break;
        }
    }
    
    if(isPossible) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}