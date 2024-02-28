#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_ELEMENT 100001
#define HAEP_EMPTY(n) (!n)

typedef struct HeapType{
    int element[MAX_ELEMENT];
    int heapSize;
}HeapType;

HeapType *createHeap();
void push(HeapType *heap, int item);
int pop(HeapType *heap);

int main()
{
    HeapType *heap;
    int n, x;

    scanf("%d", &n);

    heap = createHeap();

    while(n--){
        scanf("%d", &x);

        if(!x)
            printf("%d\n", pop(heap));
        else
            push(heap, x);
    }

    free(heap);

    return 0;
}

HeapType *createHeap()
{
    HeapType *heap;
    
    heap = (HeapType *)malloc(sizeof(*heap));
    heap->heapSize = 0;

    return heap;
}

void push(HeapType *heap, int item)
{
    int i;

    i = ++(heap->heapSize);

    while(i != 1 && abs(item) <= abs(heap->element[i / 2])){
        if(abs(item) == abs(heap->element[i / 2]) && item >= heap->element[i / 2])
            break;

        heap->element[i] = heap->element[i / 2];
        i /= 2;
    }
    heap->element[i] = item;
}

int pop(HeapType *heap)
{
    int parent, child;
    int x, temp;

    if(HAEP_EMPTY(heap->heapSize))
        return 0;

    x = heap->element[1];
    temp = heap->element[heap->heapSize--];

    parent = 1;
    child = 2;

    while(child <= heap->heapSize){
        if(child < heap->heapSize && abs(heap->element[child]) >= abs(heap->element[child + 1])){
            ++child;

            if(abs(heap->element[child - 1]) == abs(heap->element[child]) && heap->element[child - 1] < heap->element[child])
                --child;
        }

        if(abs(temp) <= abs(heap->element[child])){
            if(abs(temp) == abs(heap->element[child])){
                if(temp <= heap->element[child])
                    break;
            }
            else
                break;
        }   

        heap->element[parent] = heap->element[child];
        parent = child;
        child *= 2;
    }
    heap->element[parent] = temp;

    return x;
}