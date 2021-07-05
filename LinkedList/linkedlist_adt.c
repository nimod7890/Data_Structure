#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


typedef struct _NODE {
	char data;
	struct _NODE* next;
}NODE;
typedef struct _list {
	NODE* head;
	NODE* position;
	int curr;
	int len;
}LIST;




void addtail(LIST* list, char DATA) {
	NODE* new = malloc(sizeof(NODE));
	if (list->position->next != NULL) {
		NODE* cnt = list->head;
		while (cnt->next != NULL) {
			cnt = cnt->next;
		}
		list->position = cnt;
	}
	new->data = DATA;
	new->next = NULL;
	list->position->next = new;	
	list->position = new;

	list->curr++;
	list->len++;
}
void addfront(LIST* list, char DATA) {//처음에 전 위치에 끼워넣어주기
	NODE* before = NULL;
	before = list->head;
	int num = 0;
	while (num != list->curr - 1) {
		before = before->next;
		num++;
	}

	NODE* new = malloc(sizeof(NODE));
	new->data = DATA;
	new->next = list->position;
	before->next = new;

	list->len++;
	list->position = new;

	//printf("\naddfront %d data %c\n", list->curr,list->position->data);
};
void add(LIST* list, char DATA) {//그담부턴 그 뒤에 넣어주기

	NODE* new = malloc(sizeof(NODE));
	if (list->position->next == NULL) {//위치 마지막
		new->data = DATA;
		new->next = NULL;
		list->position->next = new;
	}
	else {
		new->next = list->position->next;
		new->data = DATA;
		list->position->next = new;

	}
	list->position = new;
	//printf("\ninsert %d data %c\n", list->curr, list->position->data);

	list->curr++;
	list->len++;

}

void delete(LIST* list) {
	NODE* rmv = list->head;
	if (list->head->next == NULL) return;  //if empty

	//if not empty

	//find beforenode
	int num = 0;
	while (num != list->curr - 1) {
		rmv = rmv->next;
		num++;
	}//printf("rmv %c\n", *rmv);

	if (list->position->next == NULL) {		//if last node
		rmv->next = NULL;
		if (list->len == 1) {
			list->position = list->head;
			list->curr = 0;
		}
		else {
			list->position = list->head->next;
			list->curr = 1;
		}//printf("\nlast node %d data %c\n", list->curr, list->position->data);
	}
	else {											//if not last node
		NODE* delete = list->position;
		rmv->next = list->position->next;
		list->position = list->position->next;
		free(delete);
		//printf("\nnot last node %d data %c\n", list->curr, list->position->data);
	}
	list->len--;
}
void empty(LIST* list) {

	NODE* temp = NULL;
	while (list->head->next != NULL) {
		temp = list->head->next;
		list->head->next = temp->next;
		free(temp);
	}
	free(list->head);
}
void is_empty(LIST* list) {
	if (list->head->next == NULL) printf("\n\tList is empty : True");
	else printf("\n\tList is empty : False");
}

void print(LIST* list) {
	NODE* crnt = list->head->next;
	printf("\n\t");
	int num = 0;
	if (crnt == NULL) printf("This list is empty");
	else while (crnt != NULL) {
		if (num == list->curr - 1) printf("(%c) ", crnt->data);
		else printf("%c ", crnt->data);
		crnt = crnt->next;
		num++;
	}
}
void printL(LIST* list) {
	NODE* crnt = list->head->next;
	printf("\n\t");
	int num = 0;
	if (crnt == NULL) printf("This list is empty");
	else while (crnt != NULL) {
		printf("%c ", crnt->data);
		crnt = crnt->next;
		num++;
	}
}

