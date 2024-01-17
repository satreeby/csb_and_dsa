/* File: 链接栈应用.c
	【例4-12,习题4-35】链接栈和空栈应用：铁路车厢编组	*/
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
NODE *Free=NULL; 				/* 空链表栈的栈顶指针	*/
NODE *Top=NULL;
error(char *string)				/* 出错处理函数			*/
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
void pushFree(NODE *node) 		/* 空链表栈的进栈函数	*/
{
	node->next = Free;
	Free = node;
}
NODE *popFree()					/* 空链表栈的出栈函数	*/
{
	NODE *head; 				/* 动态分配空间的首指针	*/
	NODE *node;
	int i;
	if(Free == NULL)
	{
	
		head = (NODE *)malloc(M * sizeof(NODE));	/* 动态申请M个结点	*/
		if(head == NULL) 						/* 上溢出				*/
			error("overflow!");
		Free=head;
		for(i=MIN; i<MAX; head++, i++)
			head->next = head + 1; 				/* 将M个结点构成链表	*/
		head->next = NULL;
	}
	node = Free; 								/* 空链表栈的结点出栈	*/
	Free = Free->next;
	return(node);
}
void push(char key)
{
	NODE *node;
	node = popFree();		/* 空栈出栈，获得新结点	*/
	node->key = key;
	node->next = Top; 		/* 新结点进栈			*/
	Top = node;
}
char pop()
{
	NODE *node;
	char key;
	if(Top == NULL)			/* 下溢出				*/
		error("underflow!");
	key = Top->key;
	node = Top;				/* 删除栈顶结点			*/
	Top = Top->next;
	pushFree(node); 		/* 已删栈顶结点进空栈	*/
	return(key);
}
void stackApp(char *data, char *out, char *op, int n)
{
	int idata=0;			/* 输入数据数组指针		*/
	int iout=0;				/* 输出数据数组指针		*/
	int iop;				/* 运算符数组指针		*/
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
	char data[30];			/* 输入数据数组		*/
	char out[30];			/* 输出数据数组		*/
	char op[50];			/* 运算符数组		*/
	printf("输入数据序列\n");
	inputData(data, &n);
/* ifdebug
	for(i=0; i<n; i++)
		printf("%c ", data[i]);
	printf("\n");
*/
	printf("输入操作序列\n");
	inputOp(op, n);
/* ifdebug
	for(i=0; i<2*n; i++)
		printf("%c ", op[i]);
	printf("\n");
*/
	printf("栈操作\n");
	stackApp(data, out, op, n);
	for(i=0; i<n; i++)
		printf("%c ", out[i]);
	printf("\n");
}
/*
输入数据
3
3 2 1
输入操作序列
PPOPOO
栈操作
2 1 3

7
B A L E M D F
PPOPOOPPOPPOOO
栈操作
A L B M F D E

6
6 1 9 2 5 3
P P O P O O P P O O P O
栈操作
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
栈操作
R C M I O

7
B A L E M D F
PPPPOPPOOOPOOO
栈操作
E D M L F A B

7
F D M I C R 0
PPOPOOPPOPPOOO
栈操作
D M F C 0 R I

7 F D M I C R 0
PPPPOPPOOOPOOO
栈操作
I R C M 0 D F

7
F D M E L A B
PPOPOOPPOPPOOO
栈操作
D M F L B A E

7
F D M E L A B
PPPPOPPOOOPOOO
栈操作
E A L M B D F
*/
