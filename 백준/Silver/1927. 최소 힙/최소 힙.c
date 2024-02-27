#include <stdio.h>

#define MAX_ELEMENT 100001
#define HEAP_EMPTY(n) (!n)

typedef struct HeapType{
    int element[MAX_ELEMENT];
    int heapSize;
}HeapType;

void init(HeapType *heap);
void push(HeapType *heap, int x);
int pop(HeapType *heap);

int main()
{
    HeapType heap;
    int n, x;

    scanf("%d", &n);

    init(&heap);

    while(n--){
        scanf("%d", &x);

        // 입력 받은 값이 0이라면, 배열에서 가장 작은 값을 출력하고 해당 값을 배열에서 제거
        if(!x)
            printf("%d\n", pop(&heap));
        else
            push(&heap, x);
    }

    return 0;
}

void init(HeapType *heap)
{
    heap->heapSize = 0;
    for(int i = 0; i < MAX_ELEMENT; i++)
        heap->element[i] = 0;
}

void push(HeapType *heap, int x)
{
    int i;

    i = ++(heap->heapSize);
    while((i != 1) && (x < heap->element[i / 2])){
        heap->element[i] = heap->element[i / 2];
        i /= 2;
    }
    heap->element[i] = x;
}

int pop(HeapType *heap)
{
    int parent, child;
    int x, temp;

    if(HEAP_EMPTY(heap->heapSize))
        return 0;

    x = heap->element[1];
    temp = heap->element[heap->heapSize--];

    parent = 1;
    child = 2;

    while(child <= heap->heapSize){
        if(child < heap->heapSize && heap->element[child] > heap->element[child + 1])
            ++child;

        if(temp <= heap->element[child])
            break;

        heap->element[parent] = heap->element[child];
        parent = child;
        child *= 2;
    }
    heap->element[parent] = temp;

    return x;
}