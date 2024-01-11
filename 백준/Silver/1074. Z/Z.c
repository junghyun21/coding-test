#include <stdio.h>
#include <stdlib.h>

// 이차원 배열을 만들어 순서를 저장해주는 방식은 메모리 초과
// 배열을 만들지 말고 순서만 따져보자
// 배열을 4등분함으로써 해당 문제 해결
int getOrder(int, int, int, int);

int main()
{
    int n, r, c;
    int size;
    int order;

    scanf("%d %d %d", &n, &r, &c);

    size = 1 << n;
    order = 0;

    printf("%d\n", getOrder(size / 2, r, c, order));

    return 0;
}

int getOrder(int size, int r, int c, int order)
{
    if(size > 0){

        // 상단
        if(size > r){
            // 좌측
            if(size > c)
                ;
            // 우측
            else{
                order += (size * size);

                c -= size;
            }
        }
        // 하단
        else{
            // 좌측
            if(size > c){
                order += (2 * (size * size));

                r -= size;
            }
            // 우측
            else{
                order += (3 * (size * size));

                c -= size;
                r -= size;
            }
        }

        return getOrder(size / 2, r, c, order);
    }

    return order;
}