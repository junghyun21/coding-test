#include <vector>
#include <queue>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

struct Point {
    int x, y, time;
};

int solution(vector<vector<int>> maps)
{
    vector<vector<bool>> road(maps.size() + 2, vector<bool>(maps[0].size() + 2, false));
    for(int i = 0; i < maps.size(); ++i) {
        for(int j = 0; j < maps[0].size(); ++j) {
            road[i + 1][j + 1] = maps[i][j];
        }
    }
    
    pair<int, int> end = {maps.size(), maps[0].size()};
    
    queue<Point> q;
    q.push({1, 1, 1});
    
    while(!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        if(!road[curr.x][curr.y])
            continue;
        
        road[curr.x][curr.y] = false;
        
        for(int i = 0; i < 4; ++i) {
            int go_x = dx[i] + curr.x;
            int go_y = dy[i] + curr.y;;
            
            if(end == pair<int, int>(go_x, go_y)) {
                return curr.time + 1;
            }
            
            if(road[go_x][go_y]) {
                q.push({go_x, go_y, curr.time + 1});
            }
        }
    }
    
    return -1;
}