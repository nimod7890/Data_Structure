#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


typedef struct _NODE {
	char data;
	struct _NODE* next;
}NODE;
typedef struct _stack {
	NODE* top;
	int len;
}STACK;

void screen() {
	printf("\n\n\t");
	printf("====================================================");
	printf("\n\n			    FUNCTION\n\t");
	printf("\n\t ****CAPITALIZE all the COMMANDSs\t");
	printf("\n\t ****Do not use space bar\n\t");
	printf("----------------------------------------------------");
	printf("\n\t + (data)		push\n\t");
	printf(" = (data)		replace data\n\t");
	printf(" - (data)		pop\n\t");
	printf(" H			hide all data \n\t"); //â�۱��
	printf(" R			reveal all data\n\t"); //
	printf(" L			print all data except cursor\n\t");
	printf(" E			is empty\n\t");	
	printf(" C			be empty\n\t");
	printf(" F			is full\n\t");
	printf(" T			return ( top index, data ) \n\t");
	printf(" P			peek // return top data \n\t");
	printf(" #			all data count\n\t");
	printf(" @ (data)		a data count\n\t");//
	printf(" ? (data)		this data is member\n\t");
	printf(" B			***BOMB*** (force stop)\n\t"); //
	printf("----------------------------------------------------\n\t");
	printf(" Q			quit\n\t"); // 
	printf("====================================================");
}

void print(STACK* stack,NODE*prnt) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("�� �����Դϴ�"); return; } //if empty
	if (prnt->next != NULL) print(stack, prnt->next); 

	
	if (prnt==stack->top) printf("(%c) ",prnt->data); //top ��ġ ǥ��
	else printf("%c ", prnt->data); // else
}

void printL(STACK* stack, NODE* prnt) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("\n\t �� �����Դϴ�"); return; } //if empty
	printf("\n\tall stack data : ");

	if (prnt->next != NULL) print(stack, prnt->next); 
	printf("%c ", prnt->data); 
	printf("\n");
}

void hide(STACK* stack, NODE* prnt) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("�� �����Դϴ�"); return; } //if empty
	if (prnt->next != NULL) hide(stack, prnt->next);

	if (prnt == stack->top) printf("(��)"); //top ��ġ ǥ��
	else printf("��", prnt->data); // else
}

void push(STACK* stack, char DATA) {

	NODE* new = malloc(sizeof(NODE));
	if (stack->len == 0) {
		stack->top->data = DATA;
		stack->len++;
		return;
	}
	new->data = DATA;
	new->next = stack->top;
	stack->top = new;

	stack->len++;

};

int is_empty(STACK* stack) {
	if (stack->len==0) return TRUE;
	else return FALSE;
}

void pop(STACK* stack) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("\n\t �� �����̱⿡ ��� ������ �Ұ��մϴ�\n"); return; } //if empty
	printf("\n\tpop : %c\n", stack->top->data);
	//if not empty
	if (stack->len != 1) {//��尡 �ΰ� �̻� ���� ���
		NODE* rmv = stack->top;
		rmv->next = stack->top->next;
		stack->top = stack->top->next;
		free(rmv);
	}
	else stack->top->data = '\0';//��尡 top �ϳ��� ���� ���
	
	stack->len--;
}

void delete(STACK* stack,int k) {
	NODE* rmv = stack->top;
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("\n\t �� �����̱⿡ ��� ������ �Ұ��մϴ�"); return; } //if empty
	//if not empty
	if (stack->len != 1) {//��尡 �ΰ� �̻� ���� ���
		NODE* rmv = stack->top;
		rmv->next = stack->top->next;
		stack->top = stack->top->next;
		free(rmv);
	}
	else stack->top->data = '\0';//��尡 top �ϳ��� ���� ���
	stack->len--;
}

void a_data_count(STACK *stack, char DATA) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("\n\t �� �����̱⿡ ��� ������ �Ұ��մϴ�\n"); return; } //if empty

	NODE* crnt = stack->top;
	int cnt = 0;
	while (crnt != NULL) {
		if (crnt->data == DATA) cnt++;
		crnt = crnt->next;
	}
	if (cnt == 0)printf("\n\tstack �� data '%c'�� �������� �ʽ��ϴ�.\n", DATA);
	else printf("\n\t%c data : %d��\n", DATA, cnt);
}

void data_count(STACK* stack) {
	printf("\n\tall data : %d��\n", stack->len);
}

