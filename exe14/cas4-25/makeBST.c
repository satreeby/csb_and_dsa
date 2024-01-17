/* File: makeBST.c
	[��4-25] �������������ɳ���	*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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
FILE *initBST()
{
	FILE *fp;
	char filename[60];
	printf("BST����ļ�: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		exit(0);
	return(fp);
}
void insertNode(BST *root, BST *node) 		/* ����BST��㺯��	*/
{
	if(node->key == root->key)
		return;
	else if(root->left != NULL && node->key < root->key)
		insertNode(root->left, node);		/* ����Ҳ���	*/
	else if(root->right != NULL && node->key > root->key)
		insertNode(root->right, node); 		/* �Ҳ��Ҳ���	*/
	else if(root->left == NULL && node->key < root->key)
		root->left = node; 					/* ��������	*/
	else if(root->right == NULL && node->key > root->key)
		root->right = node; 				/* �Ҳ������	*/
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
void main()
{
	FILE *fp;
	fp = initBST();
	makeBST(fp);
	printf("symOrder: ");
	symOrder(Root);
	printf("\n");
	printf("preOrder: ");
	preOrder(Root);
	printf("\n");
	system("pause");
}
/*
BST����ļ�: BSTdata1.txt
symOrder:  5 19 20 35 50 52 53 55 88 92 98
preOrder: 50 19  5 35 20 55 52 53 98 88 92

BST����ļ�: BSTdata2.txt
symOrder: 11 12 15 17 18 19 21 24 26 28 32 35 39
preOrder: 24 11 12 18 15 17 21 19 28 26 32 35 39

BST����ļ�: BSTdata3.txt
symOrder: 11 12 15 17 18 19 21 24 26 28 32 35 39
preOrder: 24 17 12 11 15 19 18 21 32 26 28 39 35

BST����ļ�: BSTdata4.txt
symOrder: 13 15 17 21 23 25 27 35 36 38 40 44 46 49 53 55 58 67 73 77 81 83 87
preOrder: 40 35 21 15 13 17 23 27 25 38 36 81 44 53 49 46 67 55 58 73 77 87 83
*/
