/*	File: ǰ��˳��洢.c
    ����4-21��ǰ��˳��洢������	*/

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
BITREE tree[M];               /* ����������	*/
int n;
void preOrderS(BITREE tree[]) /* ���洢˳��ǰ���������	*/
{
    int i;
    for (i = 1; i <= tree[0].pk; i++) /* ˳���ӡ���н��		*/
        printf("%c ", tree[i].key);
}
void preOrder(BITREE tree[], int k) /* ǰ���������			*/
{
    printf("%c ", tree[k].key);
    if (tree[k].pk > 0)
        preOrder(tree, k + 1);           /* ��ǰ�����������	*/
    if (ABS(tree[k].pk) < n + 1)
        preOrder(tree, ABS(tree[k].pk)); /* ��ǰ�����������	*/
}
void symOrder(BITREE tree[], int k)      /* �����������		*/
{
    if (tree[k].pk > 0)
        symOrder(tree, k + 1); /* ���������������	*/
    printf("%c ", tree[k].key);
    if (ABS(tree[k].pk) < n + 1)
        symOrder(tree, ABS(tree[k].pk)); /* ���������������	*/
}
void postOrder(BITREE tree[], int k)     /* �����������		*/
{
    if (tree[k].pk > 0)
        postOrder(tree, k + 1);           /* ���������������	*/
    if (ABS(tree[k].pk) < n + 1)
        postOrder(tree, ABS(tree[k].pk)); /* ���������������	*/
    printf("%c ", tree[k].key);
}
void main() {
    int i, pk;
    char key[10];
    printf("�����������: ");
    scanf("%d", &n);

    tree[0].pk = n;
    for (i = 1; i <= n; i++) {
        scanf("%s%d", key, &pk);
        tree[i].key = key[0];
        tree[i].pk = pk;
    }

    printf("�洢˳��\nǰ�����: ");
    preOrderS(tree);
    printf("\n");
    printf("�ݹ鷽��\nǰ�����: ");
    preOrder(tree, 1);
    printf("\n");
    printf("�������: ");
    symOrder(tree, 1);
    printf("\n");
    printf("�������: ");
    postOrder(tree, 1);
    printf("\n");
    system("pause");
}
/*
����ʾ��
8
A  6
B  -3
D  5
G  -9
H  -9
C  9
E  -8
F  -9
�洢˳��
ǰ�����: A B D G H C E F
�ݹ鷽��
ǰ�����: A B D G H C E F
�������: B G D H A E F C
�������: G H D B F E C A

 8
A  6
B  4
D  -9
C  9
F  -9
E  9
G  -8
H  -9
�洢˳��
ǰ�����: A B D C F E G H
�ݹ鷽��
ǰ�����: A B D C F E G H
�������: D B F C A G H E
�������: D F C B H G E A
*/
