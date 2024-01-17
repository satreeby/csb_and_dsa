/* File: 快速排序.c
	【例4-7】顺序存储快速排序	*/
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
	key = a[M]; 					/* 暂存key，a[left]为空位			*/
	while(L < R)
	{
		while(a[R] > key && L < R) 	/* 从右向左查找小于key的结点		*/
			R--;					/* 若a[R]>key，R递减				*/
		if(L < R) 					/* 找到a[R]<key						*/
		{
			a[M] = a[R]; 			/* 将a[R]向左移到a[L]，a[R]成为空位	*/
			M = R;
		}
		while(a[L] <= key && L < R) 	/* 从左向右查找大于key的结点		*/
			L++;					/* 若a[L]<key，L递增				*/
		if(L < R) 					/* 找到a[L]>key						*/
		{
			a[M] = a[L]; 			/* 将a[L]向右移到a[R]，a[L]成为空位	*/
			M = L;
		}
	}
	a[M] = key; 					/* 将暂存key落位a[L]，完成划分操作	*/
	for(i=0; i<n; i++)
		printf("%c%d%c", i==L? '[' : ' ', a[i], i==L? ']' : ' ');
	printf("\n");
	quick(a, left, L-1); 			/* 对ULEFT递归执行快速排序			*/
	quick(a, L+1, right); 			/* 对URIGHT递归执行快速排序			*/
}
void main()
{
	int a[N];
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	printf("快速排序\n");
	quick(a, 0, n-1);
	for(i=0; i<n; i++)
		printf(" %d ", a[i]);
	printf("\n");
}
/*
输入数据1
9 
5  1  0  7  2  3  8  6  4
快速排序
 0  1 [2] 7  5  3  8  6  4
[0] 1  2  7  5  3  8  6  4
 0  1  2 [3] 5  7  8  6  4
 0  1  2  3  5  7  4  6 [8]
 0  1  2  3  5  6  4 [7] 8
 0  1  2  3  5  4 [6] 7  8
 0  1  2  3  4 [5] 6  7  8
 0  1  2  3  4  5  6  7  8

输入数据2
8
 3  7  8  6  4  1  2  9
快速排序
 3  1  4  2 [6] 8  7  9
[1] 3  4  2  6  8  7  9
 1  3  2 [4] 6  8  7  9
 1  2 [3] 4  6  8  7  9
 1  2  3  4  6 [7] 8  9
 1  2  3  4  6  7 [8] 9
 1  2  3  4  6  7  8  9

输入数据3
8
 2  7  8  6  4  1  2  9
快速排序
 2  1  4  2 [6] 8  7  9
[1] 2  4  2  6  8  7  9
 1  2  2 [4] 6  8  7  9
 1  2 [2] 4  6  8  7  9
 1  2  2  4  6 [7] 8  9
 1  2  2  4  6  7 [8] 9
 1  2  2  4  6  7  8  9
*/