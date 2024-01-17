/*	File: ���ڱ�����.c
	��ϰ��4-43�����ڱ������ۺϳ���
	����ļ���deleteNodeL.c	*/

#include <stdio.h>
#include <stdlib.h>
#define NODE struct node
NODE
{
	int num;
	NODE  *next; 
};
void deleteNodeL(NODE *, int);

void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
void createListL(NODE *head)
{
	FILE *fp;
	NODE *node;
	int  num; 
	if((fp = fopen("inList.txt", "r")) == NULL)
		error("�޷����ļ�inList.txt");
	while(fscanf(fp, "%d", &num) == 1)
	{
		if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
			error("�ڴ����ʧ��");
		node->num = num;
		node->next = head->next;
		head->next = node;
	}
}
NODE *searchL(NODE *head, int key)
{
	NODE *node;
	for(node=head->next; node; node=node->next)
		if(node->num == key)
			return(node); 		/* ���ҳɹ�		*/
	return(NULL);				/* ����ʧ��		*/
}
void addNodeL(NODE *head, int here, int key)
{
	NODE *prev, *node;
	for(prev=head; prev->next; prev=prev->next)
	{
		if(prev->next->num == here)
		{
			if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
				error("�ڴ����ʧ��"); 
			node->num = key;	
			node->next = prev->next;	
			prev->next = node;	
			return;
		}
	}
	printf("�޷�ȷ������λ��\n");
	return;
}
void deleteNodeL(NODE *head, int key)
{
	NODE *prev, *node;
	/* �������³���		*/
	for (prev = head; prev->next; prev=prev->next)
	{
		if (prev->next->num == key)
		{
			node = prev->next;
			prev->next = node->next;
			free(node);
			return;
		}
	}
	printf("��ɾ����㲻����\n"); 
	return;
}
void prtListL(NODE *first)
{
	NODE *node;
	for(node=first; node; node=node->next)
		printf("%d ", node->num);
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
	NODE *Head=NULL, *Tail=NULL, *node;
	int key, here;
	short MenuItem, nItem;
	char *MenuTitle[] = { "[1] ���ҽ��", 
						  "[2] ������",
						  "[3] ɾ�����",
						  "[4] �������Ա�",
						  "[����] ����"};
	if( (Head = (NODE *)(malloc(sizeof(NODE))) )== NULL) /* �����ڱ�*/
		error("�ڴ����ʧ��");
	Head->next = NULL;
	printf("## ���ڱ������ۺϳ��� ##\n");
	printf("����inList.txt��������\n");
	createListL(Head);
	prtListL(Head->next);
	while(1)
	{
		printf("\n");
		for(nItem=0; nItem<5; nItem++)			/* ����˵�ѡ��		*/
			printf("%s\n", MenuTitle[nItem]);
		printf("��ѡ��");
		scanf("%d", &MenuItem);					/* ��������ѡ��		*/
		if(MenuItem == 1)						/* [1] ���ҽ��		*/
		{
			printf("������ֵ? key = ");
			scanf("%d", &key);
			if((node = searchL(Head, key)) == NULL)
				printf("����ʧ��\n");
			else
				printf("node = %d\n", node->num);
		}
		else if(MenuItem == 2)					/* [2] ������		*/
		{ 
			printf("������ֵ? key = ");
			scanf("%d", &key);
			printf("�����ĸ����֮ǰ? here = ");
			scanf("%d", &here);
			addNodeL(Head, here, key);
		}
		else if(MenuItem == 3)					/* [3] ɾ�����		*/
		{
			printf("ɾ���ĸ����? key = ");
			scanf("%d", &key);
			deleteNodeL(Head, key);
		}
		else if(MenuItem == 4)					/* [4] �������Ա�	*/
			prtListL(Head->next);
		else
			error("�ټ���");
	}
}
