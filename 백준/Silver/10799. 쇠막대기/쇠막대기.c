#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 100000
#define OPEN '('
#define CLOSE ')'

int main()
{
    char temp[N + 2];
    bool wasClose;
    int top;
    int cnt;
    int i;

    fgets(temp, N + 2, stdin);
    //if(fgets(temp, N + 2, stdin) == NULL){
    //    fprintf(stderr, "fgets error\n");
    //    exit(1);
    //}

    for(i = 0, cnt = 0, top = 0, wasClose = false; temp[i] != '\n'; i++){
        if(temp[i] == OPEN){
            ++top;
            wasClose = false;
        }
        else if(temp[i] == CLOSE){
            --top;
            cnt += (wasClose) ? 1 : top;
            wasClose = true;
        }
        //else{
        //    fprintf(stderr, "wrong input\n");
        //    exit(1);
        //}
    }

    printf("%d\n", cnt);

    return 0;
}