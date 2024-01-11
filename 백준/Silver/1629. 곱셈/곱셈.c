#include <stdio.h>

int square(int a, int b, int c);

int main()
{
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    printf("%d\n", square(a % c, b, c));

    return 0;
}

int square(int a, int b, int c)
{
    if(b == 0)
        return 1;
    else if(b == 1) 
        return a;
    else{
        unsigned long long result = square(a, b / 2, c);

        // 홀수: a^b = a^(b/2) * a^(b/2 + 1)
        if(b % 2)
            return a * (result * result % c) % c;
        // 짝수: a^b = a^(b/2) * a^(b/2)
        else
            return result * result % c;
    }
}