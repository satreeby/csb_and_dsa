/* File: BiSearch.c
	【例4-1】二分查找算法	*/

#include <stdio.h>
#include <stdlib.h>
void prt(int *a, int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%d ", a[i]);
	printf("\n");
}
int	BiSearch(int *a, int n, int key)
{ 
	int begin=0, end=n-1, middle;
	while(begin <= end)
	{
		middle = (begin + end) / 2;
		printf("middle=%d, a[%d]=%d\n", middle, middle, a[middle]);
		if(a[middle] == key)			/* 查找成功			*/
			return(middle);
		else if(key > a[middle]) 		/* 改为右半部分查找	*/
			begin = middle + 1;
		else if(key < a[middle]) 		/* 改为左半部分查找	*/
			end = middle - 1;
	}
	return(-1); 						/* 查找失败			*/
} 
int main()
{
	int a[30];
	int n, i, key;
	scanf("%d", &n);
	for(i=0; i< n; i++)
		scanf("%d", &a[i]);
	printf("Please Enter the key to search:");
	scanf("%d", &key);
	i = BiSearch(a, n, key); 
	if(i < 0)
		printf("fail to find node %d\n", key);
	else
		printf("node[%d] = %d\n", i, a[i]);
	system("pause");
}
/*
15
2 4 7 11 27 36 37 38 42 49 50 59 61 68 75

Please Enter the key to search:27
middle=7, a[7]=38
middle=3, a[3]=11
middle=5, a[5]=36
middle=4, a[4]=27
node[4] = 27

Please Enter the key to search:60
middle=7, a[7]=38
middle=11, a[11]=59
middle=13, a[13]=68
middle=12, a[12]=61
fail to find node 60
*/