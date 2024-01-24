#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, top = -1;
    int isVaild = 1;
    char parenthesis;

    scanf("%d", &n);

    while(getchar() != '\n');

    while(n){
        parenthesis = getchar();
        switch (parenthesis){
            case '(':
                ++top;
                break;

            case ')':
                if(--top < -1)
                    isVaild = 0;
                break;

            case '\n':
                --n;
                if(isVaild && top == -1)
                    printf("YES\n");
                else{
                    printf("NO\n");
                    top = -1;
                    isVaild = 1;
                }
                break;

            default:
                fprintf(stderr, "잘못된 문자 입력\n");
                exit(1);
        
        }
    }

    return 0;
}