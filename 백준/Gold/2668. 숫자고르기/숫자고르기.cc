#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 101;

int numbers[MAX_N];
bool visited[MAX_N];
bool finished[MAX_N];
int ans;

vector<int> set;

void dfs(int cur) {
    int next = numbers[cur];

    visited[cur] = true;

    if(!visited[next]) {
        dfs(next);
    }
    else if(!finished[next]) {
        for(int i = next; i != cur; i = numbers[i]) {
            set.push_back(i);
            ++ans;
        }
        set.push_back(cur);
        ++ans;
    }

    finished[cur] = true;

    return;
}

int main() {
    int N;
    cin >> N;

    for(int i = 1; i <= N; ++i) {
        cin >> numbers[i];
    }

    for(int i = 1; i <= N; ++i) {
        if(!visited[i]) {
            dfs(i);
        }
    }

    sort(set.begin(), set.end());

    cout << ans << endl;

    for(const int &s: set) {
        cout << s << endl;
    }

    return 0;
}