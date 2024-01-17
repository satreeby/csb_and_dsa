/*	File: ���ڱ�����.c
	��ϰ��4-42�����ڱ������ۺϳ���
	����ļ���addNodeL.c	*/

#include <stdio.h>
#include <stdlib.h>
#define NODE struct node

NODE
{
	int num;
	NODE  *next; 
};


void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
NODE *createListL(NODE *first)
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
		node->next = first;
		first = node;
	}
	return(first);
}
NODE *searchL(NODE *first, int key)
{
	NODE *node;
	for(node=first; node; node=node->next)
		if(node->num == key)
			return(node); 		/* ���ҳɹ�		*/
	return(NULL);				/* ����ʧ��		*/
}
NODE *deleteNodeL(NODE *first, int key)
{
	NODE *prev, *node;
	if(first == NULL)
		return(first);
	if(first->num == key)
	{
		node = first;
		first = node->next;
		free(node);
		return(first);
	}
	for(prev=first; prev->next; prev=prev->next)
	{
		if(prev->next->num == key)
		{
			node = prev->next;	
			prev->next = node->next;	
			free(node);
			return(first);
		}
	}
	printf("��ɾ����㲻����\n");
	return(first);
}

NODE *addNodeL(NODE *first, int here, int key)
{
	NODE *prev, *node;
	/* �������³���		*/
	if (first == NULL)
	{
		printf("�޷�ȷ������λ��\n");
		return(first);
	}
	if(first->num == here)
	{
		if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
			error("�ڴ����ʧ��"); 
		node->num = key;	
		node->next = first;	
		return(node);
	}
	for(prev=first; prev->next; prev=prev->next)
	{
		if(prev->next->num == here)
		{
			if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
				error("�ڴ����ʧ��"); 
			node->num = key;	
			node->next = prev->next;	
			prev->next = node;	
			return(first);
		}
	}
	printf("�޷�ȷ������λ��\n");
	return(first);

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
	NODE *First=NULL, *Tail=NULL, *node;
	int key, here;
	short MenuItem, nItem;
	char *MenuTitle[] = { "[1] ���ҽ��", 
						  "[2] ������",
						  "[3] ɾ�����",
						  "[4] �������Ա�",
						  "[����] ����"};
	printf("## ���ڱ������ۺϳ��� ##\n");
	printf("����inList.txt��������\n");
	First = createListL(First);
	prtListL(First);
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
			if((node = searchL(First, key)) == NULL)
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
			First = addNodeL(First, here, key);
		}
		else if(MenuItem == 3)					/* [3] ɾ�����		*/
		{
			printf("ɾ���ĸ����? key = ");
			scanf("%d", &key);
			First = deleteNodeL(First, key);
		}
		else if(MenuItem == 4)					/* [4] �������Ա�	*/
			prtListL(First);
		else
			error("�ټ���");
	}
}
