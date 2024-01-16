#include <stdio.h>

#define MAX_SIZE 9

int main()
{
	int i, n, num, cnt;
	int usableCnt[MAX_SIZE] = {0, }; // 0 ~ 8: 9와 6은 같은 숫자로 취급

	scanf("%d", &n);

	cnt = 0;
	while(n){
		if((num = n % 10) == 9)
			num = 6;


		// 더 이상 사용 할 수 있는 숫자가 없으면 세트 추가
		if(!usableCnt[num]){
			++cnt;

			for(i = 0; i < MAX_SIZE; i++)
				++usableCnt[i];
			++usableCnt[6];
		}
		--usableCnt[num];

		n /= 10;
	}
	
	printf("%d\n", cnt);

	return 0;
}