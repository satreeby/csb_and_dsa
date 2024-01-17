/*	File: brack2tree.c
	[例4-18,4-19] 前序遍历括号表示(bracket)生成二叉树
	结点值：数字和字符串	*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define NODE struct node
#define M 	80
NODE
{
	char key[10];
	NODE *left, *right;
};
	
NODE *Root=NULL;
char String[M];	/* 输入字符串	*/
int  Ptr=0;		/* 字符数组指针 */
void error(char *string)
{
	printf("%s\n", string);
	exit(0);
}
void input(void)				/* 输入树的括号表示	*/
{
	int i=0, c;  
	printf("请输入括号表示的二叉树"); 
	printf("(以控制符^Z+换行符为结束):\n"); 
	while( (c=getchar()) != EOF )
		if(!isspace(c))			/* 删除空字符		*/
			String[i++] = c;
	String[i] = '\0';
	printf("输入的二叉树括号表示: \n%s\n", String); 
}
int GetKey(char *key)			/* 获取结点值的函数	*/
{
	int i = 0;
	if(!isalnum(String[Ptr]))
		return(0);					/* 取值失败		*/
	while(isalnum(String[Ptr]))		/* 获取数据		*/
		key[i++] = String[Ptr++];
	key[i] = '\0'; 
	return(1); 						/* 取值成功		*/
}
int GetSymbol(char symbol) 	/* 获取指定符号的函数	*/
{
	if(String[Ptr] != symbol)
		return(0);					/* 取符号失败	*/
	Ptr++;
	return(1);					 	/* 取符号成功	*/
}
NODE *newNode(char *key) 	/* 生成结点空间的函数	*/
{
	NODE *node;
	node = (NODE *)(malloc(sizeof(NODE)));
	if(node == NULL)
		error("no space!"); 
	node->left = node->right = NULL; /* 左右子初始赋空	*/
	strcpy(node->key, key);			 /* 结点赋值		*/
	return(node);
}
void MakeNode(NODE *root) 	/* 生成子树的函数		*/
{
	char key[10];
	if(!GetSymbol('('))					/* 1. 获取左括号'('	*/
		return;
	if(GetKey(key))						/* 2. 获取左子数据	*/
	{  
		root->left = newNode(key); 		/* 生成左子空间		*/
		MakeNode(root->left);			/* 递归生成左子树	*/
	}
	if(!GetSymbol(','))					/* 3. 获取逗号','	*/
		error("missing , !"); 
	if(GetKey(key))						/* 4. 获取右子数据	*/
	{  
		root->right = newNode(key); 	/* 生成右子空间		*/
		MakeNode(root->right); 			/* 递归生成右子树	*/
	}
	if(!GetSymbol(')'))					/* 5. 获取又括号')'	*/
		error("missing ) !"); 
	if(root->right == NULL && root->left == NULL)
		error("no node !"); 			/* 无左右子，出错	*/ 
}
void MakeBitree()						/* 生成二叉树的函数	*/
{
	char key[10];
	if(GetKey(key))						/* 获取根结点数据	*/
	{	
		Root = newNode(key); 			/* 生成根结点		*/
		MakeNode(Root); 				/* 调用生成子树函数	*/
	}
	else
		error("Empty tree!"); 
}
void preOrder(NODE *node)
{
	if(!node)
		return;
	printf("%s ", node->key); 
	preOrder(node->left);
	preOrder(node->right);
}
void symOrder(NODE *node)
{
	if(!node)
		return;
	symOrder(node->left);
	printf("%s ", node->key); 
	symOrder(node->right);
}
void postOrder(NODE *node)
{
	if(!node)
		return;
	postOrder(node->left);
	postOrder(node->right);
	printf("%s ", node->key); 
}
void main()
{
	input();
	MakeBitree();
	printf("前序遍历：");
	preOrder(Root);
	printf("\n");
	printf("中序遍历：");
	symOrder(Root);
	printf("\n");
	printf("后序遍历：");
	postOrder(Root);
	printf("\n");
	system("pause");
}

/*
请输入括号表示的二叉树(以控制符^Z+换行符为结束):
E(A( ,3(2, 4)), 8(6(, G), ))
^Z
输入的二叉树括号表示:
E(A(,3(2,4)),8(6(,G),))
前序遍历：E A 3 2 4 8 6 G
中序遍历：A 2 3 4 E 6 G 8
后序遍历：2 4 3 A G 6 8 E

请输入括号表示的二叉树(以控制符^Z+换行符为结束):
  5(v2(,
72(a6,   7)  ),
12(  4,v8  ( 3,)  )  )
^Z
输入的二叉树括号表示:
5(v2(,72(a6,7)),12(4,v8(3,)))
前序遍历：5 v2 72 a6 7 12 4 v8 3
中序遍历：v2 a6 72 7 5 4 12 3 v8
后序遍历：a6 7 72 v2 4 3 v8 12 5

请输入括号表示的二叉树(以控制符^Z+换行符为结束):
A(B(, D(G, H)), C(E(, F), ))
^Z
输入的二叉树括号表示:
A(B(,D(G,H)),C(E(,F),))
前序遍历：A B D G H C E F
中序遍历：B G D H A E F C
后序遍历：G H D B F E C A

请输入括号表示的二叉树(以控制符^Z+换行符为结束):
  5(32(,
	72(40,   7)  ),
12(4,8  ( 3,)  )  )
^Z
输入的二叉树括号表示:
5(32(,72(40,7)),12(4,8(3,)))
前序遍历：5 32 72 40 7 12 4 8 3
中序遍历：32 40 72 7 5 4 12 3 8
后序遍历：40 7 72 32 4 3 8 12 5
*/