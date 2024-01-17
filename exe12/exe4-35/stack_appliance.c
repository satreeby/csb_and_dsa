/* File: ����ջӦ��.c
	����4-12,ϰ��4-35������ջ�Ϳ�ջӦ�ã���·�������	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODE	struct	node
#define M		10
#define MAX		M-1
#define MIN		0
NODE
{
	char key;
	NODE *next;
};
NODE *Free=NULL; 				/* ������ջ��ջ��ָ��	*/
NODE *Top=NULL;
error(char *string)				/* ��������			*/
{
	printf("%s\n", string);
	exit(1);
}
void inputOp(char *op, int n)
{
	int i=0, ch;
	while(i < 2*n)
	{
		if( (ch=getchar()) == EOF)
			break;
		if(ch == 'P' || ch == 'O')
			op[i++] = ch;
	}
	if(i != 2*n || op[0] != 'P' || op[2*n-1] != 'O')
		error("operator error!");
}
void inputData(char *a, int *n)
{
	int i=0;
	char str[10];
	scanf("%d", n);
	for(i=0; i<*n; i++)
	{
		scanf("%s", str);
		a[i] = str[0];
	}
}
void pushFree(NODE *node) 		/* ������ջ�Ľ�ջ����	*/
{
	node->next = Free;
	Free = node;
}
NODE *popFree()					/* ������ջ�ĳ�ջ����	*/
{
	NODE *head; 				/* ��̬����ռ����ָ��	*/
	NODE *node;
	int i;
	if(Free == NULL)
	{
	
		head = (NODE *)malloc(M * sizeof(NODE));	/* ��̬����M�����	*/
		if(head == NULL) 						/* �����				*/
			error("overflow!");
		Free=head;
		for(i=MIN; i<MAX; head++, i++)
			head->next = head + 1; 				/* ��M����㹹������	*/
		head->next = NULL;
	}
	node = Free; 								/* ������ջ�Ľ���ջ	*/
	Free = Free->next;
	return(node);
}
void push(char key)
{
	NODE *node;
	node = popFree();		/* ��ջ��ջ������½��	*/
	node->key = key;
	node->next = Top; 		/* �½���ջ			*/
	Top = node;
}
char pop()
{
	NODE *node;
	char key;
	if(Top == NULL)			/* �����				*/
		error("underflow!");
	key = Top->key;
	node = Top;				/* ɾ��ջ�����			*/
	Top = Top->next;
	pushFree(node); 		/* ��ɾջ��������ջ	*/
	return(key);
}
void stackApp(char *data, char *out, char *op, int n)
{
	int idata=0;			/* ������������ָ��		*/
	int iout=0;				/* �����������ָ��		*/
	int iop;				/* ���������ָ��		*/
	/* complete the follwing code	*/
	
    for ( iop = 0; iop < 2*n; iop++ )
	{
		if ( op[iop] == 'P' )
		{
			push( data[idata++] );
		}
		else
		{
			out[iout++]=pop();
		}
	}
	
	/* --------------------------	*/
	if(idata != n || iout != n)
		error("data error!");
}
void main()
{
	int n, i;
	char data[30];			/* ������������		*/
	char out[30];			/* �����������		*/
	char op[50];			/* ���������		*/
	printf("������������\n");
	inputData(data, &n);
/* ifdebug
	for(i=0; i<n; i++)
		printf("%c ", data[i]);
	printf("\n");
*/
	printf("�����������\n");
	inputOp(op, n);
/* ifdebug
	for(i=0; i<2*n; i++)
		printf("%c ", op[i]);
	printf("\n");
*/
	printf("ջ����\n");
	stackApp(data, out, op, n);
	for(i=0; i<n; i++)
		printf("%c ", out[i]);
	printf("\n");
}
/*
��������
3
3 2 1
�����������
PPOPOO
ջ����
2 1 3

7
B A L E M D F
PPOPOOPPOPPOOO
ջ����
A L B M F D E

6
6 1 9 2 5 3
P P O P O O P P O O P O
ջ����
1 9 6 5 2 3

7
B A L E M D F
PPOPOOPPOPP
^Z
operator error!

6
1 9 2 5 3
P P O P O O P P O O P O
^Z
operator error!

5
O R C I M
P P O P O P P O O O
ջ����
R C M I O

7
B A L E M D F
PPPPOPPOOOPOOO
ջ����
E D M L F A B

7
F D M I C R 0
PPOPOOPPOPPOOO
ջ����
D M F C 0 R I

7 F D M I C R 0
PPPPOPPOOOPOOO
ջ����
I R C M 0 D F

7
F D M E L A B
PPOPOOPPOPPOOO
ջ����
D M F L B A E

7
F D M E L A B
PPPPOPPOOOPOOO
ջ����
E A L M B D F
*/
