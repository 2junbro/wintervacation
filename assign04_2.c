/*1��*/
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

//�ϳ��� �� ǥ��
typedef struct term {
	int coef;	//���
	int expo;	//����
}Term;
//�ϳ��� ���׽� ǥ��
typedef struct polynomial {
	char name[20];	//�Լ���
	int nbr_terms;	//���� ����
	Term *terms[MAX];
}Polynomial;
Polynomial *polys[MAX];	//���׽� ���� �迭
int n=0;	//���׽��� ����
char delim[] = " ";

//���Ϸκ��� ���� ���� �б�
int read_line(char str[], int limit)
{
	int ch, i = 0;
	while ((ch = getchar()) != '\n')//���� ���ö����� ����
		if (i < limit - 1)		//���ڿ������� �о str�� ����
			str[i++] = ch;

	str[i] = '\0';	//���ڿ� ���� �ι��� ����
	return i;
}

//�Ѷ��� ��ü �о���� �Լ�
void process_command() {
	char command_line[BUF];
	char *command, *argument1;
	char *argument_2, *argument_3;
	int argument2,argument3;

	while (1) {							//�ݺ��ؼ� ��� �о�帲
		printf("$ ");
		if (read_line(command_line, BUF) <= 0)		//������ ������ �ݺ�
			continue;
		command = strtok(command_line, delim);
		if (command == NULL)continue;			//��� �´°� ������ �ݺ�

		//create �Է� ������
		if (strcmp(command, "create") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("�ٽ� �Է�\n");
				continue;
			}
			create(argument1);
		}
		//add �Է� ������
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = atoi(strtok(NULL, delim));
			argument3 = atoi(strtok(NULL, delim));
			if (argument1 == NULL ) {
				printf("�ٽ� �Է�\n");
				continue;
			}
			add(argument1,argument2,argument3);
		}
		//mult �Է� ������
		else if (strcmp(command, "mult") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = atoi(strtok(NULL, delim));
			if (argument1 == NULL) {
				printf("�ٽ��Է�\n");
				continue;
			}
			mult(argument1, argument2);
		}
		//calc �Է� ������
		else if (strcmp(command, "calc") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = atoi(strtok(NULL, delim));
			if (argument1 == NULL) {
				printf("�ٽ��Է�\n");
				continue;
			}
			printf("%d\n", calc(argument1, argument2));
		}
		//diff �Է� ������
		else if (strcmp(command, "diff")==0) {
			argument1 = strtok(NULL, delim);
			argument_2 = strtok(NULL, delim);
			argument_3 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("�ٽ� �Է�\n");
				continue;
			}
			diff(argument1, argument_2, argument_3);
		}
		//print �Է� ������
		else if (strcmp(command, "print") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("�ٽ��Է�\n");
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
			printf("��");
			break;
		}
	}
}

//���� �Լ�
int main() {
	process_command();
	return 0;
}

//�Լ��� �´� ��ġ�� ã�� search�Լ�
int search(char *name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, polys[i]->name) == 0) {
			return i;
		}
	}
	return -1;
}

//����� �°� ���Ľ����ִ� balance �Լ�
void balance(char *arg1, int count) {
	int temp, temp2;
	int index = search(arg1);


	//ũ������� ����
	for (int i = 0; i < count; i++)    // ����� ������ŭ �ݺ�
	{
		for (int j = 0; j < count - 1; j++)   // ����� ���� - 1��ŭ �ݺ�
		{
			if (polys[index]->terms[i]->expo > polys[index]->terms[j]->expo)	// ���� ����� ���� ���� ����� ���� ���Ͽ�
			{                                 // ū ����
				temp = polys[index]->terms[i]->expo;
				polys[index]->terms[i]->expo = polys[index]->terms[j]->expo;
				polys[index]->terms[j]->expo = temp;            // ���� ��ҷ� ����

				temp2 = polys[index]->terms[i]->coef;
				polys[index]->terms[i]->coef = polys[index]->terms[j]->coef;
				polys[index]->terms[j]->coef = temp2;
			}
		}
	}

	//���� ���� �����ϸ� ��� ��ħ
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

//create �Լ�
void create(char *arg1) {
	polys[n] = malloc(sizeof(Polynomial));
	for (int i = 0; i < MAX; i++) {
		polys[n]->terms[i] = malloc(sizeof(Term));
	}
	strcpy(polys[n]->name, arg1);		//���ο� �Լ��� ���� �ϰ� �ʱ�ȭ ������
	polys[n]->terms[0]->coef = 0;
	polys[n]->terms[0]->expo = 0;
	polys[n]->nbr_terms = 0;
	n++;			//���� �Լ��� �ޱ����ؼ� ���׽��� ������ n�� ����
}

//������ add �Լ�
void add(char *arg1, int arg2, int arg3) {
	int index = search(arg1);		//search�Լ��� �Լ��� �´� �� ã��
	polys[index]->terms[polys[index]->nbr_terms]->coef = arg2;	//nbr_terms�� �Լ� �׿��ٰ� ���� ����
	polys[index]->terms[polys[index]->nbr_terms]->expo = arg3;//nbr_terms�� �Լ� �׿��ٰ� ��� ����
	polys[index]->nbr_terms++;	//nbr_terms�� ����
	balance(arg1, polys[index]->nbr_terms);

}

//mult �Լ�
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

//diff�Լ�
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


//print �Լ�
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

//printall �Լ�
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