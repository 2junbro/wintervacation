/*1번*/
#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100
#define BUF 100
int search(char *name);
void add(char *arg1, int arg2, int arg3);
void create(char *arg1); 
void print(char *arg1);
int read_line(char str[], int limit);
void process_command();
void balance(char *arg1, int count);
void mult(char *arg1, int arg2);
int calc(char *arg1, int arg2);
void diff(char *arg1, char *arg2, char *arg3);
void printall();
//int find(char arg1, int len, int arg3);

//하나의 항 표현
typedef struct term {
	int coef;	//계수
	int expo;	//차수
}Term;
//하나의 다항식 표현
typedef struct polynomial {
	char name[20];	//함수명
	int nbr_terms;	//항의 개수
	Term *terms[MAX];
}Polynomial;
Polynomial *polys[MAX];	//다항식 저장 배열
int n=0;	//다항식의 개수
char delim[] = " ";

//파일로부터 라인 단위 읽기
int read_line(char str[], int limit)
{
	int ch, i = 0;
	while ((ch = getchar()) != '\n')//띄어쓰기 나올때까지 읽음
		if (i < limit - 1)		//문자열끝까지 읽어서 str에 저장
			str[i++] = ch;

	str[i] = '\0';	//문자열 끝에 널문자 넣음
	return i;
}

//한라인 전체 읽어오는 함수
void process_command() {
	char command_line[BUF];
	char *command, *argument1;
	char *argument_2, *argument_3;
	int argument2,argument3;

	while (1) {							//반복해서 계속 읽어드림
		printf("$ ");
		if (read_line(command_line, BUF) <= 0)		//읽은게 없으면 반복
			continue;
		command = strtok(command_line, delim);
		if (command == NULL)continue;			//명령 맞는게 없으면 반복

		//create 입력 했을때
		if (strcmp(command, "create") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("다시 입력\n");
				continue;
			}
			create(argument1);
		}
		//add 입력 했을때
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = atoi(strtok(NULL, delim));
			argument3 = atoi(strtok(NULL, delim));
			if (argument1 == NULL ) {
				printf("다시 입력\n");
				continue;
			}
			add(argument1,argument2,argument3);
		}
		//mult 입력 했을때
		else if (strcmp(command, "mult") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = atoi(strtok(NULL, delim));
			if (argument1 == NULL) {
				printf("다시입력\n");
				continue;
			}
			mult(argument1, argument2);
		}
		//calc 입력 햇을때
		else if (strcmp(command, "calc") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = atoi(strtok(NULL, delim));
			if (argument1 == NULL) {
				printf("다시입력\n");
				continue;
			}
			printf("%d\n", calc(argument1, argument2));
		}
		//diff 입력 햇을때
		else if (strcmp(command, "diff")==0) {
			argument1 = strtok(NULL, delim);
			argument_2 = strtok(NULL, delim);
			argument_3 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("다시 입력\n");
				continue;
			}
			diff(argument1, argument_2, argument_3);
		}
		//print 입력 했을때
		else if (strcmp(command, "print") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("다시입력\n");
				continue;
			}
			if (strcmp(argument1,"all")==0 ){
				printall();
			}
			else {
				print(argument1);
			}
		}
		else if(strcmp(command,"exit") == 0) {
			printf("끝");
			break;
		}
	}
}

//메인 함수
int main() {
	process_command();
	return 0;
}

//함수명에 맞는 위치를 찾는 search함수
int search(char *name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, polys[i]->name) == 0) {
			return i;
		}
	}
	return -1;
}

