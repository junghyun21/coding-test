// 입력된 문자열의 추가 및 삭제가 빈번히 발생
// 따라서 배열보다 연결 리스트에 값을 저장하고 관리하는 것이 더 효율적
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100001

typedef struct Node{
	char alphabet;
	struct Node *front;
	struct Node *back;
}Node;

typedef struct Header{
	Node *cursor;
	Node *head;
}Header;

void init(Header *list); // 헤더 노드 초기화 (연결 리스트 생성)
void insertNodeCursor(Header *list, char alphabet); // 커서 위치에 문자(노드) 추가
void deleteNodeCursor(Header *list); // 커서 왼쪽에 있는 문자 삭제
void printString(Header *list); // 연결 리스트에 저장된 문자열 출력

int main()
{
	Header list;
	char string[MAX_SIZE];
	char ch;
	int num, i;

	// 리스트 생성 및 초기화
	init(&list);

	// 문자열(string)과 입력할 명령어의 개수(num) 입력
	scanf("%s", string);
	scanf("%d", &num);

	// 입력받은 문자열을 연결 리스트에 저장
	for(i = 0; string[i]; i++)
		insertNodeCursor(&list, string[i]);

	// 명령어를 입력 받고 해당하는 명령어 수행
	while(num--){
		getchar();
		scanf("%c", &ch);

		switch (ch)
		{
			// 커서를 왼쪽으로 한 칸 옮김 (커서가 문장의 맨 앞이면 무시)
			case 'L':
				if(list.cursor->front)
					list.cursor = list.cursor->front;
				break;

			// 커서를 오른쪽으로 한 칸 옮김 (커서가 문장의 맨 뒤면 무시)
			case 'D':
				if(list.cursor->back)
					list.cursor = list.cursor->back;
				break;

			// 커서 왼쪽에 있는 문자 삭제 (커서가 문장의 맨 앞이면 무시)
			case 'B':
				if(list.cursor->front)
					deleteNodeCursor(&list);
				break;

			// 뒤에 같이 입력된 문자를 커서 왼쪽에 추가
			case 'P':
				getchar();
				scanf(" %c", &ch);
				insertNodeCursor(&list, ch);	
		}
	}

	printString(&list);

	return 0;
}

void init(Header *list)
{
	// 더미 노드
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->front = NULL;
	newNode->back = NULL;

	list->head = list->cursor= newNode;
}

void insertNodeCursor(Header *list, char alphabet)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->alphabet = alphabet;

	newNode->front = list->cursor;
	newNode->back = list->cursor->back;

	if(list->cursor->back != NULL)
		list->cursor->back->front = newNode;
	list->cursor->back = newNode;

	list->cursor = newNode;
}

void deleteNodeCursor(Header *list)
{
	Node *temp = list->cursor;

	list->cursor = temp->front;

	// 맨 앞에 더미노드가 있기 때문에 삭제할 노드가 tail인 경우만 예외처리하면 됨
	temp->front->back = temp->back;
	if(temp->back)
		temp->back->front = temp->front;

	free(temp);
}

void printString(Header *list)
{
	Node *temp = list->head->back;

	while(temp != NULL){
		printf("%c", temp->alphabet);
		temp = temp->back;
	}
	printf("\n");
}