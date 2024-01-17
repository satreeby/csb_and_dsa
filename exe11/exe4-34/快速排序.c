/* File: ��������.c
	����4-7��˳��洢��������	*/
#include<stdio.h>
#include<stdlib.h>
#define N 100
int i, n;
void quick(int a[], int left, int right)
{
	int key, L = left, R = right;
	if(left >= right)
		return;
	/* complete the follwing code	*/
	key = a[R];
	while (L < R)
	{
		while (a[L] < key && L < R)
		{
			L++;
		}
		if (L < R)
		{
			a[R--]=a[L];
		}
		while (a[R] >= key && L < R)
		{
			R--;
		}
		if (L < R)
		{
			a[L++] = a[R];
		}
	}
	a[R] = key;
	/* ---------------------------	*/
	for(i=0; i<n; i++)
		printf("%c%d%c", i==L? '[' : ' ', a[i], i==L? ']' : ' ');
	printf("\n");
	/* complete the follwing code	*/
	quick(a,L+1,right);
	quick(a,left,L-1);
	/* ---------------------------	*/
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
	system("pause");
}
/*
��������
8
4 1 7 9 2 8 5 6
��������
 4  1  5  2 [6] 8  9  7
 4  1  5  2  6 [7] 9  8
 4  1  5  2  6  7 [8] 9
 1 [2] 5  4  6  7  8  9
 1  2 [4] 5  6  7  8  9
 1  2  4  5  6  7  8  9

��������
10 
5  1  7  0  9  2  8  3  6  4
��������
 3  1  2  0 [4] 9  8  7  6  5
 3  1  2  0  4 [5] 8  7  6  9
 3  1  2  0  4  5  8  7  6 [9]
 3  1  2  0  4  5 [6] 7  8  9
 3  1  2  0  4  5  6  7 [8] 9
[0] 1  2  3  4  5  6  7  8  9
 0  1  2 [3] 4  5  6  7  8  9
 0  1 [2] 3  4  5  6  7  8  9
 0  1  2  3  4  5  6  7  8  9
*/
