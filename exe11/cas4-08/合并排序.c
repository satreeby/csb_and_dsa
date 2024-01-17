/*	File: 合并排序.c
	【例4-8】顺序存储合并排序	*/

#include <stdio.h>
#include <stdlib.h>
#define M 20
prt(int *a, int begin, int end)
{
	int i;
	for(i=begin; i<=end; i++)
		printf("%c%d%c", i==begin ? '[' : ' ', a[i],
				i==end ? ']' : ' ');
}
void combine(int *a, int begin, int mid, int end)
{ 		  
	int left=begin, right=mid+1, i;
	int b[M];
	for(i=begin; i<=end; i++)
		b[i] = a[i];
	prt(b, begin, mid);
	prt(b, mid+1, end);
	printf("\n");
	for(i=begin; i<=end; i++)
	{
		if(right>end)				/* 右端数据已遍历	*/
			a[i] = b[left++];		/* 复制左端数据		*/
		else if(left > mid) 		/* 左端结点已遍历	*/
			a[i] = b[right++];		/* 复制右端数据		*/
		else if(b[left] < b[right]) 
			a[i] = b[left++];		/* 复制左端较小结点	*/
		else
			a[i] = b[right++];		/* 复制右端较小结点	*/
	}
	prt(a, begin, end);
	printf("\n");
}
void merge(int *a, int begin, int end)
{
	int mid;
	if(begin < end) 					/* 如果不成立begin < end，结束递归		*/
	{
		mid = (begin + end) / 2; 		/* 计算中点mid							*/
		merge(a, begin, mid); 			/* 对左端进行递归合并划分				*/
		merge(a, mid+1, end);			/* 对右端进行递归合并划分				*/
		combine(a, begin, mid, end); 	/* 合并有序表							*/
	}
}
int main()
{
	int a[M];
	int n, i;
	scanf("%d", &n);
	for(i=0; i< n; i++)
		scanf("%d", &a[i]);
	merge(a, 0, n-1); 
	printf("合并排序结果\n");
	for(i=0; i< n; i++)
		printf("%d ", a[i]);
	printf("\n");
	system("pause");
}
/*
8
5 2 7 3 1 6 8 4
[5][2]
[2  5]
[7][3]
[3  7]
[2  5][3  7]
[2  3  5  7]
[1][6]
[1  6]
[8][4]
[4  8]
[1  6][4  8]
[1  4  6  8]
[2  3  5  7][1  4  6  8]
[1  2  3  4  5  6  7  8]
合并排序结果
1 2 3 4 5 6 7 8

9
5  2  9  1  8  3  7  4  6
[5][2]
[2  5]
[2  5][9]
[2  5  9]
[1][8]
[1  8]
[2  5  9][1  8]
[1  2  5  8  9]
[3][7]
[3  7]
[4][6]
[4  6]
[3  7][4  6]
[3  4  6  7]
[1  2  5  8  9][3  4  6  7]
[1  2  3  4  5  6  7  8  9]
合并排序结果
1 2 3 4 5 6 7 8 9

11
5 2 11 9 7 3 1 6 8 10 4
[5][2]
[2  5]
[2  5][11]
[2  5  11]
[9][7]
[7  9]
[7  9][3]
[3  7  9]
[2  5  11][3  7  9]
[2  3  5  7  9  11]
[1][6]
[1  6]
[1  6][8]
[1  6  8]
[10][4]
[4  10]
[1  6  8][4  10]
[1  4  6  8  10]
[2  3  5  7  9  11][1  4  6  8  10]
[1  2  3  4  5  6  7  8  9  10  11]
合并排序结果
1 2 3 4 5 6 7 8 9 10 11
*/
