#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, string> root;
unordered_map<string, int> f_cnt;

string find_root(string f) {
    if(root[f] == f) {
        return f;
    }

    root[f] = find_root(root[f]);

    return root[f];
}

void union_network(string f1, string f2) {
    if(root.find(f1) == root.end()) {
        root[f1] = f1;
        ++f_cnt[f1];
    }
    
    if(root.find(f2) == root.end()) {
        root[f2] = f2;
        ++f_cnt[f2];
    }

    string root1 = find_root(f1);
    string root2 = find_root(f2);

    if(root1 != root2) {
        f_cnt[root1] += f_cnt[root2];
        root[root2] = root1;
    }
}

int main() {
    vector<vector<int>> answer;
    int N; // 테스트 케이스 개수
    int F; // 친구 관계 수 (F < 100,000);

    cin >> N;

    answer.resize(N);

    for(int i = 0; i < N; ++i) {
        cin >> F;

        root.clear();
        f_cnt.clear();

        for(int j = 0; j < F; ++j) {
            string f1, f2;
            cin >> f1 >> f2;

            union_network(f1, f2);
            
            answer[i].push_back(f_cnt[find_root(f1)]);
        }
    }

    for(int i = 0; i < answer.size(); ++i) {
        for(int j = 0; j < answer[i].size(); ++j) {
            cout << answer[i][j] << endl;
        }
    }

    return 0;
}