#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void zip(char **, int, int, int, int, int);

int main()
{
    char **image;
    int n;

    scanf("%d", &n);

    image = (char **)malloc(n * sizeof(char *));
    for(int i = 0; i < n; i++)
        image[i] = (char *)malloc((n + 1) * sizeof(char));

    for(int i = 0; i < n; i++)
        scanf("%s", image[i]);
    
    zip(image, n, 0, 0, n, n);
    printf("\n");

    return 0;
}

void zip(char **image, int n, int startRow, int startCol, int endRow, int endCol)
{
    if(n > 0){
        bool isDifferent = false;

        for(int i = startRow; i < endRow; i++){
            for(int j = startCol; j < endCol; j++){
                if(image[startRow][startCol] != image[i][j]){
                    isDifferent = true;
                    break;
                }
            }

            if(isDifferent)
                break;
        }

        if(!isDifferent){
            if(image[startRow][startCol] == '0')
                printf("0");
            else    
                printf("1");
        }
        else{
            n /= 2;

            printf("(");

            zip(image, n, startRow, startCol, endRow - n, endCol - n);
            zip(image, n, startRow, startCol + n, endRow - n, endCol);
            zip(image, n, startRow + n, startCol, endRow, endCol - n);
            zip(image, n, startRow + n, startCol + n, endRow, endCol);

            printf(")");
        }
    }

    return;
}