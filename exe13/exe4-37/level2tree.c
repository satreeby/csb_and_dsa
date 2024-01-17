/*	File: level2tree.c
	[��4-17,ϰ��4-37] ���������ű�ʾ(level)����������	*/

#include <stdio.h>
#include <stdlib.h>
#define TREE struct node
#define S struct stack
#define M 	100
TREE		/* ����㶨��	*/
{
	char key;
	int level;
	TREE *sub1, *sub2, *sub3;
};
S			/* ����ջ����	*/
{
	TREE *node;
	S *next;
};
TREE *Root=NULL;
S *Top=NULL;

void error(char *string)	/* ��������	*/
{
	printf("%s\n", string);
	exit(0);
	system("pause");
}

void push(TREE *node)
{
	S *stack_node;
	stack_node = (S *)malloc(sizeof(S));
	if(stack_node == NULL)
		error("overflow!");
	stack_node->node = node;
	stack_node->next = Top;
	Top = stack_node;
}
TREE *pop()
{
	TREE *node;
	S *stack_node;
	if(Top == NULL)
		error("underflow!");
	node = Top->node;
	stack_node = Top;
	Top = Top->next;
	free(stack_node);
	return(node);
}
void preOrder(TREE *node)
{
	if(!node)
		return;
	printf("%c ", node->key); 
	preOrder(node->sub1);
	preOrder(node->sub2);
	preOrder(node->sub3);
}
void postOrder(TREE *node)
{
	if(!node)
		return;
	postOrder(node->sub1);
	postOrder(node->sub2);
	postOrder(node->sub3);
	printf("%c ", node->key); 
}
TREE *mekeNode(int level, char *key)
{
	TREE *node;
	node = (TREE *)malloc(sizeof(TREE));
	if(node == NULL)
		error("no space!");
	node->level = level;
	node->key = key[0];
	node->sub1 = node->sub2 = node->sub3 = NULL;
	return(node);
}
TREE *makeTree(void)		/* �����������ű�ʾ	*/
{
	int level;
	char key[30];
	TREE *node, *child;
	scanf("%d%s", &level, key);
	node = mekeNode(level, key);
	push(node);
	while( scanf("%d%s", &level, key) == 2)
	{
		/* complete the following code	*/
		node = mekeNode(level, key); 
		while (Top != NULL && node->level == Top->node->level - 1)
		{
			child = pop();
			if(node->sub3 == NULL)
			node->sub3 = child;
			else if(node->sub2 == NULL)
			node->sub2 = child;
			else
			node->sub1 = child;
		}
		if (node->level != 1)
		{
			push(node);
		}
		else
			return(node); 
	}
	if(Top != NULL)
		error("stack error!");	
}
void main()
{
	printf("��������\n");
	Root = makeTree();
	printf("ǰ�������");
	preOrder(Root);
	printf("\n");
	printf("���������");
	postOrder(Root);
	printf("\n");
	system("pause");
}
/*
��������
2 F 3 D 3 G 2 B 2 C 1 A
ǰ�������A F B D G C
���������F D G B C A

��������
2 E 3 H 3 C 3 G 2 F 3 D 2 B 1 A
ǰ�������A E F H C G B D
���������E H C G F D B A

��������
2 B 3 E 4 H 4 J 4 K 3 F 2 C 3 G 2 D 1 A
ǰ�������A B C E F H J K D G
���������B E H J K F C G D A
*/
