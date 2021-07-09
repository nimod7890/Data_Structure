#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


typedef struct _NODE {
	char data;
	struct _NODE* next;
}NODE;
typedef struct _queue {
	NODE* front;
	NODE* rear;
	int len;
}QUEUE;

void screen() {
	printf("\n\n\t");
	printf("====================================================");
	printf("\n\n			    FUNCTION\n\t");
	printf("\n\t ****CAPITALIZE all the COMMANDSs\t");
	printf("\n\t ****Do not use space bar\n\t");
	printf("----------------------------------------------------");
	printf("\n\t + (data)		enqueue\n\t");
	printf(" = (data)		replace rear data\n\t");
	printf(" - (data)		dequeue\n\t");
	printf(" D			hide all data \n\t"); //창작기능
	printf(" R			reveal all data\n\t"); //창작기능
	printf(" L			print all data\n\t");
	printf(" E			is empty\n\t");
	printf(" C			be empty\n\t");
	printf(" F			is full\n\t");//연결리스트로 구현했기에 항상 false
	printf(" H			return ( front index, data ) \n\t");//연결리스트로 구현했기에 front 인덱스 항상 1
	printf(" T			return ( rear index, data ) \n\t");
	printf(" P			peek // return front data \n\t");
	printf(" #			all data count\n\t");
	printf(" @ (data)		a data count\n\t");//창작기능
	printf(" ? (data)		this data is member\n\t");
	printf(" B			***BOMB*** (force stop)\n\t"); //창작기능
	printf("----------------------------------------------------\n\t");
	printf(" Q			quit\n\t"); // 창작기능
	printf("====================================================");
}

void print(QUEUE* queue) {
	int mpty = is_empty(queue);
	if (mpty == TRUE) { printf("빈 큐입니다"); return; } //if empty
	NODE* crnt = queue->front;
	if (queue->len == 1) {
		printf("%c ", crnt->data);
		return;
	}
	while (crnt != NULL) {
		printf("%c ", crnt->data);
		crnt = crnt->next;
	}
}

void printL(QUEUE* queue) {
	int mpty = is_empty(queue);
	if (mpty == TRUE) { printf("\n\t빈 큐입니다"); return; } //if empty
	NODE* crnt = queue->front;
	printf("\n\tprint all data : ");
	if (queue->len == 1) {
		printf("%c ", crnt->data);
		return;
	}
	while (crnt != NULL) {
		printf("%c ", crnt->data);
		crnt = crnt->next;
	}
	printf("\n");
}

void hide(QUEUE* queue) {
	int mpty = is_empty(queue);
	NODE* crnt = queue->front;
	if (mpty == TRUE) printf("\n\t빈 큐입니다"); 
	else if (queue->len==1) printf("○ ");
	else {
		while (crnt != NULL) {
			printf("○ ");
			crnt = crnt->next;
		}
	}
}

void enqueue(QUEUE* queue, char DATA) {

	if (queue->len == 0) {
		queue->front->data = DATA;
		//printf("front %c\n", queue->front->data);//
	}
	else if (queue->len == 1) {
		queue->rear->data = DATA;
		//printf("rear %c\n", queue->rear->data);//
	}
	else {
		NODE* new = malloc(sizeof(NODE));
		new->data = DATA;
		queue->rear->next = new;
		queue->rear = new;
		queue->rear->next = NULL;
		//printf("%d %c\n", queue->len, queue->rear->data);//

	}
	queue->len++;
};

int is_empty(QUEUE* queue) {
	if (queue->len == 0) return TRUE;
	else return FALSE;
}

void dequeue(QUEUE* queue) {
	int mpty = is_empty(queue);
	if (mpty == TRUE) { printf("\n\t빈 큐이기에 기능 실행이 불가합니다\n"); return; } //if empty
	printf("\n\tdequeue : %c\n", queue->front->data);
	//if not empty
	if (queue->len == 1) queue->front->data = '\0';//데이터가 front하나에만 존재하는 경우
	else if (queue->len == 2) { //데이터가 front, rear 에만 존재하는 경우 
		queue->rear->data = queue->front->data;//front data 지움 >> rear data front 로 옮김
		queue->rear->data = '\0';
	}
	else {//노드가 세개 이상 남은 경우
		NODE* rmv = queue->front;
		queue->front = queue->front->next;
		free(rmv);
	}
	queue->len--;
}

void delete(QUEUE* queue) {
	int mpty = is_empty(queue);
	if (mpty == TRUE) { printf("\n\t빈 큐이기에 기능 실행이 불가합니다\n"); return; } //if empty
	//if not empty
	if (queue->len == 1) queue->front->data = '\0';//데이터가 front하나에만 존재하는 경우
	else if (queue->len == 2) { //데이터가 front, rear 에만 존재하는 경우 
		queue->rear->data = queue->front->data;
		queue->rear->data = '\0';
	}
	else {//노드가 세개 이상 남은 경우
		NODE* rmv = queue->front;
		queue->front = queue->front->next;
		free(rmv);
	}
	queue->len--;
}

void a_data_count(QUEUE* queue, char DATA) {
	int mpty = is_empty(queue);
	if (mpty == TRUE) { printf("\n\t빈 큐이기에 기능 실행이 불가합니다\n"); return; } //if empty

	NODE* crnt = queue->front;
	int cnt = 0;
	while (crnt != NULL) {
		if (crnt->data == DATA) cnt++;
		crnt = crnt->next;
	}
	if (cnt == 0)printf("\n\tqueue 내 data '%c'가 존재하지 않습니다.\n", DATA);
	else printf("\n\t%c data : %d개\n", DATA, cnt);
}

