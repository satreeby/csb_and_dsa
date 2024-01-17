/*	File: ThreadTree.c
	【例4-23】顺序存储穿线树
	结点值：数字和字符串	*/

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
int n=0;		/* 结点数n<=M		*/

int getPre(TREE *th, int i)		/* 获取中序前件地址	*/
{
	if(i<1 || i>n) 				/* 非法地址 */
		exit(0);
	if(th[i].left == 0)		 	/* 无左子 */
		return(0);
	if((i = th[i].left) > 0) 	/* 有左子 */
		while(th[i].right > 0) 	/* 有右子 */
			i = th[i].right;
	return(ABS(i));
}
int getSuc(TREE *th, int i)		/* 获取中序后件地址	*/
{ 
	if(i<1 || i>n) 				/* 非法地址	*/
		exit(0);
	if(th[i].right == 0)		 /* 无右子 */
		return(0);
	if ((i=th[i].right)>0)		/* 有右子	*/
		while(th[i].left>0) 	/* 有左子	*/
			i = th[i].left;
	return(ABS(i));
}
int getFirst(TREE *th, int root)/* 获取中序首结点	*/
{
	int i=root;
	if(i<1 || i>n) 				/* 非法地址	*/
		return(0);
	while(th[i].left > 0 )		/* 有左子	*/
		i = th[i].left;
	return(i);
}
void  symOrderT(TREE *th, int root)	/* 穿线中序遍历	*/
{
	int i=root;
	if((i = getFirst(th, i)) == 0)	/* 求中序始结点	*/
		exit(0);
	do
		printf("%s ", th[i].key);	/* 求中序后件	*/
	while(i = getSuc(th, i));
	printf("\n");
}
void preOrder(TREE *tree, int root)	/* 前序遍历函数	*/
{
	if(root <= 0)
		return;
	printf("%s ", tree[root].key);
	preOrder(tree, tree[root].left);
	preOrder(tree, tree[root].right);
}
void symOrder(TREE *tree, int root)	/* 中序遍历函数	*/
{
	if(root <= 0)
		return;
	symOrder(tree, tree[root].left);
	printf("%s ", tree[root].key);
	symOrder(tree, tree[root].right);
}
void postOrder(TREE *tree, int root) /* 后序遍历函数 */
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
	printf("输入哪个文件: ");
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
	printf("前序遍历:\t");
	preOrder(Tree, 1);
	printf("\n");
	printf("后序遍历:\t");
	postOrder(Tree, 1);
	printf("\n");
	printf("中序遍历:\t");
	symOrder(Tree, 1);
	printf("\n");
	printf("穿线中序遍历:\t");
	symOrderT(Tree, 1);
	printf("寻找哪个结点的中序前件？输入结点地址：");
	scanf("%d", &i);
	k = getPre(Tree, i);
	if(k == 0)
		printf("结点%s没有中序前件\n", Tree[i].key);
	else
		printf("结点%s的中序前件 = %s\n",
				Tree[i].key, Tree[k].key);
	printf("寻找哪个结点的中序后件？输入结点地址：");
	scanf("%d", &i);
	k = getSuc(Tree, i);
	if(k == 0)
		printf("结点%s没有中序后件\n", Tree[i].key);
	else
		printf("结点%s的中序后件 = %s\n",
				Tree[i].key, Tree[k].key);
	system("pause");
}
/*
输入哪个文件: ThTree0.txt
前序遍历:       A F G D H E C B
后序遍历:       D H G F B C E A
中序遍历:       F D G H A C B E
穿线中序遍历:   F D G H A C B E

输入哪个文件: ThTree1.txt
前序遍历:       10 20 90 60 30 80 50 40 70
后序遍历:       90 30 80 60 20 70 40 50 10
中序遍历:       90 20 30 60 80 10 70 40 50
穿线中序遍历:   90 20 30 60 80 10 70 40 50

输入哪个文件: ThTree2.txt
前序遍历:       50 19 15 35 20 55 52 53 98 88
后序遍历:       15 20 35 19 53 52 88 98 55 50
中序遍历:       15 19 20 35 50 52 53 55 88 98
穿线中序遍历:   15 19 20 35 50 52 53 55 88 98

输入哪个文件: ThTree3.txt

*/
