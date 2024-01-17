/*	File: Ñ¡ÔñÅÅĞò.c
	¡¾Àı4-6¡¿Ë³Ğò´æ´¢Ñ¡ÔñÅÅĞò	*/

#include <stdio.h>
#include <stdlib.h>
#define M 10
void prt(int *a, int n, int k)
{
	int i;
	for(i=0; i<n; i++)
		printf("%c%d%c", i==0 ? '[' : ' ', a[i], i==k ? ']' : ' ');
	printf("\n");
}
void swap2(int *x, int *y)
{	
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}
void select(int *a, int n)
{ 		  
	short left, mini, i;
	for(left=0; left<n-1; left++)
	{
		for(mini=left, i=left+1; i<n; i++)
			if(a[i] < a[mini])
				mini = i;
		swap2(&a[left], &a[mini]);
		prt(a, n, left);
	}
}
int main()
{
	int a[M];
	int i, n;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	printf("ÅÅÑ¡ÔñĞò\n");
	select(a, n); 
	system("pause");
}

/*
ÊäÈëÊı¾İ
7
8  4  3  6  9  2  7
Ñ¡ÔñÅÅĞò
[2] 4  3  6  9  8  7
[2  3] 4  6  9  8  7
[2  3  4] 6  9  8  7
[2  3  4  6] 9  8  7
[2  3  4  6  7] 8  9
[2  3  4  6  7  8] 9

8
5 2 7 3 1 4 8 6
Ñ¡ÔñÅÅĞò
[1] 2  7  3  5  4  8  6
[1  2] 7  3  5  4  8  6
[1  2  3] 7  5  4  8  6
[1  2  3  4] 5  7  8  6
[1  2  3  4  5] 7  8  6
[1  2  3  4  5  6] 8  7
[1  2  3  4  5  6  7] 8

7
5 7 3 1 4 8 6
Ñ¡ÔñÅÅĞò
[1] 7  3  5  4  8  6
[1  3] 7  5  4  8  6
[1  3  4] 5  7  8  6
[1  3  4  5] 7  8  6
[1  3  4  5  6] 8  7
[1  3  4  5  6  7] 8

10
5 1 0 7 9 2 3 8 6 4
ÅÅÑ¡ÔñĞò
[0] 1  5  7  9  2  3  8  6  4
[0  1] 5  7  9  2  3  8  6  4
[0  1  2] 7  9  5  3  8  6  4
[0  1  2  3] 9  5  7  8  6  4
[0  1  2  3  4] 5  7  8  6  9
[0  1  2  3  4  5] 7  8  6  9
[0  1  2  3  4  5  6] 8  7  9
[0  1  2  3  4  5  6  7] 8  9
[0  1  2  3  4  5  6  7  8] 9
*/
