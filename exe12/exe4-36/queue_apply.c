/*	File: 循环队列应用.c
	【习题4-36】环形队列：家谱图
	相关文件：循环队列函数.c	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue_func.c"
//#define F struct family
//F						/* 家族(family)信息	*/
//{
//	int	n;				/* 族人编号(number)	*/
//	int g;				/* 辈分(generation)	*/
//	int p;				/* 父母编号(parent)	*/
//	F *next;
//}; 
//
F *Head;				/* 族人链表			*/
F *Clan;				/* 家谱链表			*/
void error(char *);
void enCircle(F *);
F *deCircle(void);
void input(void);
void prt(F *);
void prtClan(F *);

void GetClan(void)		/* 获取家谱链表函数	*/
{
	int h=1, g=1;
	F *child, *node, *prev;
	/* 在族人链表中删除先祖，进队		*/
	node = Head->next;
	Head->next = node->next;
	enCircle(node);
	while((node = deCircle()) != NULL)	/* 只要队非空	*/
	{
		/* 从族人链表中删除node的所有子女，逐个进队*/
		for (prev=Head; prev->next; )
		{
			if (prev->next->p == node->n)
			{
				child = prev->next;
				prev->next = child->next;
				enCircle(child);
			}
			else
				prev=prev->next;
		}
		/* --------------------------	*/
		/* 将node插入家谱链表			*/
		for(prev=Clan; prev->next; prev=prev->next)
			if(prev->next->n == node->p)
				break;
		/* complete the follwing code	*/
		if(prev->next){
			node->next = prev->next->next;
			prev->next->next = node;
		}
		else{
			node->next = prev->next;
			prev->next = node;
		}
		/* --------------------------	*/
	}
}
void main()
{
	input(); 				/* 输入族人信息	*/
	printf("族人链表：\n");	/*	if debug	*/
	prt(Head);				/*	if debug	*/
	GetClan();				/* 获取家谱链表	*/
	printf("家谱链表：\n");	/*	if debug	*/
	prt(Clan);				/*	if debug	*/
	printf("家谱图：\n");
	prtClan(Clan);			/* 打印家谱图	*/
	system("pause");
}
/*
输入哪个文件: clan1.txt
家谱图：
14, 1, 0  12, 2,14  11, 3,12
________  ________  13, 3,12
________  16, 2,14
________  20, 2,14  15, 3,20
________  ________  18, 3,20
________  ________  17, 3,20

输入哪个文件: clan2.txt
家谱图：
24, 1, 0  11, 2,24  12, 3,11  19, 4,12  16, 5,19
________  ________  ________  ________  27, 5,19
________  ________  ________  29, 4,12  25, 5,29
________  ________  18, 3,11  37, 4,18  22, 5,37
________  ________  21, 3,11  20, 4,21  13, 5,20
________  ________  ________  31, 4,21
________  ________  35, 3,11
________  28, 2,24  15, 3,28
________  ________  17, 3,28  30, 4,17  14, 5,30
________  ________  ________  33, 4,17
________  ________  39, 3,28  34, 4,39  38, 5,34
________  32, 2,24  26, 3,32  36, 4,26  23, 5,36
*/
