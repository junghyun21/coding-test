#include <stdio.h>

typedef struct{
    int x;
    int y;
}Point;

Point hilbertCurve(int n, int m, unsigned char dir);

int main()
{
    Point p; // 좌표(x, y)
    int n, m; // n: 한 변의 길이(n = 2^k), m: 걸어온 미터 스텝 수
    
    scanf("%d %d", &n, &m);

    // 계산을 편하게 하기 위해 1부터가 아닌 0부터 시작한다고 가정
    // 따라서 문제에서 m = 1은 코드 상에서는 m = 0을 의미함으로 m-1값으로 계산 진행
    // 0xE4 == 0b 11 10 01 00
    p = hilbertCurve(n / 2, m - 1, 0xE4);

    printf("%d %d\n", p.x, p.y);

    return 0;
}

Point hilbertCurve(int n, int m, unsigned char dir)
{
    Point p;

    // 더 이상 사등분이 안될 때
    if(n == 0){
        // (1, 1)
        p.x = 1;
        p.y = 1;
    }
    else{
        int order; // 4등분 했을 때, 찾고자 하는 좌표가 위치하는 곳의 부분을 몇 번째로 지나가는가 (0 ~ 3)
        unsigned char position; // 찾고자 하는 좌표가 4등분 중 어디에 위치하는가 (좌측 하단: 0, 좌측 상단: 1, 우측 상단: 2, 우측 하단 3)
        unsigned char changeDir;

        order = m / (n * n);
        changeDir = dir;

        // 찾고자 하는 좌표의 위치에 따라 컵의 진행 방향 변경
        // 4등분을 한 상태에서 어디 사분면에 위치하느냐에 따라 진행 방향이 변경됨
        // 맨 처음의 진행 방향: 좌측 하단(0) -> 좌측 상단(1) -> 우측 상단(2) -> 우측 하단(3); 0b 11 10 01 00
        // 진행 순서에 따라 dir 내부의 비트 변경
        switch (order){
            // 좌표가 좌측 하단(0)에 위치한 경우
            // 두번째와 네번째 순서 변경
            // 맨 처음 기준 변경될 진행 방향: 0b 01 10 11 00 
            case 0:
                changeDir &= 0x33; // 0b 0011 0011, 첫번째 세번째 순서 그대로 가져옴 (00 10 00 00)
                changeDir |= ((dir & 0x0C) << 4); // 0b 0000 1100, 두번째 순서를 네번째 순서로 보냄 (01 10 00 00)
                changeDir |= ((dir & 0xC0) >> 4); // 0b 1100 0000, 네번째 순서를 두번째 순서로 보냄 (01 10 11 00)
                break;

            // 좌표가 우측 하단(3)에 위치한 경우
            // 첫번째와 세번째 순서 변경
            // 맨 처음 기준 병경될 진행 방향: 0b 11 00 01 10
            case 3:
                changeDir &= 0xCC; // 0b 1100 1100, 두번째 네번째 순서 그대로 가져옴 (11 00 01 00)
                changeDir |= ((dir & 0x03) << 4); // 0b 0000 0011, 첫번째 순서를 세번째 순서로 보냄 (11 00 01 00)
                changeDir |= ((dir & 0x30) >> 4); // 0b 0011 0000, 세번째 순서를 첫번째 순서로 보냄 (11 00 01 10)
                break;

            // 좌표가 좌측 상단(1) 혹은 우측 상단(2)에 위치한 경우
            // 기존의 방향과 동일
            default:
                break;
        }

        p = hilbertCurve(n / 2, m % (n * n), changeDir);

        // 4등분 중 어디에 속하는지 확인
        position = dir & (0x03 << (2 * order));
        position >>= (2 * order);        

        // 4등분 중 어디에 속하느냐에 따라 좌표 값이 달라짐
        // n은 4등분한 한 변의 길이
        switch (position){
            // 좌측 하단에 있는 경우
            // (x, y)
            // 0b00
            case 0x00:
                // printf("[n = %d] 좌측 하단: (%d, %d)\n", n, p.x, p.y);
                break;

            // 좌측 상단에 있는 경우
            // (x, y + n)
            // 0b01
            case 0x01:
                //printf("[n = %d] 좌측 상단: (%d, %d)\n", n, p.x, p.y);
                p.y += n;
                break;

            // 우측 상단에 있는 경우
            // (x + n, y + n)
            // 0b10
            case 0x02:
                // printf("[n = %d] 우측 상단: (%d, %d)\n", n, p.x, p.y);
                p.x += n;
                p.y += n;
                break;

            // 우측 하단에 있는 경우
            // (x + n, y)
            // 0b11
            case 0x03:
                // printf("[n = %d] 우측 하단: (%d, %d)\n", n, p.x, p.y);
                p.x += n;
                break;
        }
    }

    return p;
}
