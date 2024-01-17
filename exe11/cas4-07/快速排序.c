/* File: ��������.c
	����4-7��˳��洢��������	*/
#include<stdio.h>
#include <string.h>
#define N 100
int i, n;
void quick(int a[], int left, int right)
{
	int key, L=left, R=right, M;
	if(left >= right)
		return;
	M = (left + right) / 2;
	key = a[M]; 					/* �ݴ�key��a[left]Ϊ��λ			*/
	while(L < R)
	{
		while(a[R] > key && L < R) 	/* �����������С��key�Ľ��		*/
			R--;					/* ��a[R]>key��R�ݼ�				*/
		if(L < R) 					/* �ҵ�a[R]<key						*/
		{
			a[M] = a[R]; 			/* ��a[R]�����Ƶ�a[L]��a[R]��Ϊ��λ	*/
			M = R;
		}
		while(a[L] <= key && L < R) 	/* �������Ҳ��Ҵ���key�Ľ��		*/
			L++;					/* ��a[L]<key��L����				*/
		if(L < R) 					/* �ҵ�a[L]>key						*/
		{
			a[M] = a[L]; 			/* ��a[L]�����Ƶ�a[R]��a[L]��Ϊ��λ	*/
			M = L;
		}
	}
	a[M] = key; 					/* ���ݴ�key��λa[L]����ɻ��ֲ���	*/
	for(i=0; i<n; i++)
		printf("%c%d%c", i==L? '[' : ' ', a[i], i==L? ']' : ' ');
	printf("\n");
	quick(a, left, L-1); 			/* ��ULEFT�ݹ�ִ�п�������			*/
	quick(a, L+1, right); 			/* ��URIGHT�ݹ�ִ�п�������			*/
}
void main()
{
	int a[N];
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	printf("��������\n");
	quick(a, 0, n-1);
	for(i=0; i<n; i++)
		printf(" %d ", a[i]);
	printf("\n");
}
/*
��������1
9 
5  1  0  7  2  3  8  6  4
��������
 0  1 [2] 7  5  3  8  6  4
[0] 1  2  7  5  3  8  6  4
 0  1  2 [3] 5  7  8  6  4
 0  1  2  3  5  7  4  6 [8]
 0  1  2  3  5  6  4 [7] 8
 0  1  2  3  5  4 [6] 7  8
 0  1  2  3  4 [5] 6  7  8
 0  1  2  3  4  5  6  7  8

��������2
8
 3  7  8  6  4  1  2  9
��������
 3  1  4  2 [6] 8  7  9
[1] 3  4  2  6  8  7  9
 1  3  2 [4] 6  8  7  9
 1  2 [3] 4  6  8  7  9
 1  2  3  4  6 [7] 8  9
 1  2  3  4  6  7 [8] 9
 1  2  3  4  6  7  8  9

��������3
8
 2  7  8  6  4  1  2  9
��������
 2  1  4  2 [6] 8  7  9
[1] 2  4  2  6  8  7  9
 1  2  2 [4] 6  8  7  9
 1  2 [2] 4  6  8  7  9
 1  2  2  4  6 [7] 8  9
 1  2  2  4  6  7 [8] 9
 1  2  2  4  6  7  8  9
*/