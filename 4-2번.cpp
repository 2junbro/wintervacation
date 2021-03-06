#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 100
#define MAX 100
#define BUFFER_SIZE 50

int read_line(FILE * fp, char str[], int n); //한 줄 읽기
int search(char Name);		// 검색
void create(char Name);		// 다항식 f(x) = 0 정의, 다항식 이름 중복되는 경우 오류 메시지 출력하기
void add(char Name, int a, int b);	// f(x)에 항 더하기
void mult(char Name, int a);		// f(x) 에 정수 n 곱하기
void calc(char Name, int x);		// f(x) x 넣어서 계산하기
void diff(char Name1, char Name2);		// f(x)  미분하여 새로운 다항식 만들어 저장하기
void print(char Name);		// h 프린트하기 -> all : 현재까지 모든 다항식 출력하기
void printAll();		// 다 출력하기

typedef struct term {	// 하나의 항을 표현하는 구조체
	int coef;			// 계수 ㅇㅇ
	int expo;			// 차수 ㅇㅇ
} Term;

typedef struct polynomial {	// 하나의 다항식을 표현하기 위한 구조체
	char name;				// f, g, h등의 다항식의 이름 ㅇㅇ
	int nbr_terms;			// 이 다항식을 구성하는 항의 개수 ㅇㅇ
	Term *terms[MAX_TERMS];
}Polynomial;

Polynomial *polys[MAX];	// 여러 개의 다항식을 저장하기 위한 배열
int n = 0;					// 다항식의 개수

int main() {

	char command_line[BUFFER_SIZE];
	char *command, *argument;
	char Ar, Ar2;

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "create") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			Ar = argument[0];
			create(Ar);
		}

		else if (strcmp(command, "add") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("잘못\n");
				continue;
			}
			Ar = argument[0];
			argument = strtok(NULL, " ");
			int a = atoi(argument);
			argument = strtok(NULL, " ");
			int b = atoi(argument);
			add(Ar, a, b);
		}

		else if (strcmp(command, "mult") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("잘못\n");
				continue;
			}
			Ar = argument[0];
			argument = strtok(NULL, " ");
			int a = atoi(argument);
			mult(Ar, a);
		}

		else if (strcmp(command, "calc") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("잘못\n");
				continue;
			}
			Ar = argument[0];
			argument = strtok(NULL, " ");
			int a = atoi(argument);
			calc(Ar, a);
		}

		else if (strcmp(command, "print") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("잘못\n");
				continue;
			}
			else if (strcmp(argument, "all") == 0) {
				printAll();
			}
			else {
				Ar = argument[0];
				print(Ar);
			}
		}

		else if (strcmp(command, "diff") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("잘못\n");
				continue;
			}
			Ar = argument[0];
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("잘못\n");
				continue;
			}
			argument = strtok(NULL, " ");
			Ar2 = argument[0];
			diff(Ar, Ar2);
		}
		else if (strcmp(command, "exit") == 0)
			return 0;
	}
}

int read_line(FILE * fp, char str[], int n) {
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n')
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';

	return i;
}

int search(char Name) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (Name == polys[i]->name)
			return i;
		count++;
	}
	if (count == 0)
		return -2;
	return -3;
}

void create(char Name) {
	int j = n - 1;
	if (j >= 0) {
		if (search(Name) != -1 && search(Name) != -3) {
			printf("중복\n");
			return;
		}
		while (polys[j]->name > Name) {
			polys[j + 1] = polys[j];
			j--;
		}
	}
	polys[j + 1] = (Polynomial *)malloc(sizeof(Polynomial));
	polys[j + 1]->name = Name;
	polys[j + 1]->nbr_terms = 0;
	n++;
}

void add(char Name, int a, int b) { /* 차수 순서대로 저장 */
	int p = search(Name);
	if (p == -1) {
		printf("없음\n");
		return;
	}
	int j = polys[p]->nbr_terms - 1;

	for (int k = 0; k < j; k++)
		if (b == polys[p]->terms[k]->expo) {
			polys[p]->terms[k]->coef += a;
			return;
		}

	while (j >= 0 && polys[p]->terms[j]->expo < b) {
		polys[p]->terms[j + 1] = polys[p]->terms[j];
		j--;
	}
	polys[p]->terms[j + 1] = (Term *)malloc(sizeof(Term));
	polys[p]->terms[j + 1]->coef = a;
	polys[p]->terms[j + 1]->expo = b;
	polys[p]->nbr_terms++;
}

void mult(char Name, int a) {
	int p = search(Name);
	if (p == -1) {
		printf("없음\n");
		return;
	}
	for (int i = 0; i < polys[p]->nbr_terms; i++)
		polys[p]->terms[i]->coef *= a;
}

void calc(char Name, int x) {
	int p = search(Name);
	if (p == -1) {
		printf("없음\n");
		return;
	}
	int result1 = 0;
	int result2 = 0;
	for (int i = 0; i < polys[p]->nbr_terms; i++) {
		result1 = polys[p]->terms[i]->coef;
		for (int j = 0; j < polys[p]->terms[i]->expo; j++) {
			result1 *= x;
		}
		result2 += result1;
	}
	printf("%d\n", result2);
}

void print(char Name) {
	int p = search(Name);
	if (p == -1) {
		printf("없음\n");
		return;
	}

	for (int j = 0; j < polys[p]->nbr_terms; j++) {
		if (polys[p]->terms[j]->coef >= 0 && j != 0)
			printf("+");
		if (polys[p]->terms[j]->expo > 1) {
			if (polys[p]->terms[j]->coef == 1)
				printf("x^%d", polys[p]->terms[j]->expo);
			else if (polys[p]->terms[j]->coef == -1)
				printf("-x^%d", polys[p]->terms[j]->expo);
			else
				printf("%dx^%d", polys[p]->terms[j]->coef, polys[p]->terms[j]->expo);
		}
		else if (polys[p]->terms[j]->expo == 1) {
			if (polys[p]->terms[j]->coef == 1)
				printf("x");
			else if (polys[p]->terms[j]->coef == -1)
				printf("-x");
			else
				printf("%dx", polys[p]->terms[j]->coef);
		}
		else
			printf("%d", polys[p]->terms[j]->coef);
	}
	printf("\n");
	return;
}

void diff(char Name1, char Name2) {
	create(Name2);
	int p1 = search(Name1);
	int p2 = search(Name2);
	for (int i = 0; i < polys[p1]->nbr_terms; i++) {
		polys[p2]->terms[i] = (Term *)malloc(sizeof(Term));
		polys[p2]->terms[i]->coef = polys[p1]->terms[i]->coef*polys[p1]->terms[i]->expo;
		polys[p2]->terms[i]->expo = polys[p1]->terms[i]->expo - 1;
		if (polys[p1]->terms[i]->expo == 0)
			return;
		polys[p2]->nbr_terms++;
	}
}

void printAll() {
	for (int i = 0; i < n; i++) {
		printf("%c(x) = ", polys[i]->name);
		print(polys[i]->name);
	}
}