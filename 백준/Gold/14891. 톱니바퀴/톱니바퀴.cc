#include <iostream>

using namespace std;

int main() {
    int gear[5][8];     // 각 톱니바퀴의 상태 (1~4)
    int gear_num[100];  // 회전시킨 톱니바퀴의 번호
    int gear_d[100];    // 톱니바퀴의 회전 방향
    int k;              // 회전 횟수
    

    for(int i = 1; i <= 4; ++i) {
        char s[9];
        scanf("%s", s);

        for(int j = 0; j < 8; ++j) {
            gear[i][j] = s[j] - '0';
        }
    }

    scanf("%d", &k);

    for(int i = 0; i < k; ++i) {
        scanf("%d %d", &gear_num[i], &gear_d[i]);
    }

    // ---------------------------------
    int tooth_top[5] = {0, };   // 각 톱니바퀴의 12시 방향의 톱니의 인덱스

    for(int i = 0; i < k; ++i) {
        int spin_d[5] = {0, };      // 각 톱니바퀴의 회전 방향
        int num = gear_num[i];
        int d = gear_d[i];

        spin_d[num] = d;

        // 회전시킨 톱니바퀴 기준 왼쪽 톱니바퀴들 중 회전하는 톱니 탐색
        for(int j = num - 1; j >= 1; --j) {
            int right_idx = (tooth_top[j + 1] + 6) % 8; // 오른쪽 톱니바퀴의 9시 방향 톱니의 인덱스
            int left_idx = (tooth_top[j] + 2) % 8;      // 왼쪽 톱니바퀴의 3시 방향 톱니의 인덱스

            if(gear[j + 1][right_idx] == gear[j][left_idx]) {
                break;
            }

            spin_d[j] = -spin_d[j + 1];
        }

        // 회전시킨 톱니바퀴 기준 오른쪽 톱니바퀴들 회전하는 톱니 탐색
        for(int j = num + 1; j <= 4; ++j) {
            int right_idx = (tooth_top[j] + 6) % 8;     // 오른쪽 톱니바퀴의 9시 방향 톱니의 인덱스
            int left_idx = (tooth_top[j - 1] + 2) % 8;  // 왼쪽 톱니바퀴의 3시 방향 톱니의 인덱스

            if(gear[j][right_idx] == gear[j - 1][left_idx]) {
                break;
            }

            spin_d[j] = -spin_d[j - 1];
        }

        // 회전하는 톱니들의 12시 방향 톱니의 인덱스 변경
        for(int j = 1; j <= 4; ++j) {
            tooth_top[j] = (tooth_top[j] - spin_d[j] + 8) % 8;
        }
    }

    int ans = 0;
    for(int i = 1, score = 1; i <= 4; ++i, score *= 2) {
        ans += (gear[i][tooth_top[i]] == 1) ? score : 0;
    }

    cout << ans << endl;

    return 0;
}