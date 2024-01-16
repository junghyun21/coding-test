#include <stdio.h>
#include <stdlib.h>

void heapSort(int *, int);
void heapify(int *, int, int);
void swap(int *, int *);

int main()
{
	int i, j, res, n, x, cnt = 0;
	int *a;

	scanf("%d", &n);
	
	a = (int *)malloc(n * sizeof(int));

	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);

	scanf("%d", &x);

	heapSort(a, n); // 오름차순 정렬

	i = 0;
	j = n - 1;
	while(i < j){
		if((res = a[i] + a[j]) > x){
			--j;
		}
		else if(res == x){
			++cnt;
			++i;
			--j;
		}
		else{
			++i;
		}
	}
	
	printf("%d\n", cnt);

	return 0;
}

// 힙 정렬
void heapSort(int *a, int n)
{
	int i;

	// 최대 힙 구성
	// i: 배열의 중간 지점 (배열의 인덱스는 0부터 시작하기 때문에 n / 2 - 1)
	for(i = (n / 2) - 1; i >= 0; i--)
		heapify(a, n, i);

	// 힙에서 하나씩 꺼내어 정렬
    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]); // 최대(또는 최소) 원소를 배열 끝으로 이동
        heapify(a, i, 0); // 줄어든 힙에 대해 다시 최대 힙 구성
    }
	
}

// 최대 힙 구성
void heapify(int *a, int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 왼쪽 자식이 루트보다 크면 largest 업데이트
    if (left < n && a[left] > a[largest]){
        largest = left;
    }

    // 오른쪽 자식이 루트보다 크면 largest 업데이트
    if (right < n && a[right] > a[largest]){
        largest = right;
    }

    // largest가 루트가 아니면 루트와 largest 원소 교환 후 재귀 호출
    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

// 배열의 두 원소를 교환하는 함수
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}