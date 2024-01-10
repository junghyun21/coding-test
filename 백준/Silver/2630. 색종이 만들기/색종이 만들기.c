#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void cutPaper(int *, int, bool **);
void copyArray(bool **, bool **, int, int, int);

int main()
{
    bool **isBlue;
    int cnt[2] = {0, }; // cnt[0]: 하얀색 종이의 개수, cnt[1]: 파란색 종이의 개수
    int n; // 한 변의 길이(n) = 2^k
    int color;

    scanf("%d", &n);

    // isBlue[n][n] == isBlue[2^k][2^k]
    isBlue = (bool **)malloc(n * sizeof(bool *));
    for(int i = 0; i < n; i++)
        isBlue[i] = (bool *)malloc(n * sizeof(bool));

    // 색종이의 색깔 입력 받음
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &color);

            isBlue[i][j] = (color == 1);
        }
    }

    cutPaper(cnt, n, isBlue);

    printf("%d\n%d\n", cnt[0], cnt[1]);

    // 할당된 메모리 해제
    for (int i = 0; i < n; i++) {
        free(isBlue[i]);
    }
    free(isBlue);


    return 0;
}

void cutPaper(int *cnt, int n, bool **isBlue)
{
    if(n > 0){
        bool **isBlueRecursion;
        bool isDifferent = false;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(isBlue[0][0] != isBlue[i][j]){
                    isDifferent = true;
                    break;
                }
            }

            if(isDifferent)
                break;
        }

        // 같은 색만 있는 경우 재귀 종료
        if(!isDifferent){
            if(isBlue[0][0])
                cnt[1]++;
            else
                cnt[0]++;

            return;
        }

        isBlueRecursion = (bool **)malloc(n * sizeof(bool *));
        for(int i = 0; i < n; i++)
           isBlueRecursion[i] = (bool *)malloc(n * sizeof(bool));

        // 좌측 상단
        copyArray(isBlue, isBlueRecursion, n / 2, 0, 0);
        cutPaper(cnt, n / 2, isBlueRecursion);

        // 우측 상단
        copyArray(isBlue, isBlueRecursion, n / 2, 0, n / 2);
        cutPaper(cnt, n / 2, isBlueRecursion);

        // 좌측 하단
        copyArray(isBlue, isBlueRecursion, n / 2, n / 2, 0);
        cutPaper(cnt, n / 2, isBlueRecursion);

        // 우측 하단
        copyArray(isBlue, isBlueRecursion, n / 2, n / 2, n / 2);
        cutPaper(cnt, n / 2, isBlueRecursion);
    }

    return;
}

void copyArray(bool **source, bool **destination, int size, int startRow, int startCol){
    for(int i = 0, k = startRow; i < size; i++, k++)
        for(int j = 0, l = startCol; j < size; j++, l++)
            destination[i][j] = source[k][l];

    return;
}