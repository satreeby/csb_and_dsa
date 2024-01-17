/*	File: ѭ�����к���.c
	��ϰ��4-36�����ζ��У�����ͼ
	����ļ���ѭ������Ӧ��.c	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define F struct inheritor
#define	M		10		/* ��������			*/
#define	MAX	 	M-1 	/* ��βָ������ֵ */
#define	EMPTY	-1		/* �ն�ָ��ֵ		*/
F						/* ����(family)��Ϣ	*/
{
	int	n;				/* ���˱��(number)	*/
	int g;				/* ����(generation)	*/
	int p;				/* ��ĸ���(parent)	*/
	F *next;
};
F *Head;			/* ��������				*/
F *Clan;			/* ��������				*/
F *Q[M];			/* ���ζ���ָ������		*/
int	Top=EMPTY; 		/* ����ָ�룬��ʼΪ�ն�	*/
int	Tail=EMPTY; 	/* ��βָ�룬��ʼΪ�ն�	*/

void error(char *error_msg)	/* ��������		*/
{
	printf("**** %s ****\n", error_msg);
	exit(0);
}
void enCircle(F *node)		/* ���ζ��н��Ӻ���	*/
{
	if((Tail+1) % M == Top)	
		error("�����(overflow)"); 	/* �����(overflow)	*/
	if(Top<EMPTY || Top>MAX || Tail<EMPTY || Tail>MAX)
		error("�Ƿ�����"); 			/* �Ƿ�				*/
	/* ���¶���ָ��			*/
	Tail = (Tail + 1) % M; 
	if(Top == EMPTY)
		Top = Tail;					/* �նӽ���			*/
	Q[Tail] = node;					/* ������������		*/
}
F *deCircle(void)			/* ���ζ��г��Ӻ���	*/
{
	F *node;
	if(Top<EMPTY || Top>MAX || Tail<EMPTY || Tail>MAX)
		error("�Ƿ�����");			/* �Ƿ�				*/
	if(Top == EMPTY)
		return(NULL); 				/* �����(underflow)*/
	node = Q[Top];
	/* ���¶���ָ��			*/
	if(Top != Tail)					/* ��������			*/
		Top = (Top + 1) % M;
	else  							/* ���գ���Ϊ�ն�	*/
		Top = Tail = EMPTY;
	return(node); 
}
void input(void)			/* ��ʼ������Ϣ�ĺ���	*/
{
	int	n, g, p;
	F *node;
	FILE *fp;
	char filename[60];
	printf("�����ĸ��ļ�: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		error("cannot open file");
	/*	�������������ڱ�			*/
	Head = (F *)malloc(sizeof(F));
	if(Head == NULL)
		error("no space");
	Head->next = NULL;
	/*	���ü��������ڱ�			*/
	Clan = (F *)malloc(sizeof(F));
	if(Clan == NULL)
		error("no space");
	Clan->next = NULL;
	/*	����������Ϣ��������������	*/
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
void prt(F *head)			/* ��ӡ����ĺ���		*/
{
	F *node;
	for(node=head->next; node; node=node->next)
	printf("n=%-4dg=%-4dp=%-4d\n",
			node->n, node->g, node->p);
}
void prtClan(F *clan)		/* ��ӡ����ͼ�ĺ���		*/
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
