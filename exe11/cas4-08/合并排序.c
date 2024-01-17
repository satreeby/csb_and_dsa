/*	File: �ϲ�����.c
	����4-8��˳��洢�ϲ�����	*/

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
		if(right>end)				/* �Ҷ������ѱ���	*/
			a[i] = b[left++];		/* �����������		*/
		else if(left > mid) 		/* ��˽���ѱ���	*/
			a[i] = b[right++];		/* �����Ҷ�����		*/
		else if(b[left] < b[right]) 
			a[i] = b[left++];		/* ������˽�С���	*/
		else
			a[i] = b[right++];		/* �����Ҷ˽�С���	*/
	}
	prt(a, begin, end);
	printf("\n");
}
void merge(int *a, int begin, int end)
{
	int mid;
	if(begin < end) 					/* ���������begin < end�������ݹ�		*/
	{
		mid = (begin + end) / 2; 		/* �����е�mid							*/
		merge(a, begin, mid); 			/* ����˽��еݹ�ϲ�����				*/
		merge(a, mid+1, end);			/* ���Ҷ˽��еݹ�ϲ�����				*/
		combine(a, begin, mid, end); 	/* �ϲ������							*/
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
	printf("�ϲ�������\n");
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
�ϲ�������
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
�ϲ�������
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
�ϲ�������
1 2 3 4 5 6 7 8 9 10 11
*/
