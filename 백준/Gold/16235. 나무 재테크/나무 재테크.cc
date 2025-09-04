#include <iostream>
#include <vector>
#include <map>

using namespace std;

int get_meal(map<int, int> &trees, int old_meal);
void increase_age(map<int, int> &trees);
void grow_new_tree(vector<vector<map<int, int>>> &treeinfo);

int main() {
    vector<vector<int>> A;                  // 겨울에 추가할 양분의 양
    vector<vector<int>> meals;               // 양분의 양
    vector<vector<map<int, int>>> treeinfo; // 각 나무들의 개수와 나이 (key: 나무의 나이, value: 각 나이에 해당하는 나무 개수) 
    int N, M, K;
    int x, y, z;
    int ans;

    cin >> N >> M >> K;

    A.resize(N + 2, vector<int>(N + 2));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> A[i][j];
        }
    }
    
    treeinfo.resize(N + 2, vector<map<int, int>>(N + 2));
    for(int i = 0; i < M; ++i) {
        cin >> x >> y >> z;
        ++treeinfo[x][y][z];
    }
    
    meals.resize(N + 2, vector<int>(N + 2, 5));
    for(int i = 0 ; i < K; ++i) {
        for(int r = 1; r <= N; ++r) {
            for(int c = 1; c <= N; ++c) {
                int meal = get_meal(treeinfo[r][c], meals[r][c]);        
                meals[r][c] = meal + A[r][c];
                
                increase_age(treeinfo[r][c]);
            }
        }

        grow_new_tree(treeinfo);
    }

    ans = 0;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            for(const auto &tree : treeinfo[i][j]) {
                ans += tree.second;
            }
        }
    }

    cout << ans << endl;

    return 0;
}

int get_meal(map<int, int> &trees, int old_meal) {
    int new_meal = 0;

    for(auto &[age, cnt] : trees) {
        if(cnt == 0) {
            continue;
        }

        int survive = min(cnt, old_meal / age);
        int dead = cnt - survive;

        old_meal -= age * survive;
        new_meal += (age / 2) * dead;

        cnt = survive;
    }

    return new_meal + old_meal;
}

void increase_age(map<int, int> &trees) {
    map<int, int> temp;

    for(const auto &[age, cnt] : trees) {
        if(cnt > 0) {
            temp[age + 1] = cnt;
        }
    }

    trees.swap(temp);

    return;
}

void grow_new_tree(vector<vector<map<int, int>>> &treeinfo) {
    vector<vector<int>> new_tree(treeinfo.size(), vector<int>(treeinfo[0].size()));
    static const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dc[] = {-1, 0, 1, -1, 1, -1, 0 ,1};

    for(int i = 1; i < treeinfo.size() - 1; ++i) {
        for(int j = 1; j < treeinfo[i].size() - 1; ++j) {
            for(const auto &[age, cnt] : treeinfo[i][j]) {
                if(cnt == 0 || age % 5 != 0) {
                    continue;
                }

                for(int d = 0; d < 8; ++d) {
                    int new_r = i + dr[d];
                    int new_c = j + dc[d];

                    new_tree[new_r][new_c] += cnt;
                }
            }
        }
    }
    
    for(int i = 1; i < new_tree.size() - 1; ++i) {
        for(int j = 1; j < new_tree[i].size() - 1; ++j) {
            treeinfo[i][j][1] += new_tree[i][j];
        }
    }

    return;
}