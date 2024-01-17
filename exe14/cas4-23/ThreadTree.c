/*	File: ThreadTree.c
	����4-23��˳��洢������
	���ֵ�����ֺ��ַ���	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  M  50
#define  ABS(X)	((X) > 0 ? (X) : (-X))
#define TREE struct tree
TREE
{
	char key[10];
	int left, right;
};
TREE  Tree[M];
int n=0;		/* �����n<=M		*/

int getPre(TREE *th, int i)		/* ��ȡ����ǰ����ַ	*/
{
	if(i<1 || i>n) 				/* �Ƿ���ַ */
		exit(0);
	if(th[i].left == 0)		 	/* ������ */
		return(0);
	if((i = th[i].left) > 0) 	/* ������ */
		while(th[i].right > 0) 	/* ������ */
			i = th[i].right;
	return(ABS(i));
}
int getSuc(TREE *th, int i)		/* ��ȡ��������ַ	*/
{ 
	if(i<1 || i>n) 				/* �Ƿ���ַ	*/
		exit(0);
	if(th[i].right == 0)		 /* ������ */
		return(0);
	if ((i=th[i].right)>0)		/* ������	*/
		while(th[i].left>0) 	/* ������	*/
			i = th[i].left;
	return(ABS(i));
}
int getFirst(TREE *th, int root)/* ��ȡ�����׽��	*/
{
	int i=root;
	if(i<1 || i>n) 				/* �Ƿ���ַ	*/
		return(0);
	while(th[i].left > 0 )		/* ������	*/
		i = th[i].left;
	return(i);
}
void  symOrderT(TREE *th, int root)	/* �����������	*/
{
	int i=root;
	if((i = getFirst(th, i)) == 0)	/* ������ʼ���	*/
		exit(0);
	do
		printf("%s ", th[i].key);	/* ��������	*/
	while(i = getSuc(th, i));
	printf("\n");
}
void preOrder(TREE *tree, int root)	/* ǰ���������	*/
{
	if(root <= 0)
		return;
	printf("%s ", tree[root].key);
	preOrder(tree, tree[root].left);
	preOrder(tree, tree[root].right);
}
void symOrder(TREE *tree, int root)	/* �����������	*/
{
	if(root <= 0)
		return;
	symOrder(tree, tree[root].left);
	printf("%s ", tree[root].key);
	symOrder(tree, tree[root].right);
}
void postOrder(TREE *tree, int root) /* ����������� */
{
	if(root <= 0)
		return;
	postOrder(tree, tree[root].left);
	postOrder(tree, tree[root].right);
	printf("%s ", tree[root].key);
}
main()
{
	int  left, right, i, k;
	FILE *fp;
	char key[10], filename[M];
	printf("�����ĸ��ļ�: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		exit(0);
	n++;
	while(fscanf(fp, "%s%d%d", key, &left, &right) == 3)
	{
		strcpy(Tree[n].key, key);
		Tree[n].left = left;
		Tree[n].right = right;
		n++;
	}
	printf("ǰ�����:\t");
	preOrder(Tree, 1);
	printf("\n");
	printf("�������:\t");
	postOrder(Tree, 1);
	printf("\n");
	printf("�������:\t");
	symOrder(Tree, 1);
	printf("\n");
	printf("�����������:\t");
	symOrderT(Tree, 1);
	printf("Ѱ���ĸ���������ǰ�����������ַ��");
	scanf("%d", &i);
	k = getPre(Tree, i);
	if(k == 0)
		printf("���%sû������ǰ��\n", Tree[i].key);
	else
		printf("���%s������ǰ�� = %s\n",
				Tree[i].key, Tree[k].key);
	printf("Ѱ���ĸ��������������������ַ��");
	scanf("%d", &i);
	k = getSuc(Tree, i);
	if(k == 0)
		printf("���%sû��������\n", Tree[i].key);
	else
		printf("���%s�������� = %s\n",
				Tree[i].key, Tree[k].key);
	system("pause");
}
/*
�����ĸ��ļ�: ThTree0.txt
ǰ�����:       A F G D H E C B
�������:       D H G F B C E A
�������:       F D G H A C B E
�����������:   F D G H A C B E

�����ĸ��ļ�: ThTree1.txt
ǰ�����:       10 20 90 60 30 80 50 40 70
�������:       90 30 80 60 20 70 40 50 10
�������:       90 20 30 60 80 10 70 40 50
�����������:   90 20 30 60 80 10 70 40 50

�����ĸ��ļ�: ThTree2.txt
ǰ�����:       50 19 15 35 20 55 52 53 98 88
�������:       15 20 35 19 53 52 88 98 55 50
�������:       15 19 20 35 50 52 53 55 88 98
�����������:   15 19 20 35 50 52 53 55 88 98

�����ĸ��ļ�: ThTree3.txt

*/
