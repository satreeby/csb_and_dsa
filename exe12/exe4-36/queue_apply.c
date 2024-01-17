/*	File: ѭ������Ӧ��.c
	��ϰ��4-36�����ζ��У�����ͼ
	����ļ���ѭ�����к���.c	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue_func.c"
//#define F struct family
//F						/* ����(family)��Ϣ	*/
//{
//	int	n;				/* ���˱��(number)	*/
//	int g;				/* ����(generation)	*/
//	int p;				/* ��ĸ���(parent)	*/
//	F *next;
//}; 
//
F *Head;				/* ��������			*/
F *Clan;				/* ��������			*/
void error(char *);
void enCircle(F *);
F *deCircle(void);
void input(void);
void prt(F *);
void prtClan(F *);

void GetClan(void)		/* ��ȡ����������	*/
{
	int h=1, g=1;
	F *child, *node, *prev;
	/* ������������ɾ�����棬����		*/
	node = Head->next;
	Head->next = node->next;
	enCircle(node);
	while((node = deCircle()) != NULL)	/* ֻҪ�ӷǿ�	*/
	{
		/* ������������ɾ��node��������Ů���������*/
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
		/* ��node�����������			*/
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
	input(); 				/* ����������Ϣ	*/
	printf("��������\n");	/*	if debug	*/
	prt(Head);				/*	if debug	*/
	GetClan();				/* ��ȡ��������	*/
	printf("��������\n");	/*	if debug	*/
	prt(Clan);				/*	if debug	*/
	printf("����ͼ��\n");
	prtClan(Clan);			/* ��ӡ����ͼ	*/
	system("pause");
}
/*
�����ĸ��ļ�: clan1.txt
����ͼ��
14, 1, 0  12, 2,14  11, 3,12
________  ________  13, 3,12
________  16, 2,14
________  20, 2,14  15, 3,20
________  ________  18, 3,20
________  ________  17, 3,20

�����ĸ��ļ�: clan2.txt
����ͼ��
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
