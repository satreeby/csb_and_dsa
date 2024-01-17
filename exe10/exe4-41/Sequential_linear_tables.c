/*	File: ˳�����Ա�.c
	��ϰ��4-41��˳��洢���Ա��ۺϳ���	*/


#include <stdio.h>
#include <stdlib.h>
#define M 100
void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
void createListS(int a[], int *n)
{
	FILE *fp;
	int  num;
	if((fp = fopen("inList.txt", "r")) == NULL)
		error("�޷����ļ�inList.txt");
	*n = 0;
	while(fscanf(fp, "%d", &num) == 1)
		a[(*n)++] = num;
}
int searchS(int a[], int n, int key) 	/* ���Һ���		*/
{
	int i;
	for(i=0; i<n; i++)
		if(a[i] == key)
			return(i); 	/* ���ҳɹ�	*/
	return(-1);			/* ����ʧ��	*/
}
void addNodeS(int a[], int *n, int here, int key)
{
	int i, j;
	if((i = searchS(a, *n, here)) == -1)
	{
		printf("�޷��ҵ���ǰ���\n");
		return;
	}
	for(j=(*n)-1; j>=i; j--)			/* ���β�ƶ�	*/
		a[j+1] = a[j];
	a[i] = key;							/* ����½��	*/
	(*n)++;								/* �������1	*/
}
void  deleteNodeS(int a[], int *n, int key)
{
	int i, k;
	if((i = searchS(a, *n, key)) == -1)
	{
		printf("�޷��ҵ���ɾ�����\n");
		return;
	}
	for(k=i+1; k<(*n); k++)
		a[k-1] = a[k]; /*��ǰ�ƶ�*/
	(*n)--;
}
void prtListS(int a[], int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("a[%d]=%d ", i, a[i]);
	printf("\n");
}

void ExitTask(void)
{
	printf("�ټ���\n");
	system("pause");
	exit(0);
}
void main()
{
	int a[M], n, i, here, key;
	short MenuItem, nItem;
	char *MenuTitle[] = { "[1] ���ҽ��", 
						  "[2] ������",
						  "[3] ɾ�����",
						  "[4] �������Ա�",
						  "[����] ����"};
	printf("## ˳��洢���Ա��ۺϳ��� ##\n");
	printf("����inList.txt�������Ա�\n");
	createListS(a, &n);
	prtListS(a, n);
	while(1)
	{
		printf("\n");
		for(nItem=0; nItem<5; nItem++)			/* ����˵�ѡ��		*/
			printf("%s\n", MenuTitle[nItem]);
		printf("��ѡ��");
		scanf("%d", &MenuItem);					/* ��������ѡ��		*/
		if(MenuItem == 1)						/* [1] ���ҽ��		*/
		{
			printf("�����ĸ����? key = ");
			scanf("%d", &key);
			if((i = searchS(a, n, key)) == -1)
				printf("����ʧ��\n");
			else
				printf("a[%d] = %d\n", i, key);
		}
		else if(MenuItem == 2)					/* [2] ������		*/
		{ 
			printf("������ֵ? key = ");
			scanf("%d", &key);
			printf("�����ĸ����֮ǰ? here = ");
			scanf("%d", &here);
			addNodeS(a, &n, here, key);
		}
		else if(MenuItem == 3)					/* [3] ɾ�����		*/
		{
			printf("ɾ���ĸ����? key = ");
			scanf("%d", &key);
			deleteNodeS(a, &n, key);
		}
		else if(MenuItem == 4)					/* [4] �������Ա�	*/
			prtListS(a, n);
		else
			error("�ټ���");
	}
}
