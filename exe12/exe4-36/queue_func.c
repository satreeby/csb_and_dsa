/*	File: 循环队列函数.c
	【习题4-36】环形队列：家谱图
	相关文件：循环队列应用.c	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define F struct inheritor
#define	M		10		/* 队列容量			*/
#define	MAX	 	M-1 	/* 队尾指针的最大值 */
#define	EMPTY	-1		/* 空队指针值		*/
F						/* 家族(family)信息	*/
{
	int	n;				/* 族人编号(number)	*/
	int g;				/* 辈分(generation)	*/
	int p;				/* 父母编号(parent)	*/
	F *next;
};
F *Head;			/* 族人链表				*/
F *Clan;			/* 家谱链表				*/
F *Q[M];			/* 环形队列指针数组		*/
int	Top=EMPTY; 		/* 队首指针，初始为空队	*/
int	Tail=EMPTY; 	/* 队尾指针，初始为空队	*/

void error(char *error_msg)	/* 出错处理函数		*/
{
	printf("**** %s ****\n", error_msg);
	exit(0);
}
void enCircle(F *node)		/* 环形队列进队函数	*/
{
	if((Tail+1) % M == Top)	
		error("上溢出(overflow)"); 	/* 上溢出(overflow)	*/
	if(Top<EMPTY || Top>MAX || Tail<EMPTY || Tail>MAX)
		error("非法进队"); 			/* 非法				*/
	/* 更新队列指针			*/
	Tail = (Tail + 1) % M; 
	if(Top == EMPTY)
		Top = Tail;					/* 空队进队			*/
	Q[Tail] = node;					/* 包括正常进队		*/
}
F *deCircle(void)			/* 环形队列出队函数	*/
{
	F *node;
	if(Top<EMPTY || Top>MAX || Tail<EMPTY || Tail>MAX)
		error("非法出队");			/* 非法				*/
	if(Top == EMPTY)
		return(NULL); 				/* 下溢出(underflow)*/
	node = Q[Top];
	/* 更新队列指针			*/
	if(Top != Tail)					/* 正常出队			*/
		Top = (Top + 1) % M;
	else  							/* 出空：成为空队	*/
		Top = Tail = EMPTY;
	return(node); 
}
void input(void)			/* 初始输入信息的函数	*/
{
	int	n, g, p;
	F *node;
	FILE *fp;
	char filename[60];
	printf("输入哪个文件: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		error("cannot open file");
	/*	设置族人链表哨兵			*/
	Head = (F *)malloc(sizeof(F));
	if(Head == NULL)
		error("no space");
	Head->next = NULL;
	/*	设置家谱链表哨兵			*/
	Clan = (F *)malloc(sizeof(F));
	if(Clan == NULL)
		error("no space");
	Clan->next = NULL;
	/*	输入族人信息，插入族人链表	*/
	while(fscanf(fp, "%d%d%d", &n, &g, &p) == 3)
	{
		node = (F *)malloc(sizeof(F));
		if(node == NULL)
			error("no space");
		node->n = n;
		node->g = g;
		node->p = p;
		node->next = Head->next;
		Head->next = node;
	}
}
void prt(F *head)			/* 打印链表的函数		*/
{
	F *node;
	for(node=head->next; node; node=node->next)
	printf("n=%-4dg=%-4dp=%-4d\n",
			node->n, node->g, node->p);
}
void prtClan(F *clan)		/* 打印家谱图的函数		*/
{
	int i;
	F *node;
	for(node=Clan; node->next; node=node->next)
	{
		if(node->next && node->g >= node->next->g)
		{
			for(i=1; i<node->next->g; i++)
				printf("________  ");
		}
		printf("%2d,%2d,%2d  ", 
			node->next->n, node->next->g, node->next->p);
		if(node->next->next == NULL || 
			node->next->g >= node->next->next->g)
			printf("\n");
	}
}
