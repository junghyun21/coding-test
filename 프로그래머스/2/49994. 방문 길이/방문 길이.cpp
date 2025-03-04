#include <string>
#include <vector>
using namespace std;

constexpr int start_x = 5;
constexpr int start_y = 5;

enum Direct {U, D, L, R};

// isVisit[접근 방향][x좌표][y좌표]
// 접근 방향 -> 0: U, 1: D, 2: L, 3: R
int solution(string dirs) {
    vector<vector<vector<bool>>> isVisit(4, vector<vector<bool>>(11, vector<bool>(11)));
    int x = start_x;
    int y = start_y;
    int answer = 0;
    int d; // 접근 방향 인덱스
    
    for(const char &s : dirs) {
        if(s == 'U' && y < 10) {
            isVisit[U][x][y] = true; 
            ++y;
            d = D;
        }
        else if(s == 'D' && y > 0) {
            isVisit[D][x][y] = true; 
            --y;
            d = U;
        }
        else if(s == 'L' && x > 0) { 
            isVisit[L][x][y] = true; 
            --x;
            d = R;
        }
        else if(s == 'R' && x < 10) {
            isVisit[R][x][y] = true; 
            ++x;
            d = L;
        }
        
        if(!isVisit[d][x][y]) {
            ++answer;
            isVisit[d][x][y] = true;
        }     
    }
    
    return answer;
}