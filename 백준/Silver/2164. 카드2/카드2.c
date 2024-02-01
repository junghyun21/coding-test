#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, cardNum;
    int *card;
    int front = -1;
    int rear = -1;

    scanf("%d", &n);

    card = (int *)malloc(sizeof(int) * n + 1);

    // 큐에 카드들 삽입
    for(i = 0; i < n; i++)
        card[++rear] = i + 1;

    cardNum = n; // 첫번째에 마지막 카드 번호는 입력받은 N
    while(1){
        // 카드 삭제
        front = (front + 1) % n;
        if(front == rear){
            cardNum = card[front];
            break;
        }

        // 카드 삭제 후 뒤로 보내기
        front = (front + 1) % n;
        if(front == rear){
            cardNum = card[front];
            break;
        }
        else{
            rear = (rear + 1) % n;
            card[rear] = card[front];
        }
    }

    printf("%d\n", cardNum);

    return 0;
}