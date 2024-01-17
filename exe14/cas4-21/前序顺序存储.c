/*	File: 前序顺序存储.c
    【例4-21】前序顺序存储二叉树	*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define M 100
#define ABS(X) ((X > 0) ? (X) : (-X))
#define BITREE struct bitree
BITREE {
    char key;
    int pk;
};
BITREE tree[M];               /* 二叉树数组	*/
int n;
void preOrderS(BITREE tree[]) /* 按存储顺序前序遍历函数	*/
{
    int i;
    for (i = 1; i <= tree[0].pk; i++) /* 顺序打印所有结点		*/
        printf("%c ", tree[i].key);
}
void preOrder(BITREE tree[], int k) /* 前序遍历函数			*/
{
    printf("%c ", tree[k].key);
    if (tree[k].pk > 0)
        preOrder(tree, k + 1);           /* 按前序遍历左子树	*/
    if (ABS(tree[k].pk) < n + 1)
        preOrder(tree, ABS(tree[k].pk)); /* 按前序遍历右子树	*/
}
void symOrder(BITREE tree[], int k)      /* 中序遍历函数		*/
{
    if (tree[k].pk > 0)
        symOrder(tree, k + 1); /* 按中序遍历左子树	*/
    printf("%c ", tree[k].key);
    if (ABS(tree[k].pk) < n + 1)
        symOrder(tree, ABS(tree[k].pk)); /* 按中序遍历右子树	*/
}
void postOrder(BITREE tree[], int k)     /* 后序遍历函数		*/
{
    if (tree[k].pk > 0)
        postOrder(tree, k + 1);           /* 按后序遍历左子树	*/
    if (ABS(tree[k].pk) < n + 1)
        postOrder(tree, ABS(tree[k].pk)); /* 按后序遍历右子树	*/
    printf("%c ", tree[k].key);
}
void main() {
    int i, pk;
    char key[10];
    printf("请输入二叉树: ");
    scanf("%d", &n);

    tree[0].pk = n;
    for (i = 1; i <= n; i++) {
        scanf("%s%d", key, &pk);
        tree[i].key = key[0];
        tree[i].pk = pk;
    }

    printf("存储顺序\n前序遍历: ");
    preOrderS(tree);
    printf("\n");
    printf("递归方法\n前序遍历: ");
    preOrder(tree, 1);
    printf("\n");
    printf("中序遍历: ");
    symOrder(tree, 1);
    printf("\n");
    printf("后序遍历: ");
    postOrder(tree, 1);
    printf("\n");
    system("pause");
}
/*
运行示例
8
A  6
B  -3
D  5
G  -9
H  -9
C  9
E  -8
F  -9
存储顺序
前序遍历: A B D G H C E F
递归方法
前序遍历: A B D G H C E F
中序遍历: B G D H A E F C
后序遍历: G H D B F E C A

 8
A  6
B  4
D  -9
C  9
F  -9
E  9
G  -8
H  -9
存储顺序
前序遍历: A B D C F E G H
递归方法
前序遍历: A B D C F E G H
中序遍历: D B F C A G H E
后序遍历: D F C B H G E A
*/
