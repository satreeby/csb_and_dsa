/* File: Huffman.c
	[例4-24] 哈夫曼树生成和编码程序	*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NODE struct node
NODE
{
	char key;
	int weigh;
	char code[10];
	NODE *next;
	NODE *left, *right;
};
NODE *Head;
int lenCode=0;
void prt()
{
	NODE *node = Head->next;
	for(; node ; node = node->next)
		printf("%c %d ", node->key, node->weigh);
	printf("\n");
}
void prtCode(NODE *node) 		/* 打印Huffman编码函数	*/
{
	int lengh;
	if(node == NULL)
		return;
	if(node->key != '#')
	{
		lengh = strlen(node->code) * node->weigh;
		lenCode += lengh;
		printf("%c %d [%s] %d\n", node->key, node->weigh, node->code, lengh);
	}
	prtCode(node->left);
	prtCode(node->right);
	return;
}
void preOrder(NODE *node) 		/* 前序遍历函数			*/
{
	if(node == NULL)
		return;
	printf("%c %d %s\n", node->key, node->weigh, node->code);
	preOrder(node->left);
	preOrder(node->right);
}
void LeafOrder(NODE *node) 		/* 结果遍历函数			*/
{
	if(node == NULL)
		return;
	if(!node->left && !node->right)
		printf("%c %d %s\n", node->key, node->weigh, node->code);
	LeafOrder(node->left);
	LeafOrder(node->right);
}
void insertNode(NODE *node) 	/* 按频度升序插入结点	*/
{
	NODE *prev = Head;
	while(prev->next && node->weigh > prev->next->weigh)
		prev = prev->next;
	node->next = prev->next;
	prev->next = node;
}
void MakeTree() 				/* 生成Huffman树函数	*/
{
	NODE *node;
	while(Head->next->next)
	{
		if((node = (NODE *)malloc(sizeof(NODE))) == NULL)
			exit(0);
		node->left = Head->next;		/* 链接左子		*/
		Head->next = Head->next->next;	/* 删除结点		*/
		node->right = Head->next;		/* 链接右子		*/
		Head->next = Head->next->next;	/* 删除结点		*/
		node->key = '#';			/* 用#表示空结点值	*/
		node->code[0] = '\0';
		node->weigh = node->left->weigh + node->right->weigh;
		insertNode(node); 		/* 按频度升序插入结点	*/
		prt();
	}
}
void MakeCode(NODE *node) 		/* 生成Huffman编码函数	*/
{
	if(node == NULL)
		return;
	if(node->left)
	{
		strcpy(node->left->code, node->code);
		strcat(node->left->code, "0");
		MakeCode(node->left);
	}
	if(node->right)
	{
		strcpy(node->right->code, node->code);
		strcat(node->right->code, "1");
		MakeCode(node->right);
	}
}
void main()
{
	char key[10];
	int weigh;
	NODE *node;
	FILE *fp;
	char filename[60];
	printf("输入结点文件: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		exit(0);
	if((Head = (NODE *)malloc(sizeof(NODE))) == NULL)
		exit(0);
	Head->next = NULL;
	Head->key = '-';
	while(fscanf(fp, "%s%d", key, &weigh) == 2)
	{
		if((node = (NODE *)malloc(sizeof(NODE))) == NULL)
			exit(0);
		node->key = key[0];
		node->weigh = weigh;
		node->code[0] = '\0';
		node->left = NULL;
		node->right = NULL;
		insertNode(node);
	}
	prt();
	printf("MakeTree\n");
	MakeTree();
	MakeCode(Head->next);
	printf("prtCode\n");
	prtCode(Head->next);
	printf("lengh of code = %d\n", lenCode);
	system("pause");
}
/*
node1.txt
A 2 D 4 G 5 O 8
MakeTree
G 5 # 6 O 8
O 8 # 11
# 19
prtCode
O 8 [0] 8
G 5 [10] 10
A 2 [110] 6
D 4 [111] 12
lengh of code = 36

node2.txt
V 1 G 2 L 5 R 6 N 7 E 10
MakeTree
# 3 L 5 R 6 N 7 E 10
R 6 N 7 # 8 E 10
# 8 E 10 # 13
# 13 # 18
# 31
prtCode
R 6 [00] 12
N 7 [01] 14
V 1 [1000] 4
G 2 [1001] 8
L 5 [101] 15
E 10 [11] 20
lengh of code = 73

node3.txt
B 2 Y 3 D 4 A 8 H 10 O 11
MakeTree
D 4 # 5 A 8 H 10 O 11
A 8 # 9 H 10 O 11
H 10 O 11 # 17
# 17 # 21
# 38
prtCode
A 8 [00] 16
D 4 [010] 12
B 2 [0110] 8
Y 3 [0111] 12
H 10 [10] 20
O 11 [11] 22
lengh of code = 90

node4.txt
P 2 F 3 C 4 S 7 O 8 E 10
MakeTree
C 4 # 5 S 7 O 8 E 10
S 7 O 8 # 9 E 10
# 9 E 10 # 15
# 15 # 19
# 34
prtCode
S 7 [00] 14
O 8 [01] 16
C 4 [100] 12
P 2 [1010] 8
F 3 [1011] 12
E 10 [11] 20
lengh of code = 82

node5.txt
P 2 M 3 U 4 H 6 N 7 T 8
MakeTree
U 4 # 5 H 6 N 7 T 8
H 6 N 7 T 8 # 9
T 8 # 9 # 13
# 13 # 17
# 30
prtCode
H 6 [00] 12
N 7 [01] 14
T 8 [10] 16
U 4 [110] 12
P 2 [1110] 8
M 3 [1111] 12
lengh of code = 74

node6.txt
P 2 M 3 U 6 H 12 N 13 T 14
MakeTree
# 5 U 6 H 12 N 13 T 14
# 11 H 12 N 13 T 14
N 13 T 14 # 23
# 23 # 27
# 50
prtCode
P 2 [0000] 8
M 3 [0001] 12
U 6 [001] 18
H 12 [01] 24
N 13 [10] 26
T 14 [11] 28
lengh of code = 116
*/