#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    vector<int> tops(board[0].size(), board.size()); // board의 각 열의 top(인덱스)을 저장할 배열
    
    // tops 배열 초기화
    for(int r = 0; r < board.size(); ++r) {       
        for(int c = 0; c < board[r].size(); ++c) {
            // 위의 행(r-1)에 인형이 없던 경우 && 현재 뽑기 칸(board[r][c])에 인형이 있는 경우
            // tops의 값은 현재 행(r)으로 지정
            if(tops[c] == board.size() && board[r][c] != 0)
                tops[c] = r;
        }
    }
    
    stack<int> stk; // 인형 바구니
    int answer = 0; // 터트려져 사라진 인형의 개수
    
    for(const int &m : moves) {
        int col = m - 1;
        int row = tops[col];
        
        if(row == board.size()) continue; // 해당 열에 인형이 없는 경우 -> 아무런 일도 발생하지 않음
        else ++tops[col];                 // 해당 열에 인형이 있는 경우 -> top 위치 변경
        
        if(stk.empty() || board[row][col] != stk.top()) {
            stk.push(board[row][col]);
        }
        else {
            answer += 2; // pop은 한 번 발생하지만, 인형은 두 개 사라짐
            stk.pop();
        }    
    }
    
    return answer;
}