void data_count(QUEUE* queue) {
	printf("\n\tall data : %d개\n", queue->len);
}

void peek(QUEUE* queue) {
	int mpty = is_empty(queue);
	if (mpty == TRUE) { printf("\n\t빈 큐이기에 기능 실행이 불가합니다\n"); return; } //if empty

	printf("\n\tfront data : %c\n", queue->front->data);
}

void is_member(QUEUE* queue, char DATA) {
	int mpty = is_empty(queue);
	if (mpty == TRUE) { printf("\n\t빈 큐이기에 기능 실행이 불가합니다\n"); return; } //if empty
	printf("\n\t만약 동일 데이터 존재 시 \n\t모든 값의 위치를 반환합니다\n\t");

	NODE* new = queue->front;
	int num = 0;
	int no = FALSE;
	while (num != queue->len) {
		if (new->data == DATA) {
			printf("\n\tdata[%d] : %c", num+1, DATA);
			no = TRUE;
		}
		new = new->next;
		num++;
	}
	printf("\n");
	if (no == FALSE) printf("\n\tdata %c 가 queue 내에 존재하지 않습니다\n", DATA);
}

void replace(QUEUE* queue, char DATA) {
	queue->rear->data = DATA;
}

void empty(QUEUE* queue) {

	NODE* temp = NULL;
	while (queue->front->next != NULL) {
		temp = queue->front;
		queue->front = temp->next;
		free(temp);
	}
	free(queue->front);
}


int main() {
	NODE* newf = malloc(sizeof(NODE));
	NODE* newr = malloc(sizeof(NODE));

	QUEUE* queue = malloc(sizeof(NODE));
	queue->front = newf;
	queue->rear = newr;
	queue->front->data = '\0';
	queue->rear->data = '\0';
	queue->front->next = queue->rear;
	queue->rear->next = NULL;
	queue->len = 0;

	screen();
	int go = TRUE;
	int nhide = FALSE;
	while (go) {
		printf("\n\t");
		if (nhide == FALSE) print(queue);
		else hide(queue);
		char order[30] = { 0 };
		printf("\n\t>>> ");
		gets(order);
		int num = 0;
		int k = queue->len;
		int if_empty = 0;
		int index = 0;
		for (int i = 0; i < strlen(order); i++) {
			if (num == 0 && (int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
				while (order[i] - 48 >= 0 && order[i] - 48 <= 9) {
					index = index * 10;
					index += order[i] - 48;
					i++;
				}
				i--;
			}
			switch (order[i]) {
			case '+'://
				if (order[i + 1] == '\0') break; //자동 오타 수정 기능
				enqueue(queue, order[i + 1]);
				i++;
				break;
			case '-'://
				if (index != 0) for (int i = 0; i < index; i++) dequeue(queue);
				else dequeue(queue);
				break;
			case'C'://
				while (k != 0) { delete(queue, k); k--; }
				break;
			case'P'://
				peek(queue);
				break;
			case 'L':
				printL(queue);
				break;
			case 'D':
				nhide = TRUE;
				break;
			case 'R':
				nhide = FALSE;
				break;			
			case 'H':
				if (queue->len==0) printf("\n\t빈 큐이기에 기능 실행이 불가합니다\n");  //if empty
				else printf("\n\tFront : ( 1 , %c )\n",queue->front->data);
				break;
			case 'T':
				if (queue->len == 0) printf("\n\t빈 큐이기에 기능 실행이 불가합니다\n");  //if empty
				else printf("\n\trear : ( %d , %c )\n", queue->len, queue->rear->data);
				break;
			case '='://
				if (order[i + 1] == '\0') break;
				replace(queue, order[i + 1]);
				i++;
				break;
			case '#'://
				data_count(queue);
				break;
			case '@'://
				if (order[i + 1] == '\0') break;
				a_data_count(queue, order[i + 1]);
				i++;
				break;
			case'?'://
				if (order[i + 1] == '\0') break;
				is_member(queue, order[i + 1]);
				break;
			case'E'://
				if_empty = is_empty(queue);
				if (if_empty == TRUE) printf("\n\tQueue is empty : TRUE\n");
				else printf("\n\tQueue is empty : FALSE\n");
				break;
			case'F'://
				printf("\n\t해당 queue의 메모리 할당 방식 : dynamic\n\tSo this queue is not full\n");
				break;
			case'B'://
				printf("\n\t곧 큐를 통째로 날려버리는 폭탄이 작동합니다\n\n\t.\n\t.\n\t.\n\n\t");
				printf("&$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("@$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("&$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("@&%$#@%#&@&%$#@@y$#@?&@&(@#\n\t");
				printf("&$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("@&%$#@%#&@&%$#@@y$#@?&@&(@# \n\t");
				empty(queue);
				printf("\n\tQueue를 지웠기 때문에 프로그램을 강제 종료합니다.\n\n\t.\n\t.\n\t.");
				go = FALSE;
				break;//
			case 'Q'://
				printf("\n\tQueue를 비우고 프로그램을 종료합니다.\n\n");
				empty(queue);
				go = FALSE;
				break;
			default:
				break;
			}
		}

	}
	return 0;
}