//계수에 맞게 정렬시켜주는 balance 함수
void balance(char *arg1, int count) {
	int temp, temp2;
	int index = search(arg1);


	//크기순으로 정렬
	for (int i = 0; i < count; i++)    // 요소의 개수만큼 반복
	{
		for (int j = 0; j < count - 1; j++)   // 요소의 개수 - 1만큼 반복
		{
			if (polys[index]->terms[i]->expo > polys[index]->terms[j]->expo)	// 현재 요소의 값과 다음 요소의 값을 비교하여
			{                                 // 큰 값을
				temp = polys[index]->terms[i]->expo;
				polys[index]->terms[i]->expo = polys[index]->terms[j]->expo;
				polys[index]->terms[j]->expo = temp;            // 다음 요소로 보냄

				temp2 = polys[index]->terms[i]->coef;
				polys[index]->terms[i]->coef = polys[index]->terms[j]->coef;
				polys[index]->terms[j]->coef = temp2;
			}
		}
	}

	//같은 차수 존재하면 계수 합침
	for (int i = 0; i < count; i++)
	{
			if (polys[index]->terms[i]->expo == polys[index]->terms[i+1]->expo)	
			{                                
				polys[index]->terms[i]->coef += polys[index]->terms[i+1]->coef;
				polys[index]->terms[i+1]->expo = 0;            
				polys[index]->terms[i+1]->coef = 0;
			}
	}
}

//create 함수
void create(char *arg1) {
	polys[n] = malloc(sizeof(Polynomial));
	for (int i = 0; i < MAX; i++) {
		polys[n]->terms[i] = malloc(sizeof(Term));
	}
	strcpy(polys[n]->name, arg1);		//새로운 함수를 선언 하고 초기화 시켜줌
	polys[n]->terms[0]->coef = 0;
	polys[n]->terms[0]->expo = 0;
	polys[n]->nbr_terms = 0;
	n++;			//다음 함수를 받기위해서 다항식의 개수인 n을 증가
}

//수정전 add 함수
void add(char *arg1, int arg2, int arg3) {
	int index = search(arg1);		//search함수로 함수명에 맞는 곳 찾기
	polys[index]->terms[polys[index]->nbr_terms]->coef = arg2;	//nbr_terms의 함수 항에다가 차수 대입
	polys[index]->terms[polys[index]->nbr_terms]->expo = arg3;//nbr_terms의 함수 항에다가 계수 대입
	polys[index]->nbr_terms++;	//nbr_terms값 증가
	balance(arg1, polys[index]->nbr_terms);

}

//mult 함수
void mult(char *arg1, int arg2)
{
	int index = search(arg1);
	int count = polys[index]->nbr_terms;
	for (int i = 0; i < count; i++) {
		(polys[index]->terms[i]->coef) *= arg2;
	}
}

int calc(char *arg1, int arg2)
{
	int index = search(arg1);
	int count = polys[index]->nbr_terms;
	int answer = 0;
	for (int i = 0; i < count; i++) {
		answer += ((polys[index]->terms[i]->coef)*pow(arg2, polys[index]->terms[i]->expo));
	}
	return answer;
}

//diff함수
void diff(char *arg1, char *arg2, char *arg3)
{
	int index = search(arg1);
	int count = polys[index]->nbr_terms;
	create(arg3);
	int index2 = search(arg3);
	polys[index2]->nbr_terms = polys[index]->nbr_terms;
	for (int i = 0; i < count; i++) {
		polys[index2]->terms[i]->coef = polys[index]->terms[i]->coef*polys[index]->terms[i]->expo;
		polys[index2]->terms[i]->expo = polys[index]->terms[i]->expo - 1;
	}
}


//print 함수
void print(char *arg1) {
	int index = search(arg1);
	for (int i = 0; i < polys[index]->nbr_terms; i++) {
		if (polys[index]->terms[i]->coef != 0) {
			if (polys[index]->terms[i]->coef > 0)
				printf("+");
			printf("%dx", polys[index]->terms[i]->coef);
			printf("^%d", polys[index]->terms[i]->expo);
		}
	}
	printf("\n");
}

//printall 함수
void printall() {
	for (int j = 0; j < n; j++) {
		printf("%s: ", polys[j]->name);
		for (int i = 0; i < polys[j]->nbr_terms; i++) {
			if (polys[j]->terms[i]->coef != 0) {
				if (polys[j]->terms[i]->coef > 0)
					printf("+");
				printf("%dx", polys[j]->terms[i]->coef);
				printf("^%d", polys[j]->terms[i]->expo);
			}
		}
		printf("\n");

	}
}