/* File: B2T.c
	[ϰ��4-38] ������ת��Ϊ������	*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define BINODE struct binode
#define TRINODE struct trinode
#define M 	80
BINODE
{
	char key;
	BINODE *left, *right;
};
TRINODE
{
	char key;
	TRINODE *sub1, *sub2, *sub3;
};
	
BINODE	*RootB=NULL;	/* �������ĸ����ָ��		*/
TRINODE	*RootT=NULL;	/* �������ĸ����ָ��		*/
char String[M];	/* �����ַ���	*/
int  Ptr=0;		/* �ַ�����ָ�� */
void error(char *string)
{
	printf("%s\n", string);
	exit(0);
	system("pause");
}
/* �ݹ鷽��ǰ�����������		*/
void preOrderT(TRINODE *node)
{
	if(!node)
		return;
	printf("%c ", node->key); 
	preOrderT(node->sub1);
	preOrderT(node->sub2);
	preOrderT(node->sub3);
}
/* �ݹ鷽���������������		*/
void postOrderT(TRINODE *node)
{
	if(!node)
		return;
	postOrderT(node->sub1);
	postOrderT(node->sub2);
	postOrderT(node->sub3);
	printf("%c ", node->key); 
}
void preOrder(BINODE *node)
{
	if(!node)
		return;
	printf("%c ", node->key); 
	preOrder(node->left);
	preOrder(node->right);
}
void symOrder(BINODE *node)
{
	if(!node)
		return;
	symOrder(node->left);
	printf("%c ", node->key); 
	symOrder(node->right);
}
void postOrder(BINODE *node)
{
	if(!node)
		return;
	postOrder(node->left);
	postOrder(node->right);
	printf("%c ", node->key); 
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
/*	printf("����Ķ��������ű�ʾ: \n%s\n", String); 
*/
}
int GetKey(char *key)			/* ��ȡ���ֵ�ĺ���	*/
{
	int i = 0;
	if(!isalnum(String[Ptr]))
		return(0);					/* ȡֵʧ��		*/
	while(isalnum(String[Ptr]))		/* ��ȡ����		*/
		*key = String[Ptr++];
	return(1); 						/* ȡֵ�ɹ�		*/
}
int GetSymbol(char symbol) 	/* ��ȡָ�����ŵĺ���	*/
{
	if(String[Ptr] != symbol)
		return(0);					/* ȡ����ʧ��	*/
	Ptr++;
	return(1);					 	/* ȡ���ųɹ�	*/
}
BINODE *newNode(char key) 	/* ���ɽ��ռ�ĺ���	*/
{
	BINODE *node;
	node = (BINODE *)(malloc(sizeof(BINODE)));
	if(node == NULL)
		error("no space!"); 
	node->left = node->right = NULL; /* �����ӳ�ʼ����	*/
	node->key = key;				 /* ��㸳ֵ		*/
	return(node);
}
void MakeNode(BINODE *root) 	/* ���������ĺ���		*/
{
	char key;
	if(!GetSymbol('('))					/* 1. ��ȡ������'('	*/
		return;
	if(GetKey(&key))					/* 2. ��ȡ��������	*/
	{  
		root->left = newNode(key); 		/* �������ӿռ�		*/
		MakeNode(root->left);			/* �ݹ�����������	*/
	}
	if(!GetSymbol(','))					/* 3. ��ȡ����','	*/
		error("missing , !"); 
	if(GetKey(&key))					/* 4. ��ȡ��������	*/
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
	char key;
	if(GetKey(&key))					/* ��ȡ���������	*/
	{	
		RootB = newNode(key); 			/* ���ɸ����		*/
		MakeNode(RootB); 				/* ����������������	*/
	}
	else
		error("Empty tree!"); 
}
void B2T(BINODE * bi_node, TRINODE *tri_node)
{
	if(tri_node == NULL || bi_node == NULL)
		error ("empty tree");
	tri_node->key = bi_node->key;
	/* complete the following code			*/
	tri_node->sub1 = tri_node->sub2 = tri_node->sub3 = NULL;
	if(bi_node->left)
	{
		tri_node->sub1 = (TRINODE *)malloc(sizeof(TRINODE));
		if(tri_node->sub1 == NULL)
			error("no space");
		B2T(bi_node->left, tri_node->sub1);	
		if(bi_node->left->right)
		{
			tri_node->sub2 = (TRINODE *)malloc(sizeof(TRINODE));
			if(tri_node->sub2 == NULL)
				error("no space");
			B2T(bi_node->left->right, tri_node->sub2);
			if(bi_node->left->right->right)
			{
				tri_node->sub3 = (TRINODE *)malloc(sizeof(TRINODE));
				if(tri_node->sub3 == NULL)
					error("no space");
				B2T(bi_node->left->right->right, tri_node->sub3);
			}
		}
	}
}
void main()
{
	input();
	MakeBitree();
	printf("ǰ�������������");
	preOrder(RootB);
	printf("\n");
	printf("���������������");
	symOrder(RootB);
	printf("\n");
	printf("���������������");
	postOrder(RootB);
	printf("\n");

	RootT = (TRINODE *)malloc(sizeof(TRINODE));
	if(RootT == NULL)
		error("no space");
	B2T(RootB, RootT);
	printf("ǰ�����������: "); 
	preOrderT(RootT);
	printf("\n");
	printf("�������������: "); 
	postOrderT(RootT);
	printf("\n");
	system("pause");
}

/*
���������ű�ʾ�Ķ�����(�Կ��Ʒ�^Z+���з�Ϊ����):
A(E
   (,6(8
        (,3(,G)),2(4,))),)
^Z
ǰ�������������A E 6 8 3 G 2 4
���������������E 8 3 G 6 4 2 A
���������������G 3 8 4 2 6 E A
ǰ�����������: A E 6 8 3 G 2 4
�������������: E 8 3 G 6 4 2 A

���������ű�ʾ�Ķ�����(�Կ��Ʒ�^Z+���з�Ϊ����):
A(B( ,C(E( ,F(H( ,J(,K)), )),D(G, ))),)
^Z
ǰ�������������A B C E F H J K D G
���������������B E H J K F C G D A
���������������K J H F E G D C B A
ǰ�����������: A B C E F H J K D G
�������������: B E H J K F C G D A
*/
