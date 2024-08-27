#include <stdio.h>
#include <string.h>

#define MAX (80 + 1)

int N; // 수열의 길이
char arr[MAX]; // 수열
int isFound;

void solve(int idx, int num);
void initUse();

int main()
{
    scanf("%d", &N);
    for(int i = 1; i <= 3 && !isFound; i++){
        solve(0, i);
    }

    printf("%s\n", arr);
    
    return 0;
}

void solve(int idx, int num)
{
    if(idx == N){
        isFound = 1;
        return;
    }

    arr[idx] = num + '0';
    for(int i = 0; i * 2 < idx; i++){
        if(!strncmp(arr + idx - (i * 2 + 1), arr + idx - i, i + 1)){
            arr[idx] = '\0';
            return;
        }
    }

    for(int i = 1; i <= 3 && !isFound; i++){
        solve(idx + 1, i);
    }
}