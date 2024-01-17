/*	File: order2tree.c
	[例4-20] 根据前序和中序遍历生成二叉树	*/

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
/* 递归方法的前序遍历函数		*/
void preOrder(NODE *node)
{
	if(!node)
		return;
	printf("%c ", node->key); 
	preOrder(node->left);
	preOrder(node->right);
}
/* 递归方法的中序遍历函数		*/
void symOrder(NODE *node)
{
	if(!node)
		return;
	symOrder(node->left);
	printf("%c ", node->key); 
	symOrder(node->right);
}
/* 递归方法的后序遍历函数		*/
void postOrder(NODE *node)
{
	if(!node)
		return;
	postOrder(node->left);
	postOrder(node->right);
	printf("%c ", node->key); 
}
int rootInSym(int s1, int s2, char key)
{	/* 在中序字符串中找寻子树的根（key）	*/
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
		node->left  = MakeTree(p1+1, r-s2+p2, s1, r-1);	/* 递归生成左子树	*/
		node->right = MakeTree(r-s2+p2+1, p2, r+1, s2);	/* 递归生成右子树	*/
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
	/* 1. 输入字符串 */
	printf("请输入前序遍历: "); 
	scanf("%s", Pre); 
	printf("请输入中序遍历: "); 
	scanf("%s", Sym); 
	/* 2. 生成树 */
	Root = MakeTree(0, strlen(Pre)-1, 0, strlen(Sym)-1);
	/* 3. 树的遍历 */
	printf("前序遍历: "); 
	preOrder(Root);
	printf("\n");
	printf("中序遍历: "); 
	symOrder(Root);
	printf("\n");
	printf("后序遍历: "); 
	postOrder(Root);
	printf("\n");
	printf("层次遍历: "); 
	leverOrder(Root);
	printf("\n");
	system("pause");
}
/*
运行示例
ABDCFEGH
DBFCAGHE
请输入前序遍历: DFCBHGEA
请输入中序遍历: DBFCAGHE
前序遍历: A B D C F E G H
中序遍历: D B F C A G H E
后序遍历: D F C B H G E A

ABCDEFGH
BDCAGFHE
请输入前序遍历: DCBGHFEA
请输入中序遍历: BDCAGFHE
前序遍历: A B C D E F G H
中序遍历: B D C A G F H E
后序遍历: D C B G H F E A

CEFLMGDHJK
ELMFGCHKJD
请输入前序遍历: CEFLMGDHJK
请输入中序遍历: ELMFGCHKJD
前序遍历: C E F L M G D H J K
中序遍历: E L M F G C H K J D
后序遍历: M L G F E K J H D C

MLGFEKJHDC
ELMFGCHKJD
请输入前序遍历: MLGFEKJHDC
请输入中序遍历: ELMFGCHKJD
no root in Sym
*/
