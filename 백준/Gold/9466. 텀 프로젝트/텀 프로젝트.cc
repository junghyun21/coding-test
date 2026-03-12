#include <iostream>

using namespace std;

int students[100001];
bool visited[100001];
bool finish[100001];
int cnt;

void dfs(int cur) {
    int next = students[cur];
    
    visited[cur] = true;

    if(!visited[next]) {
        dfs(next);
    }
    else if(!finish[next]) {
        for(int i = next; i != cur; i = students[i]) {
            --cnt;
        }
        --cnt;
    }

    finish[cur] = true;

    return;
}

int main() {
    int tc, n;

    cin >> tc;

    while(tc--) {
        cin >> n;

        cnt = n;

        for(int i = 1; i <= n; ++i) {
            cin >> students[i];
            visited[i] = false;
            finish[i] = false;
        }

        for(int i = 1; i <= n; ++i) {
            if(!visited[i]) {
                dfs(i);
            }
        }

        cout << cnt << endl;
    }

    return 0;
}
