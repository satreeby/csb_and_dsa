/* File: BSTdeleteTest.c
	[��4-26] �������������ɾ���Ĳ��Գ���	*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define BST struct bst
BST
{
	int key;
	BST *left, *right;
};
BST *Root=NULL;
void error(char *string)	/* ��������	*/
{
	printf("%s\n", string);
	exit(0);
	system("pause");
}
void symOrder(BST *node)
{
	if(node == NULL)
		return;
	symOrder(node->left);
	printf("%2d ", node->key);
	symOrder(node->right);
}
void preOrder(BST *node)
{
	if(node == NULL)
		return;
	printf("%2d ", node->key);
	preOrder(node->left);
	preOrder(node->right);
}
void prt(BST *Root)
{
	printf("symOrder: ");
	symOrder(Root);
	printf("\n");
	printf("preOrder: ");
	preOrder(Root);
	printf("\n");
}
FILE *initBST()
{
	FILE *fp;
	char filename[60];
	printf("BST����ļ�: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		error("cannot open the file!");
	return(fp);
}
void insertNode(BST *root, BST *node)
{
	if(node->key == root->key)
		return;
	else if(root->left != NULL && node->key < root->key)
		insertNode(root->left, node);
	else if(root->right != NULL && node->key > root->key)
		insertNode(root->right, node);
	else if(root->left == NULL && node->key < root->key)
	{
		node->left = root->left;
		root->left = node;
		return;
	}
	else if(root->right == NULL && node->key > root->key)
	{
		node->right = root->right;
		root->right = node;
		return;
	}
}
void makeBST(FILE *fp)				/* ����BST����		*/
{
	int key;
	BST *node;
	fscanf(fp, "%d", &key);
	if((Root = (BST *)malloc(sizeof(BST))) == NULL)
		error("no space!"); 		/* ����BST�����	*/
	Root->key = key;	
	Root->left = Root->right = NULL;
	while(fscanf(fp, "%d", &key) == 1)
	{
		if((node = (BST *)malloc(sizeof(BST))) == NULL)
			error("no space!");
		node->key = key;
		node->left = node->right = NULL;
		insertNode(Root, node);
	}
}
BST * deleteNode(BST *parent, BST *node)
{
	BST *prev, *tmp;
	/* case1��node�����ӣ���node���������node			*/
	if(node->left == NULL)	
	{
		if(node == parent->left)
			printf("1L\n"), parent->left = node->right;
		if(node == parent->right)
			printf("1R\n"),parent->right = node->right;
	}
	/* case2��node�����������ӣ���node���������node	*/
	else if(node->left->right == NULL)
	{ 
		node->left->right = node->right;
		if(node == parent->left)
			printf("2L\n"), parent->left = node->left;
		if(node == parent->right)
			printf("2R\n"), parent->right = node->left;
	}
	/* case3������node������ǰ��pSym����pSym���node	*/
	else if(node->left->right != NULL)
	{
		for(prev=node->left; prev->right->right; prev=prev->right)
			;								/* ����pSym						*/
		tmp = prev->right->left;			/* ��tmp����pSym������			*/
		prev->right->left = node->left;		/* ��pSym���nodeָ��node������	*/
		prev->right->right = node->right;	/* ��pSym���nodeָ��node������	*/
		if(node == parent->left)
			printf("3L\n"), parent->left = prev->right;	/* parent������ָ��pSym	*/
		if(node == parent->right)
			printf("3R\n"), parent->right = prev->right;/* parent������ָ��pSym	*/
		prev->right = tmp;					/* prev������ָ��tmp			*/
	}
	return(node);
}
BST * findNode(BST *parent, BST *node, int key)
{
	if(node == NULL)
		return(NULL);
	else if(key == node->key)
	{
		printf("d:parent=%d node=%d\n", parent->key, node->key);
		return( deleteNode(parent, node) );
	}
	else if(key < node->key)
	{
		printf("sL:key=%d node=%d\n", key, node->key);
		return( findNode(node, node->left, key) );
	}
	else if(key > node->key)
	{
		printf("sR:key=%d node=%d\n", key, node->key);
		return( findNode(node, node->right, key) );
	}
	return(NULL);
}
BST *virtualRoot(BST *Root, int mini)
{
	BST *node;
	if((node = (BST *)malloc(sizeof(BST))) == NULL)
		error("no space!");
	node->left = NULL;
	node->right = Root;
	node->key = mini;
	return(node);
}
void main()
{
	int key, mini=-1;
	BST *node;
	FILE *fp;
	fp = initBST();
	makeBST(fp);
	prt(Root);
	Root = virtualRoot(Root, mini);
	while(1)
	{
		printf("ɾ���ĸ����[0��ʾ����]: ");
		scanf("%d", &key);
		if(key == 0)
			break;
		if( node = findNode(Root, Root->right, key) )
		{
			free(node);
			prt(Root->right);
		}
		else
			printf("cannot found key: %d\n", key);
	}
	system("pause");
}
/*
BST����ļ�: BSTdata.txt
symOrder: 11 12 15 18 19 24 26 28 32
preOrder: 24 11 12 15 19 18 28 26 32
ɾ���ĸ����[0��ʾ����]: 24
d:parent=-1 node=24
3R
symOrder: 11 12 15 18 19 26 28 32
preOrder: 19 11 12 15 18 28 26 32

BST����ļ�: BSTdata4.txt
symOrder: 13 15 16 17 21 23 25 27 35 36 38 40 44 46 49 53 55 58 67 73 77 81 83 87
preOrder: 40 35 21 15 13 17 16 23 27 25 38 36 81 44 53 49 46 67 55 58 73 77 87 83

ɾ������
��1��ɾ����㣺25  58  73  21
��2��ɾ����㣺55  15  27  53
��3��ɾ����㣺49  35  67  81
��4��ɾ����㣺40
������ļ���
BSTout4-1.txt, BSTout4-2.txt, BSTout4-3.txt, BSTout4-4.txt
*/