void is_member(LIST* list, char DATA) {
	NODE* crnt = list->position;
	NODE* node = NULL;

	printf("\n\t만약 동일 데이터 존재 시 \n\t모든 값의 위치를 반환 후\n\t마지막 반환 값의 위치로 이동합니다.\n\n\t");
	int num = list->curr;
	int no = FALSE;
	int k = 0;
	do {
		if (crnt->data == DATA) {
			printf("%c : %d번째 데이터 \n\t", DATA, num);
			k = num;//위치 임시저장
			node = crnt;//노드 임시 저장
			no = TRUE;
		}
		crnt = crnt->next;
		num++;

		if (crnt == NULL) {
			crnt = list->head->next;
			num = 1;
		}
	} while (num != list->curr);
	list->curr = k;
	list->position = node;
	if (no != TRUE) printf("Not Found");
}
void get_data(LIST* list) {
	printf("\n\tcurrent data : %c", list->position->data);
}
void data_count(LIST* list) {
	NODE* cnt = list->head->next;

	printf("\n\tall data : ");
	int num = 0;
	while (cnt != NULL) {
		cnt = cnt->next;
		num++;
	}
	printf("%d개", num);
	free(cnt);
}
void a_data_count(LIST* list, char DATA) {
	NODE* crnt = list->head->next;
	int num = 0, cnt = 0;
	while (crnt != NULL) {
		if (crnt->data == DATA) cnt++;
		crnt = crnt->next;
		num++;
	}
	printf("\n\t%c data : %d개", DATA, cnt);
}

void traverse_front(LIST* list) {
	if (list->len == 0) return;
	list->curr = 1;
	list->position = list->head->next;
}//
void traverse_rear(LIST* list) {
	if (list->position->next == NULL) return;
	NODE* crnt = list->head->next;
	int num = 1;
	while (crnt->next != NULL) {
		crnt = crnt->next;
		num++;
	}
	crnt->next = NULL;
	list->position = crnt;
	list->curr = num;
}
void gonext(LIST* list) {
	if (list->position->next == NULL) return;
	list->curr++;
	list->position = list->position->next;
}
void goback(LIST* list) {
	if (list->curr <= 1) return;
	NODE* crnt = list->head;

	int num = 0;
	while (num != list->curr - 1) {
		crnt = crnt->next;
		num++;
	}
	crnt->next = list->position;
	list->position = crnt;
	list->curr--;
}
void go_index(LIST* list, int index) {

	if (list->len == 0 || index > list->len) return;
	NODE* crr = list->head;

	for (int i = 0; i < index; i++)	crr = crr->next;
	
	list->position = crr;
	list->curr = index;
}
void replace(LIST* list, char DATA) {
	list->position->data = DATA;
}


int main() {
	NODE* new = malloc(sizeof(NODE));
	LIST* list = malloc(sizeof(NODE));
	list->head = new;
	list->head->data = NULL;
	list->head->next = NULL;
	list->position = list->head;
	list->curr = 0;
	list->len = 0;

	screen();
	int go = TRUE;

	while (go) {
		print(list);
		char order[30] = { 0 };
		printf("\n\t>>> ");
		gets(order);
		int num = 0, k = list->len;

		for (int i = 0; i < strlen(order); i++) {
			if (num == 0 && (int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
				int index = 0;
				while (order[i] - 48 >= 0 && order[i] - 48 <= 9) {
					index = index * 10;
					index += order[i] - 48;
					i++;
				}
				i--;
				go_index(list, index);
			}
			if (order[i] == '~') {
				if (order[i + 1] == '\0') break;
				addtail(list, order[i + 1]);
				i++;
				num++;
				continue;
			}
			switch (order[i]) {
			case '+':
				if (order[i + 1] == '\0') break;
				if (num == 0 && list->len != 0) addfront(list, order[i + 1]);
				else add(list, order[i + 1]);
				i++;
				num++;
				break;
			case '-':
				delete(list);
				break;
			case'C':
				while (k != 0) { delete(list); k--; }
				break;
			case 'L':
				printL(list);
				break;
			case 'G':
				get_data(list);
				break;
			case '<':
				traverse_front(list);
				break;
			case '>':
				traverse_rear(list);
				break;
			case 'N':
				gonext(list);
				break;
			case 'P':
				goback(list);
				break;
			case '=':
				replace(list, order[i + 1]);
				i++;
				break;
			case '#':
				data_count(list);
				break;
			case '@':
				a_data_count(list, order[i + 1]);
				i++;
				break;
			case'?':
				is_member(list, order[i + 1]);
				break;
			case'E':
				is_empty(list);
				break;
			case'M':
				empty(list);
				printf("\n\tList를 지웠기 때문에 프로그램을 강제 종료합니다.\n\n");
				go = FALSE;
				break;
			case 'Q':
				printf("\n\tList를 비우고 프로그램을 종료합니다.\n\n");
				empty(list);
				go = FALSE;
				break;
			default:
				break;
			}
		}

	}

	return 0;
}