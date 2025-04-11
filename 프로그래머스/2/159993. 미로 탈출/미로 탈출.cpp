#include <queue>
#include <tuple>
#include <vector>

using namespace std;

const int x[4] = {0, 0, 1, -1};
const int y[4] = {1, -1, 0, 0};

bool maze[102][102];

int bfs(const pair<int, int> &start, const pair<int, int> &target) {
    int distance = 0;
    bool isFind = false;
    bool visited[102][102] = {false};
    
    queue<pair<pair<int, int>, int>> q; // <x좌표, y좌표, 거리>
    q.push({start, 0});
    
    while(!q.empty()) {
        pair<int, int> curr = q.front().first;
        int d = q.front().second;
        q.pop();
        
        if(visited[curr.first][curr.second])
            continue;
        
        visited[curr.first][curr.second] = true;
        
        for(int i = 0; i < 4; ++i) {
            int newX = curr.first + x[i];
            int newY = curr.second + y[i];
            auto p = make_pair(newX, newY);
            
            if(p == target) {
                return d + 1;
            }
            
            if(maze[newX][newY] && !visited[newX][newY]) {
                q.push({p, d + 1});
            }
        }
    }
    
    return -1;
}

int solution(vector<string> maps) {
    pair<int, int> start;
    pair<int, int> laber;
    pair<int, int> end;
    
    for(int i = 0; i < maps.size(); ++i) {
        for(int j = 0; j < maps[i].size(); ++j) {
            switch(maps[i][j]) {
                case 'S':
                    start.first = i + 1;
                    start.second = j + 1;
                    maze[i + 1][j + 1] = true;
                    break;
                case 'E':
                    end.first = i + 1;
                    end.second = j + 1;
                    maze[i + 1][j + 1] = true;
                    break;
                case 'L':
                    laber.first = i + 1;
                    laber.second = j + 1;
                    maze[i + 1][j + 1] = true;
                    break;
                case 'O':
                    maze[i + 1][j + 1] = true;
            }
        }
    }
    
    int answer = 0;
    int temp;
    
    if((temp = bfs(start, laber)) == -1) {
        return -1;
    }
    else {
        answer += temp;
    }
       
   if((temp = bfs(laber, end)) == -1) {
        return -1;
    }
    else {
        answer += temp;
    }
    
    return answer;
}