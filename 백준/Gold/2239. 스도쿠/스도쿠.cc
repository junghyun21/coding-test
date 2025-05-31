#include <iostream>
#include <string>

using namespace std;

const int SIZE = 9;

string board[SIZE];

bool is_possible(int c, int r, char num) {
    // 동일 행, 열
    for(int i = 0; i < SIZE; ++i) {
        if(board[c][i] == num || board[i][r] == num)
            return false;
    }

    // 3*3 크기의 사각형
    int start_c = (c / 3) * 3;
    int start_r = (r / 3) * 3;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(board[start_c + i][start_r + j] == num)
                return false;
        }
    }
    
    return true;
}

bool dfs(int idx) {
    if(idx == SIZE * SIZE)
        return true;

    int c = idx / SIZE;
    int r = idx % SIZE;

    if(board[c][r] == '0') {
        // cout << "[" << c  << "]" << "[" << r << "] " << board[c][r] << endl;
        for(char num = '1'; num <= '9'; ++num) {
            if(is_possible(c, r, num)) {
                board[c][r] = num;

                if(dfs(idx + 1))
                    return true;
            }

        }

        board[c][r] = '0';
    }
    else {
        // cout << "[" << c  << "]" << "[" << r << "] " << board[c][r] << endl;
        char num = board[c][r];

        board[c][r] = '0';
        if(is_possible(c, r, num)) {
            board[c][r] = num;

            if(dfs(idx + 1))
                return true;
        }
    }

    return false;
}

int main() {
    for(int i = 0; i < SIZE; ++i) {
        getline(cin, board[i]);
    }

    dfs(0);

    for(int i = 0; i < SIZE; ++i) {
        cout << board[i] << endl;
    }

    return 0;
}