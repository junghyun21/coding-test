#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void cutPaper(int **, int *, int);
void copyPaper(int **, int **, int, int, int);

int main()
{
    int n;
    int **paper;
    int cnt[3] = {0, }; // cnt[0]: -1, cnt[1]: 0, cnt[2]: 1

    scanf("%d", &n);

    paper = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++)
        paper[i] = (int *)malloc(n * sizeof(int));

    // 종이의 색깔 입력 받음
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &paper[i][j]);

    cutPaper(paper, cnt, n);

    for(int i = 0 ; i < 3; i++)
        printf("%d\n", cnt[i]);

    for(int i = 0; i < n; i++)
        free(paper[i]);
    free(paper);

    return 0;
}

void cutPaper(int **paper, int *cnt, int n)
{
    // 한 칸이면 해당 칸의 색에 따라 종이 개수 카운팅
    if(n > 0){
        int **copiedPaper;
        int size, i, j;
        bool isDifferent = false;

        // 색이 모두 같은 경우 종이 개수 카운팅
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++)
                if(paper[0][0] != paper[i][j]){
                    isDifferent = true;
                    break;
                }

            if(isDifferent)
                break;
        }    

        if(!isDifferent){
            switch (paper[0][0]){
                case -1:
                    ++cnt[0];
                    break;

                case 0:
                    ++cnt[1];
                    break;

                default:
                    ++cnt[2];
            }

            return;
        }

        size = n / 3;

        copiedPaper = (int **)malloc(size * sizeof(int *));
        for(i = 0; i < size; i++)
            copiedPaper[i] = (int *)malloc(size * sizeof(int));

        for(i = 0; i < n; i += size){
            for(j = 0; j < n; j += size){
                copyPaper(paper, copiedPaper, i, j, size);

                // printf("size: %d, startRow: %d, startCol: %d\n", size, i, j);
                // for(int k = 0; k < size; k++){
                //     for(int l = 0; l < size; l++)
                //         printf("%4d", copiedPaper[k][l]);
                //     printf("\n");
                // }

                cutPaper(copiedPaper, cnt, size);
            }
        }

        for(int i = 0; i < size; i++)
            free(copiedPaper[i]);
        free(copiedPaper);
    }

    return;
}

void copyPaper(int **paper, int **copiedPaper, int row, int col, int size)
{
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            copiedPaper[i][j] = paper[row + i][col + j];

    return;
}