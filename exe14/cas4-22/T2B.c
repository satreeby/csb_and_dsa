/* File: T2B.c
	[例4-22] 三次树转换为二叉树	*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define BINODE struct binode
#define TRINODE struct trinode
#define S struct stack
BINODE
{
	char key;
	BINODE *left, *right;
};
TRINODE
{
	char key;
	int level;
	TRINODE *sub1, *sub2, *sub3;
};
S			/* 链接栈定义	*/
{
	TRINODE *node;
	S *next;
};
BINODE	*RootB;			/* 二叉树的根结点指针		*/
TRINODE	*RootT;			/* 三次树的根结点指针		*/
S *Top=NULL;
void error(char *string) 				/* 出错处理函数			*/
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
/* 递归方法前序遍历三次树		*/
void preOrderT(TRINODE *node)
{
	if(!node)
		return;
	printf("%c ", node->key); 
	preOrderT(node->sub1);
	preOrderT(node->sub2);
	preOrderT(node->sub3);
}
/* 递归方法后序遍历三次树		*/
void postOrderT(TRINODE *node)
{
	if(!node)
		return;
	postOrderT(node->sub1);
	postOrderT(node->sub2);
	postOrderT(node->sub3);
	printf("%c ", node->key); 
}
/* 递归方法前序遍历二叉树		*/
void preOrderB(BINODE *node)
{
	if(!node)
		return;
	printf("%c ", node->key); 
	preOrderB(node->left);
	preOrderB(node->right);
}
/* 递归方法中序遍历二叉树		*/
void symOrder(BINODE *node)
{
	if(!node)
		return;
	symOrder(node->left);
	printf("%c ", node->key); 
	symOrder(node->right);
}
/* 递归方法后序遍历二叉树		*/
void postOrderB(BINODE *node)
{
	if(!node)
		return;
	postOrderB(node->left);
	postOrderB(node->right);
	printf("%c ", node->key); 
}
void push(TRINODE *node)
{
	S *stack_node;
	stack_node = (S *)malloc(sizeof(S));
	if(stack_node == NULL)
		error("overflow!");
	stack_node->node = node;
	stack_node->next = Top;
	Top = stack_node;
}
TRINODE *pop()
{
	TRINODE *node;
	S *stack_node;
	if(Top == NULL)
		error("underflow!");
	node = Top->node;
	stack_node = Top;
	Top = Top->next;
	free(stack_node);
	return(node);
}
TRINODE *mekeNode(int level, char *key)
{
	TRINODE *node;
	node = (TRINODE *)malloc(sizeof(TRINODE));
	if(node == NULL)
		error("no space!");
	node->level = level;
	node->key = key[0];
	node->sub1 = node->sub2 = node->sub3 = NULL;
	return(node);
}
TRINODE *makeTree(void)		/* 输入树的括号表示	*/
{
	int level;
	char key[30];
	TRINODE *node, *child;
	scanf("%d%s", &level, key);
	node = mekeNode(level, key);
	push(node);
	while( scanf("%d%s", &level, key) == 2)
	{
		node = mekeNode(level, key);
		while(Top != NULL &&
			Top->node->level == node->level + 1)
		{
			child = pop();
			if(node->sub3 == NULL)
				node->sub3 = child;
			else if(node->sub2 == NULL)
				node->sub2 = child;
			else
				node->sub1 = child;
		}
		if(node->level != 1)
			push(node);
		else
			return(node);
	}
	if(Top != NULL)
		error("stack error!");
}
void *reOrder(TRINODE *node)		/* 输入树的括号表示	*/
{
	if(node == NULL)
		return(0);
	if( node->sub1 == NULL &&
		node->sub2 == NULL &&
		node->sub3 == NULL)
		return(0);
	if(node->sub1 == NULL)
	{
		if(node->sub2 == NULL)
		{
			node->sub1 = node->sub3;
			node->sub3 = NULL;
		}
		else
		{
			node->sub1 = node->sub2;
			node->sub2 = node->sub3;
			node->sub3 = NULL;
		}
	}
	reOrder(node->sub1);
	reOrder(node->sub2);
	reOrder(node->sub3);
	return 0;
}
BINODE *T2B(TRINODE *tri_node)
{
	BINODE *bi_node;
	if(tri_node == NULL)
		return(NULL);
	bi_node = (BINODE *)malloc(sizeof(BINODE));
	if(bi_node == NULL)
		error("no space");
	bi_node->key = tri_node->key;
	bi_node->left = bi_node->right = NULL;
	if(tri_node->sub1)
	{
		bi_node->left = T2B(tri_node->sub1);
		if(tri_node->sub2)
		{
			bi_node->left->right = T2B(tri_node->sub2);
			if(tri_node->sub3)
				bi_node->left->right->right = T2B(tri_node->sub3);
		}
	}
	return(bi_node);
}
void postOrderT2B(BINODE *RootB){
	if (RootB==NULL)
	{
		return;
	}
	if (RootB->left)
	{
		postOrderT2B(RootB->left);
	}
	printf("%c ",RootB->key);
	if (RootB->right)
	{
		postOrderT2B(RootB->right);
	}
	return; 
}
void main()
{
	/* 1. 输入三次树 */
	printf("请输入: "); 
	RootT = makeTree();
	reOrder(RootT);
	/* 2. 三次树的遍历	 */
	printf("前序遍历三次树: "); 
	preOrderT(RootT);
	printf("\n");
	printf("后序遍历三次树: "); 
	postOrderT(RootT);
	printf("\n");
	/* 3. T2B		*/
	RootB = T2B(RootT);
	printf("前序遍历二叉树: "); 
	preOrderB(RootB);
	printf("\n");
	printf("中序遍历二叉树: "); 
	symOrder(RootB);
	printf("\n");
	printf("后序遍历二叉树: "); 
	postOrderB(RootB);
	printf("\n");
	printf("后序遍历三次树：");
	postOrderT2B(RootB);
	printf("\n");
	system("pause");
}
/*
输入数据
2 F 3 D 3 G 2 B 2 C 1 A
前序遍历三次树: A F B D G C
后序遍历三次树: F D G B C A
前序遍历二叉树: A F B D G C
中序遍历二叉树: F D G B C A
后序遍历二叉树: G D C B F A

输入数据
2 E 3 G 3 J 2 H 3 C 3 F 3 D 2 B 1 A
前序遍历三次树: A E H G J B C F D
后序遍历三次树: E G J H C F D B A
前序遍历二叉树: A E H G J B C F D
中序遍历二叉树: E G J H C F D B A
后序遍历二叉树: J G D F C B H E A

输入数据
4 O 4 N 4 M 3 G 3 J 2 H 2 E 4 L 4 K 3 C 3 F 3 D 2 B 1 A
前序遍历三次树: A H G O N M J E B C L K F D
后序遍历三次树: O N M G J H E L K C F D B A
前序遍历二叉树: A H G O N M J E B C L K F D
中序遍历二叉树: O N M G J H E L K C F D B A
后序遍历二叉树: M N O J G K L D F C B E H A
*/
