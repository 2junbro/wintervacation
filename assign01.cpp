//1��
/*
#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
int main()
{
	FILE *in_fp = fopen("harry.txt", "r");
	FILE *out_fp = fopen("words.txt", "w");
	char buffer[100];
	char *arr[10];
	int stop = 0,j=0;
	while (fscanf(in_fp, "%s", buffer) != EOF)
	{
		printf("%s ", buffer);
		for (int i = 0; i < 10; i++)
		{
			if (arr[i] == buffer) {
				stop = 1;
				break;
			}
		}

		if (stop != 1) {
			arr[j] = buffer;
			fprintf(out_fp, "%s\n", arr[j]);
			j++;
		}
		printf("%d", j);

		stop = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("\n���%s", arr[i]);
	}
	fclose(in_fp);
	fclose(out_fp);
}
*/



//������ �迭 const �̿�
/*
#include<stdio.h>
int main() {
	char *arr[3];
	arr[0] = "blue";
	arr[1] = "yellow";
	arr[2] = "green";
	for (int i = 0; i < 3; i++) {
		printf("%s\n", arr[i]);
	}
	getchar();
	return 0;

}
*/

//�����͹迭 �����Ҵ� �̿� �̰ɷ��ϱ�
/*
#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char * arr[10];
	char tmp[30];
	int len, i=0;

	FILE *in_fp = fopen("harry.txt", "r");
	FILE *out_fp = fopen("words.txt", "w");

	while (fscanf(in_fp, "%s", tmp) != EOF)
	{
		len = strlen(tmp) + 1;

		arr[i] = (char *)malloc(sizeof(char) * len);
		int stop = 0;

		for (int j = 0; j < 10; j++)
		{
			stop = 0;

			//??
			printf("\n�̰�?:%s", arr[1]);
			//���� �̺κ��� ���� ���� ���ľ��� �ߺ����� ��� �ذ�?&&�־??
			if (strcmp(*arr,tmp)==0) {
				stop = 1;
				break;
			}
		}

		if (stop != 1) {
			strcpy(arr[i], tmp);
			printf("%s\n", arr[i]);
			fprintf(out_fp, "%s\n", arr[i]);
			i++;
		}
	}
	fclose(in_fp);
	fclose(out_fp);
}
*/


//�̰�
/*
#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char * arr[10];
	char tmp[30];
	int stop[10] = { 0 };

	FILE *in_fp = fopen("harry.txt", "r");
	FILE *out_fp = fopen("words.txt", "w");

	int i = 0;
	while (fscanf(in_fp, "%s", tmp) != EOF)
	{
		printf("%d", i);
		printf("%s\n", tmp);

		//���� �̺κ��� ���� ���� ���ľ��� �ߺ����� ��� �ذ�?&&�־??
		for (int j = 0; j < i+1; j++)
		{
			if (arr[j]==tmp) {
				stop[i]++;
				break;
			}
		}

		if (stop[i] == 0) {
			arr[i] = tmp;
		}
		i++;
	}
	int compare = 0;
	char temp[10];
	int j = 10;
	for (i = 0; i < j; i++) {
		for (int k = 0; k < j - 1; k++) {
			compare = strcmp(arr[k], arr[k + 1]);
			if (compare > 0) {
				strcpy(temp, arr[k + 1]);
				strcpy(arr[k + 1], arr[k]);
				strcpy(arr[k], temp);
			}
		}
	}

	for(int i=0;i<10;i++)
	fprintf(out_fp, "%s\n", arr[i]);
	
	fclose(in_fp);
	fclose(out_fp);
}
*/


//2�� 
/*
#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
int main()
{
	//�ܾ� �о����
	FILE *fp = fopen("harray.txt", "r");
	char buffer[100];
	while (fscanf(fp, "%s", buffer) != EOF)
	fclose(fp);
	//�ܾ��� ���� ���
	int leng = 0;
	for (int i = 0; i < 100; i++)
	{
		if (buffer[i] == 0)
			break;
		else
			leng++;
	}
	printf("����:%d\n", leng);

	//1���ε� �� ����
	int ans[100] = { 0 };
	for (int i = 0; i < leng; i++)
	{
		ans[i] = 1;
	}
	//�ܾ� ������ ���
	int last = 0;
			int stop = 0;

	while (stop==0)
	{
		int end = 0;
		char check;
		scanf("%c", &check);
		printf("%c\n", check);
		//�ܾ� �ִ��� üũ
		for (int i = 0; i < leng; i++)
		{
			//�ܾ� ������ 2�� �ǰ�
			if (check == buffer[i])
				ans[i] = 2;
		}
		//�����ֱ�
		for (int i = 0; i < leng; i++)
		{
			if (ans[i] == 2)
				printf("%c", buffer[i]);
			else
				printf("*");
		}
		//��� ã�Ҵ��� üũ
		char stop1;
		for (int i = 0; i < leng; i++)
		{
			if (ans[i] == 2)
				end++;
			if (end == leng)
			{
				printf("��� �Ͻðڽ��ϱ�?(y/n)");
				scanf("%c", &stop1);
				//�̰� �� �ȸ���????
				if (stop1 == 'n') {
					break;
				}
				else
					for (int i = 0; i < leng; i++)
					{
						ans[i] = 1;
					}
			}
		}
	}
}
*/

//3�� 
/*
#pragma warning(disable:4996)
#include<stdio.h>
int main() {
	FILE *in_fp = fopen("tabular.txt", "r");
	FILE *out_fp = fopen("output.txt", "w");
	char buffer[100];
	int m = 0, n = 0;
	fscanf(in_fp, "%d ", &m);
	fscanf(in_fp, "%d ", &n);
	while (fscanf(in_fp, "%s ", buffer) != EOF)
	{
		if (*buffer == '&')
			fprintf(out_fp, "\t\t", buffer);
		else if (*buffer == '\\')
			fprintf(out_fp, "\n", buffer);
		else 
			fprintf(out_fp, "%s ", buffer);
	}
	fclose(in_fp);
	fclose(out_fp);
}
*/

