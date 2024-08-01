#include <stdio.h>
#include <stdbool.h>

int main()
{
	bool paper[100][100] = { 0, };
	int n;
	int x, y;
	int i, j;
	int sum = 0;

	(void)scanf("%d", &n);

	while (n--) {
		(void)scanf("%d %d", &x, &y);
		
		for (i = x; i < x + 10; i++) {
			for (j = y; j < y + 10; j++) {
				if (!paper[i][j]) {
					paper[i][j] = true;
					sum++;
				}
			}
		}

	}

	printf("%d\n", sum);

	return 0;
}