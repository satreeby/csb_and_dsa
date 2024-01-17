/*	File: order2tree.c
	[��4-20] ����ǰ�������������ɶ�����	*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define M 	30
#define NODE struct node
NODE
{
	char key;
	NODE *left, *right;
};
	
NODE *Root=NULL;
char Pre[M], Sym[M];

void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
/* �ݹ鷽����ǰ���������		*/
void preOrder(NODE *node)
{
	if(!node)
		return;
	printf("%c ", node->key); 
	preOrder(node->left);
	preOrder(node->right);
}
/* �ݹ鷽���������������		*/
void symOrder(NODE *node)
{
	if(!node)
		return;
	symOrder(node->left);
	printf("%c ", node->key); 
	symOrder(node->right);
}
/* �ݹ鷽���ĺ����������		*/
void postOrder(NODE *node)
{
	if(!node)
		return;
	postOrder(node->left);
	postOrder(node->right);
	printf("%c ", node->key); 
}
int rootInSym(int s1, int s2, char key)
{	/* �������ַ�������Ѱ�����ĸ���key��	*/
	int i;
	for(i=s1; i<=s2; i++)
		if( Sym[i] == key )		
			return(i);	
	error("no root in Sym");
	return(-1);
}
NODE *MakeTree(int p1, int p2, int s1, int s2)
{
	NODE *node;
	int r;
	if(p1 > p2 || s1 > s2)
		return(NULL);
	if ((node =(NODE*)malloc(sizeof(NODE))) == NULL) 
		error("no sppace");
	node->key = Pre[p1];
	if (p1 == p2)
		node->left = node->right = NULL;
	else	
	{
		r = rootInSym(s1, s2, node->key);
		node->left  = MakeTree(p1+1, r-s2+p2, s1, r-1);	/* �ݹ�����������	*/
		node->right = MakeTree(r-s2+p2+1, p2, r+1, s2);	/* �ݹ�����������	*/
	}
	return(node);
}
struct queue
{
	NODE *node;
	struct queue *next;
};

struct queue *First = NULL;
struct queue *Tail = NULL;
void enqueue(NODE *node){
	if (First == NULL)
	{
		struct queue *queuenode = (struct queue*)malloc(sizeof(struct queue));
		queuenode->node = node;
		queuenode->next = NULL;
		First = queuenode;
		Tail = queuenode;
	}
	else
	{
		struct queue *queuenode = (struct queue*)malloc(sizeof(struct queue));
		queuenode->node = node;
		queuenode->next = NULL;
		Tail->next = queuenode;
		Tail = queuenode;
	}
}
NODE *dequeue(){
	if (First == NULL)
	{
		error("");
	}
	else
	{
		NODE *node = (NODE *)malloc(sizeof(NODE));
		node = First->node;
		First = First->next;
		return(node);
	}
}
void leverOrder(NODE *Root){
	if(!Root){
		error("");
	}
	else
	{
		enqueue(Root);
		NODE *node = (NODE *)malloc(sizeof(NODE));
		while (node = dequeue())
		{
			printf("%c ",node->key);
			if(node->left) enqueue(node->left);
			if(node->right) enqueue(node->right);
		}	
	}
}
void main()
{
	/* 1. �����ַ��� */
	printf("������ǰ�����: "); 
	scanf("%s", Pre); 
	printf("�������������: "); 
	scanf("%s", Sym); 
	/* 2. ������ */
	Root = MakeTree(0, strlen(Pre)-1, 0, strlen(Sym)-1);
	/* 3. ���ı��� */
	printf("ǰ�����: "); 
	preOrder(Root);
	printf("\n");
	printf("�������: "); 
	symOrder(Root);
	printf("\n");
	printf("�������: "); 
	postOrder(Root);
	printf("\n");
	printf("��α���: "); 
	leverOrder(Root);
	printf("\n");
	system("pause");
}
/*
����ʾ��
ABDCFEGH
DBFCAGHE
������ǰ�����: DFCBHGEA
�������������: DBFCAGHE
ǰ�����: A B D C F E G H
�������: D B F C A G H E
�������: D F C B H G E A

ABCDEFGH
BDCAGFHE
������ǰ�����: DCBGHFEA
�������������: BDCAGFHE
ǰ�����: A B C D E F G H
�������: B D C A G F H E
�������: D C B G H F E A

CEFLMGDHJK
ELMFGCHKJD
������ǰ�����: CEFLMGDHJK
�������������: ELMFGCHKJD
ǰ�����: C E F L M G D H J K
�������: E L M F G C H K J D
�������: M L G F E K J H D C

MLGFEKJHDC
ELMFGCHKJD
������ǰ�����: MLGFEKJHDC
�������������: ELMFGCHKJD
no root in Sym
*/
