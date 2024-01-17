/*	File: brack2tree.c
	[��4-18,4-19] ǰ��������ű�ʾ(bracket)���ɶ�����
	���ֵ�����ֺ��ַ���	*/

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
char String[M];	/* �����ַ���	*/
int  Ptr=0;		/* �ַ�����ָ�� */
void error(char *string)
{
	printf("%s\n", string);
	exit(0);
}
void input(void)				/* �����������ű�ʾ	*/
{
	int i=0, c;  
	printf("���������ű�ʾ�Ķ�����"); 
	printf("(�Կ��Ʒ�^Z+���з�Ϊ����):\n"); 
	while( (c=getchar()) != EOF )
		if(!isspace(c))			/* ɾ�����ַ�		*/
			String[i++] = c;
	String[i] = '\0';
	printf("����Ķ��������ű�ʾ: \n%s\n", String); 
}
int GetKey(char *key)			/* ��ȡ���ֵ�ĺ���	*/
{
	int i = 0;
	if(!isalnum(String[Ptr]))
		return(0);					/* ȡֵʧ��		*/
	while(isalnum(String[Ptr]))		/* ��ȡ����		*/
		key[i++] = String[Ptr++];
	key[i] = '\0'; 
	return(1); 						/* ȡֵ�ɹ�		*/
}
int GetSymbol(char symbol) 	/* ��ȡָ�����ŵĺ���	*/
{
	if(String[Ptr] != symbol)
		return(0);					/* ȡ����ʧ��	*/
	Ptr++;
	return(1);					 	/* ȡ���ųɹ�	*/
}
NODE *newNode(char *key) 	/* ���ɽ��ռ�ĺ���	*/
{
	NODE *node;
	node = (NODE *)(malloc(sizeof(NODE)));
	if(node == NULL)
		error("no space!"); 
	node->left = node->right = NULL; /* �����ӳ�ʼ����	*/
	strcpy(node->key, key);			 /* ��㸳ֵ		*/
	return(node);
}
void MakeNode(NODE *root) 	/* ���������ĺ���		*/
{
	char key[10];
	if(!GetSymbol('('))					/* 1. ��ȡ������'('	*/
		return;
	if(GetKey(key))						/* 2. ��ȡ��������	*/
	{  
		root->left = newNode(key); 		/* �������ӿռ�		*/
		MakeNode(root->left);			/* �ݹ�����������	*/
	}
	if(!GetSymbol(','))					/* 3. ��ȡ����','	*/
		error("missing , !"); 
	if(GetKey(key))						/* 4. ��ȡ��������	*/
	{  
		root->right = newNode(key); 	/* �������ӿռ�		*/
		MakeNode(root->right); 			/* �ݹ�����������	*/
	}
	if(!GetSymbol(')'))					/* 5. ��ȡ������')'	*/
		error("missing ) !"); 
	if(root->right == NULL && root->left == NULL)
		error("no node !"); 			/* �������ӣ�����	*/ 
}
void MakeBitree()						/* ���ɶ������ĺ���	*/
{
	char key[10];
	if(GetKey(key))						/* ��ȡ���������	*/
	{	
		Root = newNode(key); 			/* ���ɸ����		*/
		MakeNode(Root); 				/* ����������������	*/
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
	printf("ǰ�������");
	preOrder(Root);
	printf("\n");
	printf("���������");
	symOrder(Root);
	printf("\n");
	printf("���������");
	postOrder(Root);
	printf("\n");
	system("pause");
}

/*
���������ű�ʾ�Ķ�����(�Կ��Ʒ�^Z+���з�Ϊ����):
E(A( ,3(2, 4)), 8(6(, G), ))
^Z
����Ķ��������ű�ʾ:
E(A(,3(2,4)),8(6(,G),))
ǰ�������E A 3 2 4 8 6 G
���������A 2 3 4 E 6 G 8
���������2 4 3 A G 6 8 E

���������ű�ʾ�Ķ�����(�Կ��Ʒ�^Z+���з�Ϊ����):
  5(v2(,
72(a6,   7)  ),
12(  4,v8  ( 3,)  )  )
^Z
����Ķ��������ű�ʾ:
5(v2(,72(a6,7)),12(4,v8(3,)))
ǰ�������5 v2 72 a6 7 12 4 v8 3
���������v2 a6 72 7 5 4 12 3 v8
���������a6 7 72 v2 4 3 v8 12 5

���������ű�ʾ�Ķ�����(�Կ��Ʒ�^Z+���з�Ϊ����):
A(B(, D(G, H)), C(E(, F), ))
^Z
����Ķ��������ű�ʾ:
A(B(,D(G,H)),C(E(,F),))
ǰ�������A B D G H C E F
���������B G D H A E F C
���������G H D B F E C A

���������ű�ʾ�Ķ�����(�Կ��Ʒ�^Z+���з�Ϊ����):
  5(32(,
	72(40,   7)  ),
12(4,8  ( 3,)  )  )
^Z
����Ķ��������ű�ʾ:
5(32(,72(40,7)),12(4,8(3,)))
ǰ�������5 32 72 40 7 12 4 8 3
���������32 40 72 7 5 4 12 3 8
���������40 7 72 32 4 3 8 12 5
*/