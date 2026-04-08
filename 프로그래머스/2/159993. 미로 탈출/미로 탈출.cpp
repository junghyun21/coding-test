#include <string>
#include <vector>
#include <queue>

using namespace std;

const int dr[] = {0, 0, -1, 1};
const int dc[] = {-1, 1, 0, 0};

struct node {
    int r;
    int c;
    int time;
};

int bfs(const vector<string> &maps, const pair<int, int> &start, const char &end) {
    vector<vector<bool>> visited(maps.size(), vector<bool>(maps[0].size(), false));
    queue<node> q;
    
    q.push({start.first, start.second, 0});
    visited[start.first][start.second] = true;
    
    while(!q.empty()) {
        int curR = q.front().r;
        int curC = q.front().c;
        int curTime = q.front().time;
        q.pop();
        
        for(int i = 0; i < 4; ++i) {
            int newR = curR + dr[i];
            int newC = curC + dc[i];
            
            if(maps[newR][newC] == end) {
                return curTime + 1;
            }
            
            if(!visited[newR][newC] && maps[newR][newC] != 'X') {
                q.push({newR, newC, curTime + 1});
                visited[newR][newC] = true;
            }
        }
    }
    
    return -1;
}

int solution(vector<string> maps) {
    vector<string> new_maps(maps.size() + 2, string(maps[0].size() + 2, 'X'));
    pair<int, int> start;
    pair<int, int> laber;
    pair<int, int> end;
    
    for(int i = 0; i < maps.size(); ++i) {
        for(int j = 0; j < maps[i].size(); ++j) {
            if(maps[i][j] == 'S') {
                start = {i + 1, j + 1};
            }
            else if(maps[i][j] == 'L') {
                laber = {i + 1, j + 1};
            }
            new_maps[i + 1][j + 1] = maps[i][j];
        }
    }
    
    int StoL = bfs(new_maps, start, 'L');
    if(StoL == -1) {
        return -1;
    }
    
    int LtoO = bfs(new_maps, laber, 'E');
    if(LtoO == -1) {
        return -1;
    }

    return StoL + LtoO;
}