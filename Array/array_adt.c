#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ARRAYSIZE 30
#define NULL '\0'

int length = 0;
int position = -1;

void screen(char array[]) {
	printf("\n\n\t");
	printf("=================================================");
	printf("\n\n			    FUNCTION\n\t");
	printf("\n\t ****CAPITALIZE all the COMMANDSs\t");
	printf("\n\t ****Enter all DATA in LOWERCASE\t");
	printf("\n\t ****Do not use space bar\n\t");
	printf("-------------------------------------------------");
	printf("\n\n\t + (data)		insert\n\t");
	printf(" + (index) (data)	insert (numberth) data\n\t"); //창작 기능 1
	printf(" = (data)		replace data\n\t");
	printf(" = (index) (data)	replace (numberth) data\n\t"); //창작 기능 2
	printf(" - (data)		delete\n\t");
	printf(" - (index)		delete (numberth) data\n\t"); //창작 기능 3
	printf(" @			print present data\n\t");
	printf(" @ (index)		print (numberth) data\n\t"); //창작 기능 4
	printf(" L			print all data\n\t");
	printf(" E			be empty\n\t");
	printf(" A			length of array\n\t"); //창작 기능 5
	printf(" R			reverse array\n\t");//창작 기능 6
	printf(" <			go to first index\n\t");
	printf(" >			go to last index\n\t");
	printf(" N			go to next index\n\t");
	printf(" P			go to previous index\n\t");
	printf(" G (index)		go to (numberth) index\n\t"); //창작 기능 7
	printf(" M (index)		Move (numberth) index\n\t");
	printf(" MN			move forward one\n\t");
	printf(" MP			move backward one\n\t");
	printf(" Mn			move to end of list \n\n\t");
	printf("-------------------------------------------------\n\t");
	printf(" Q			quit\n\t"); // 8
	printf("=================================================");
}//screen()

void insert(char array[], char data) {
	position++;
	length = strlen(array);
	for (int i = length; i >= position; i--) {
		array[i] = array[i - 1];
	}
	array[position] = data;
}

void change(char array[], char data) {
	array[position] = data;
}
void change_part(char array[], int index, char data) {
	array[index - 48] = data;
	position = index - 48;
}

void delete(char array[], int position) {
	for (int i = position; i < length - 1; i++) {
		array[i] = array[i + 1];
	}array[length - 1] = NULL;
}

void empty(char array[]) {
	for (int i = 0; i < length; i++) {
		array[i] = NULL;
	}
	position = -1;
}

void print(char array[]) {
	length = strlen(array);
	if (length == 0) printf(" This array is empty");
	else {
		printf("\t    array : [");
		for (int i = 0; i < length-1; i++)	printf(" %c,", array[i]);
		printf(" %c ]\n",array[length-1]);
	}
	
}
void reverse(char array[]) {
	char temp;

	for (int i = 0; i < length / 2; i++) {
		temp = array[i];
		array[i] = array[(length - 1) - i];
		array[(length - 1) - i] = temp;
	}
}

void gofirst(char array[]) {
	position = 0;
}
void golast(char array[]) {
	position = length - 1;
}
void gonext(char array[]) {
	if (position == length - 1);
	else position++;
}
void goprevious(char array[]) {
	if (position == 0);
	else position--;
}
void gowhere(char array[], int index) {
	if ((index - 48 < 0) || (index - 48 > 29));
	else position = index - 48;
}

void move(char array[], int index) {
	char temp;
	if (position > index) {
		for (int i = position; i > index; i--) {
			temp = array[i - 1];
			array[i - 1] = array[i];
			array[i] = temp;
		}
	}
	else if (position < index) {
		for (int i = position; i < index; i++) {
			temp = array[i + 1];
			array[i + 1] = array[i];
			array[i] = temp;
		}
	}
	else;
	position = index;
}

//main function
int main() {

	char my_array[ARRAYSIZE] = { 0 };
	int bIterationFlag = TRUE;
	screen(my_array);
	while (bIterationFlag) {

		char order[30] = { 0 }; //create

		length = strlen(my_array);
		if (length == 0) printf("\n\t This array is empty");
		else {
			printf("\t");
			for (int i = 0; i < length; i++) {
				if ((i == position || (position == -1 && length != 0))) printf(" (%c)", my_array[i]);
				else printf(" %c", my_array[i]);
			}
		}
		printf("\n\t>>> ");
		gets(order);
		char orderLength = strlen(order);

		for (int i = 0; i < orderLength; i++) {
			switch (order[i]) {
			case '+':
				if (((int)order[i + 1] - 48 >= 0) && ((int)order[i + 1] - 48 < 30)) {
					position = (int)order[i + 1] - 48 - 1;
					insert(my_array, order[i + 2]);
					i = i + 2;
				}
				else {
					insert(my_array, order[i + 1]);
					i++;
				}break;
			case '-':
				if (((int)order[i + 1] - 48 >= 0) && ((int)order[i + 1] - 48 < 30)) {
					position = (int)order[i + 1] - 48;
					i++;
				}delete(my_array, position);
				if (position == length - 1)position = 0;
				break;
			case '=':
				if (((int)order[i + 1] - 48 >= 0) && ((int)order[i + 1] - 48 < 30)) {
					change_part(my_array, (int)order[i + 1], order[i + 2]);
					i = i + 2;
				}
				else {
					change(my_array, order[i + 1]);
					i++;
				}break;
			case 'E':
				empty(my_array);
				break;
			case '@':
				if (((int)order[i + 1] - 48 >= 0) && ((int)order[i + 1] - 48 < 30))
					printf("\t array[%d] : %c\n", (int)order[i + 1] - 48, my_array[(int)order[i + 1] - 48]);
				else printf("\t array[%d] : %c\n", position, my_array[position]);
				break;
			case 'A':
				printf("\t Length of array : %d\n", strlen(my_array));
				break;
			case 'L':
				print(my_array);
				break;
			case 'R':
				reverse(my_array);
				break;
			case '<':
				gofirst(my_array);
				break;
			case '>':
				golast(my_array);
				break;
			case 'N':
				gonext(my_array);
				break;
			case 'P':
				goprevious(my_array);
				break;
			case 'G':
				if (((int)order[i + 1] - 48 >= 0) && ((int)order[i + 1] - 48 < 30)) {
					gowhere(my_array, (int)order[i + 1]);
					i++;
				}break;
			case 'M':
				if (order[i + 1] == 'N')
					move(my_array, position + 1);
				else if (order[i + 1] == 'P')
					move(my_array, position - 1);
				else if (order[i + 1] == 'n') {
					move(my_array, length - 1);
					i++;
				}
				else if (((int)order[i + 1] - 48 >= 0) && ((int)order[i + 1] - 48 < 30))
					move(my_array, (int)order[i + 1] - 48);
				i++;
				break;
			case 'Q':
				printf("\n\t\t\t\t\t\t-The end-\n\n");
				bIterationFlag = FALSE;
				break;
			default:
				break;
			}//switch
		}//for
	}//while
	return 0;
}//main()
