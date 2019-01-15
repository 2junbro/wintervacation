#pragma warning (disable: 4996)//4-2 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#define capacity 100 
#define buffer_length 100 
#define MAX 100 
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 

typedef struct term {   // 하나의 항을 표현하는 구조체         
	int coef;    // 계수 
	int expo;    // 차수     
} term;

typedef struct polynomial {  // 하나의 다항식을 표현하기 위한 구조체 
	char name;    // f, g, h등의 다항식의 이름     
	int nbr_terms;   // 이 다항식을 구성하는 항의 개수  
	term *terms[MAX];  // MAX는 100정도로 한다.      
} polynomial;

polynomial *polys[MAX];   // 여러 개의 다항식을 저장하기위한 배열    

int n = 0;      // 다항식의 개수  

int read_line(FILE * fp, char str[], int n);
//다항식은 싸그리 전역변수로 써서 반환값은 굳이 없어도 됨 
int create(char *b);//입력덩어리 한개 있는지없는지 반환 
void add(char *b);//입력 덩어리 세개 
void mult(char *b);//입력덩어리 두개 
void calc(char *b);//입력덩어리 두개-함수값출력 
void diff(char *b);//입력덩어리 네개 as포함 
void print(char *b);//입력덩어리 한개 

int main() {
	char command_line[buffer_length];//읽을 한줄 
	char *command;
	//memset(polys, 0, sizeof(polys)); 
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	while (1)
	{
		printf("$ ");
		if (read_line(stdin, command_line, buffer_length) <= 0)
			continue;
		command = strtok(command_line, " ");

		char *b = command_line + strlen(command) + 1;

		if (strcmp(command, "create") == 0) {
			//char name = *b; 
			create(b);
		}
		else if (strcmp(command, "add") == 0) {
			add(b);
		}
		else if (strcmp(command, "mult") == 0) {
			mult(b);
		}
		else if (strcmp(command, "calc") == 0) {
			calc(b);
		}
		else if (strcmp(command, "diff") == 0) {
			diff(b);
		}
		else if (strcmp(command, "print") == 0) {
			print(b);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			free(polys[i]->terms[j]);
		}
		free(polys[i]);
	}
	return 0;
}
/*컨트롤할 전역변수
polynomial polys[MAX];   // 여러 개의 다항식을 저장하기위한 배열
int n;      // 다항식의 개수
char name;    // f, g, h등의 다항식의 이름
int nbr_terms;   // 이 다항식을 구성하는 항의 개수
term terms[MAX]
int coef;    // 계수
int expo;    // 차수
*/
int read_line(FILE * fp, char str[], int n)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
	return i;
}
int create(char *b)//check 
{//이미 선언된것이 있는지 검사 
	for (int i = 0; i < n; i++)
	{
		if (*b == polys[i]->name)
		{
			printf("이미 선언된 함수입니다.\n");
			return 0;
		}
	}
	polys[n] = (polynomial *)malloc(sizeof(polynomial));
	memset(polys[n], 0, sizeof(polynomial));

	for (int i = 0; i < MAX; i++) {
		polys[n]->terms[i] = (term *)malloc(sizeof(term));
		memset(polys[n]->terms[i], 0, sizeof(term));
	}
	polys[n]->name = *b;  //할당되지않은 메모리 참조 why? 
	n++;
	return 1;
}
void add(char *b) {
	char token = *strtok(b, " ");//함수이름이 저장될것이다. 
	int index = -1;
	int coef;//차수 
	int expo;//계수 

	while (token != polys[++index]->name)//index찾기, 같을때 반복문을 탈출한다. 
	{
	}
	coef = atoi(strtok(NULL, " "));// 계수가 들어간다 
	expo = atoi(strtok(NULL, " "));//차수저장 
	if (polys[index]->terms[expo]->coef == 0)//오류 
		polys[index]->nbr_terms++;
	polys[index]->terms[expo]->coef += coef;//계수 
	polys[index]->terms[expo]->expo = expo;//차수 
	return;
}
void mult(char *b) {//check 
	int count = 0;//곱해진 항의 갯수를 카운트한다 
	char token = *strtok(b, " ");//함수이름이 저장될것이다. 
	int number = atoi(strtok(NULL, " ")); //곱할 계수가 저장된다. 
	int index = -1;
	while (token != polys[++index]->name)//index찾기, 같을때 반복문을 탈출한다. 
	{
	}
	int i = 0;
	while (!(count == polys[index]->nbr_terms))//같을때 탈출 
	{

		if (polys[index]->terms[i]->coef != 0)//0이아닐때 
		{
			polys[index]->terms[i]->coef *= number;
			count++;
		}
		i++;
	}
	return;
}
void calc(char *b) //입력덩어리 두개 - 함수값출력//check 
{

	char token = *strtok(b, " ");//함수이름이 저장될것이다. 
	int x = atoi(strtok(NULL, " ")); //x값이 저장된다. 
	int number = 1, tot = 0;//tot 토탈값 , number 한차수에서의 값 
	int count = 0;
	int index = -1;
	while (token != polys[++index]->name)//index찾기, 같을때 반복문을 탈출한다. 
	{
	}
	int it = 0;
	while (!(count == polys[index]->nbr_terms))//같을때 탈출 
	{


		if (polys[index]->terms[it]->coef != 0)//0이아닐때 
		{
			number *= polys[index]->terms[it]->coef;//계수를 곱한다. 
			for (int i = 1; i <= polys[index]->terms[it]->expo; i++)
			{
				number *= x; //차수수만큼 곱한다. 
			}
			count++;
			tot += number;
			number = 1;
		}
		it++;
	}
	printf("%c(%d) = %d\n", polys[index]->name, x, tot);
	return;
}
void diff(char *b) {//미분  
	char token1 = *strtok(b, " ");//원함수 
	char *as = strtok(NULL, " ");//as 
	char *token2 = strtok(NULL, " ");//미분함수 
	if (create(token2))//create(h) 
	{
		int index = -1;//원함수 인덱스 
		while (index < MAX)
		{
			if (token1 == polys[++index]->name)
				break;
			index++;
		}
		if (index == MAX)
			return;
		int count = 0;

		for (int i = 1; count != polys[index]->nbr_terms; i++)
		{
			if ((polys[index]->terms[i]->coef) != 0)
			{
				polys[n - 1]->terms[i - 1]->expo = i - 1;
				polys[n - 1]->terms[i - 1]->coef = i * (polys[index]->terms[i]->coef);
				polys[n - 1]->nbr_terms++;
				count++;
			}
		}
	}
	return;
}
void print(char *b) {//check 
	char *token = strtok(b, " ");//함수이름이 저장될것이다. 
	if (strcmp(token, "all") == 0)//같은경우 0반환 전체 출력 
	{
		for (int i = 0; i < n; i++)
		{
			printf("%c(x): ", polys[i]->name);
			char *function = &polys[i]->name;
			print(function);//재귀함수 구현 
		}
	}

	else //부분함수만 출력 
	{
		int index = -1;

		while (*token != polys[++index]->name)//index찾기, 같을때 반복문을 탈출한다. 
		{
		}// 전체출력일때는 불필요한 부분이라 약간 비효율적이다. 
		 //문자열로 만들어서 출력할까? 한자씩 출력하게 할까? 
		int MAX_index = 0;
		//항수를 세서 확인하는용 
		for (int i = 0, count = 0; i < MAX; i++)//i는 여기서 최고차항 계수이다. 
		{
			if (polys[index]->terms[i]->coef != 0 && MAX_index < i)
			{
				MAX_index = i;
				count++;
			}
			if (count == polys[index]->nbr_terms)
				break;
		}//MAX_index를 구했다. 
		if (MAX_index != 0)//첫항 출력 
		{
			if (polys[index]->terms[MAX_index]->coef != 1)// 1구분 
				printf("%dx^%d",
					polys[index]->terms[MAX_index]->coef, polys[index]->terms[MAX_index]->expo);
			else
			{
				printf("x^%d",
					polys[index]->terms[MAX_index]->expo);
			}//인덱스가 0이 아니고 계수가 1일때 계수는 생략한다. 
		}//계수, x^차수 
		else//MAX_index =0일경우 
		{
			printf("%d\n", polys[index]->terms[MAX_index]->coef);
			return;
		}
		if (1 == polys[index]->nbr_terms)
		{
			printf("\n");
			return;
		}MAX_index--;
		for (int count = 1; ; )
		{
			if (polys[index]->terms[MAX_index]->coef != 0 && MAX_index != 0)
			{
				if (polys[index]->terms[MAX_index]->coef > 0)
				{
					if (polys[index]->terms[MAX_index]->coef != 1)
						printf("+%dx^%d",
							polys[index]->terms[MAX_index]->coef, polys[index]->terms[MAX_index]->expo);
					else
					{
						printf("+x^%d",
							polys[index]->terms[MAX_index]->expo);
					}//인덱스가 0이 아니고 계수가 1일때 계수는 생략한다. 

				}
				else //(polys[index]->terms[MAX_index].coef<0)//양음 출력이다르다 
				{
					printf("%dx^%d",
						polys[index]->terms[MAX_index]->coef, polys[index]->terms[MAX_index]->expo);
				}
				count++;
			}
			else if ((polys[index]->terms[MAX_index]->coef != 0 && MAX_index == 0))//자연수출력 
			{
				if (polys[index]->terms[MAX_index]->coef > 0)//양음 구분 
				{
					printf("+%d",
						polys[index]->terms[MAX_index]->coef);
				}
				else
				{
					printf("%d",
						polys[index]->terms[MAX_index]->coef);
				}
				count++;
			}//0일때 차수를 빼고 출력후 바로 리턴 

			if (count == polys[index]->nbr_terms)
				break;
			MAX_index--;
		}
		printf("\n");
	}
	return;
}