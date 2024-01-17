/*	File: 插入排序.c
	【习题4-31】顺序存储插入排序(降序)	*/

#include <stdio.h>
#include <stdlib.h>
void error(char *str)
{
    printf("%s\n", str);
	exit(0);
}
void prt(int a[], int n, int k)
{
	int i;
	for(i=0; i<n; i++)
		printf("%c%d%c", i==0 ? '[' : ' ', a[i], i==k ? ']' : ' ');
	printf("\n");
}
void insertS(int a[], int n)
{
	int key, s, k;
	prt(a, n, 0);
	for(s=1; s<n; s++)
	{
		key = a[n-1];
		for ( k = n-1; k > s; k--)
			a[k] = a[k-1]; 
		for ( k = s; k > 0; k--)
			if (a[k-1]<key)
				a[k]=a[k-1];
			else
				break;
		a[k] = key;
		prt(a, n, s);
	}
}
void main()
{
	int a[20], n, i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	printf("插入排序\n");
	insertS(a, n);
	system("pause");
}
/*
输入数据0
5
6 2 8 4 5
插入排序
[6] 2  8  4  5
[6  5] 2  8  4
[6  5  4] 2  8
[8  6  5  4] 2
[8  6  5  4  2]

输入数据1
5
1 7 8 4 5
插入排序
[1] 7  8  4  5
[5  1] 7  8  4
[5  4  1] 7  8
[8  5  4  1] 7
[8  7  5  4  1]

输入数据2
9
2 3 4 1 5 6 7 8 9
插入排序
[2] 3  4  1  5  6  7  8  9
[9  2] 3  4  1  5  6  7  8
[9  8  2] 3  4  1  5  6  7
[9  8  7  2] 3  4  1  5  6
[9  8  7  6  2] 3  4  1  5
[9  8  7  6  5  2] 3  4  1
[9  8  7  6  5  2  1] 3  4
[9  8  7  6  5  4  2  1] 3
[9  8  7  6  5  4  3  2  1]

输入数据3
7
8 4 3 6 9 2 7
插入排序
[8] 4  3  6  9  2  7
[8  7] 4  3  6  9  2
[8  7  2] 4  3  6  9
[9  8  7  2] 4  3  6
[9  8  7  6  2] 4  3
[9  8  7  6  3  2] 4
[9  8  7  6  4  3  2]
*/