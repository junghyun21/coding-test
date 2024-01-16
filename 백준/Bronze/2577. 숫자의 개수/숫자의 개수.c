#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 10

int main()
{
	int i, a, b, c, res, num[MAX_SIZE] = {0, };

	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	res = a * b * c;

	// a, b, c는 모두 100보다 크기 때문에 맨 앞에 0이 올 수 없음
	while(res){
		++num[res % 10];
		res /= 10;
	}
	
	for(i = 0; i < MAX_SIZE; i++)
		printf("%d\n", num[i]);

	return 0;
}