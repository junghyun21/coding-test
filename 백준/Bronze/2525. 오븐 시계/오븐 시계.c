#include <stdio.h>

int main()
{
    int hour, min;
    int time;

    scanf("%d %d", &hour, &min);
    scanf("%d", &time);

    hour += (time / 60);
    min += (time % 60);

    if(min >= 60){
        min -= 60;
        ++hour;
    }
    if(hour >= 24){
        hour = hour % 24;
    }

    printf("%d %d\n", hour, min);

    return 0;
}   