#include <stdio.h>

#define MAX_ELEMENT 100001
#define HEAP_EMPTY() (!heapSize)

void push(int x);
int pop();

int heap[MAX_ELEMENT];
int heapSize;

int main()
{
    int n, x;

    scanf("%d", &n);

    while(n--){
        scanf("%d", &x);

        // 0이 입력되었을 때, 배열에서 가장 큰 값 출력 및 해당 값을 배열에서 제거
        if(!x)
            printf("%d\n", pop());
        else
            push(x);
    }

    return 0;
}

void push(int x)
{
    int i;

    i = ++heapSize;
    while((i != 1) && (x > heap[i / 2])){
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = x;

    return;
}

int pop()
{
    int parent, child;
    int x, temp;

    if(HEAP_EMPTY())
        return 0;
    
    x = heap[1];
    temp = heap[heapSize--];

    parent = 1;
    child = 2;

    while(child <= heapSize){
        if(child < heapSize && heap[child] < heap[child + 1])
            ++child;

        if(temp >= heap[child])
            break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;

    return x;
}