void top(STACK* stack) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("\n\t �� �����̱⿡ top�� �������� �ʽ��ϴ�"); return; } //if empty

	printf("\n\t( %d, %c )\n", stack->len, stack->top->data);
}
void peek(STACK* stack) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("\n\t �� �����̱⿡ ��� ������ �Ұ��մϴ�\n"); return; } //if empty

	printf("\n\ttop data : %c\n", stack->top->data);
}

void is_member(STACK* stack,char DATA) {
	int mpty = is_empty(stack);
	if (mpty == TRUE) { printf("\n\t�� �����̱⿡ ��� ������ �Ұ��մϴ�\n"); return; } //if empty
	printf("\n\t���� ���� ������ ���� �� \n\t��� ���� ��ġ�� ��ȯ�մϴ�\n\t");

	NODE* new = stack->top;
	int num = 0;
	int no = FALSE;
	while (num != stack->len) {
		if (new->data == DATA) {
			printf("\n\tdata[%d] : %c", stack->len-num, DATA);
			no = TRUE;
		}
		new = new->next;
		num++;
	}
	printf("\n");
	if (no == FALSE) printf("\n\tdata %c �� stack ���� �������� �ʽ��ϴ�\n", DATA);
}

void empty(STACK* stack) {

	NODE* temp = NULL;
	while (stack->top->next != NULL) {
		temp = stack->top;
		stack->top = temp->next;
		free(temp);
	}
	free(stack->top);
}

void replace(STACK* stack, char DATA) {
	stack->top->data = DATA;
}

int main() {
	NODE* new = malloc(sizeof(NODE));
	STACK* stack = malloc(sizeof(NODE));
	stack->top = new;
	stack->top->data = '\0';
	stack->top->next = NULL;
	stack->len = 0;

	screen();
	int go = TRUE;
	int nhide = FALSE;
	while (go){
		NODE* prnt = stack->top;//print()�� ����Լ��� ������
		printf("\n\t");
		if (nhide == FALSE) print(stack, prnt);
		else hide(stack, prnt);
		char order[30] = { 0 };
		printf("\n\t>>> ");
		gets(order);
		int num = 0;
		int k = stack->len;
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
				if (order[i + 1] == '\0') break; //�ڵ� ��Ÿ ���� ���
				push(stack, order[i + 1]);
				i++;
				break;
			case '-'://
				if (index != 0) for (int i = 0; i < index; i++) pop(stack);
				else pop(stack);
				break;
			case'C'://
				while (k != 0) { delete(stack, k); k--; }
				break;
			case'T'://
				top(stack);
				break;
			case'P'://
				peek(stack);
				break;
			case 'L':
				printL(stack,prnt);
				break;
			case 'H':
				nhide = TRUE;
				break;
			case 'R':
				nhide = FALSE;
				break;
			case '='://
				if (order[i + 1] == '\0') break;
				replace(stack, order[i + 1]);
				i++;
				break;
			case '#'://
				data_count(stack);
				break;
			case '@'://
				if (order[i + 1] == '\0') break;
				a_data_count(stack, order[i + 1]);
				i++;
				break;
			case'?'://
				if (order[i + 1] == '\0') break;
				is_member(stack, order[i + 1]);
				break;
			case'E'://

				if_empty = is_empty(stack);
				if (if_empty == TRUE) printf("\n\tStack is empty : TRUE\n");
				else printf("\n\tStack is empty : FALSE\n");
				break;
			case'F'://
				printf("\n\t�ش� stack�� �޸� �Ҵ� ��� : dynamic\n\tSo this stack is not full\n");
				break;
			case'B'://
				printf("\n\t�� ������ ��°�� ���������� ��ź�� �۵��մϴ�\n\n\t.\n\t.\n\t.\n\n\t");
				printf("&$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("@$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("&$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("@&%$#@%#&@&%$#@@y$#@?&@&(@#\n\t");
				printf("&$$%$#@%$#$#@!$@#$!@#$%&%$@\n\t");
				printf("@&%$#@%#&@&%$#@@y$#@?&@&(@# \n\t");
				empty(stack);
				printf("\n\tStack�� ������ ������ ���α׷��� ���� �����մϴ�.\n\n\t.\n\t.\n\t.");
				go = FALSE;
				break;//
			case 'Q'://
				printf("\n\tStack�� ���� ���α׷��� �����մϴ�.\n\n");
				empty(stack);
				go = FALSE;
				break;
			default:
				break;
			}
		}

	}

	return 0;
}