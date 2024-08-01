#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *dishes;
    int *sushis;
    int n, d, k, c;
    int newIdx, oldIdx;
    int max, cnt;
    int i;

    (void)scanf("%d %d %d %d\n", &n, &d, &k, &c);

    dishes = (int *)malloc(sizeof(int) * (n + 1));
    sushis = (int *)malloc(sizeof(int) * (d + 1));

    for(i = 1; i <= n; i++)
        scanf("%d", &dishes[i]);

    for(i = 1; i <= d; i++)
        sushis[i] = 0;

    for(i = 1, max = 0, cnt = 0; i < n + k; i++){
        oldIdx = i > k ? i - k : 0;
        if(i > n)
            newIdx = i % n;
        else
            newIdx = i;

        if(0 == sushis[dishes[newIdx]]++)
            cnt++;

        if(oldIdx && !(--sushis[dishes[oldIdx]]))
            cnt--;

        if(max <= cnt){
            max = cnt;
            
            if(!sushis[c])
                ++max;
        }
    }

    printf("%d\n", max);

    return 0;
}
