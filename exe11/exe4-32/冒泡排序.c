/*	File: √∞≈›≈≈–Ú.c
	°æœ∞Ã‚4-32°øÀ≥–Ú¥Ê¥¢√∞≈›≈≈–Ú	*/

#include <stdio.h>
#include <stdlib.h>
void swap2(int *x, int *y)
{	
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}
void prt(int a[], int n, int k)
{
	int i;
	for(i=0; i<n; i++)
		printf("%c%d%c", i==0 ? '[' : ' ', a[i], i==k ? ']' : ' ');
	printf("\n");
}
void bubble(int a[], int n)
{
	int i, j, tmp, s;
	for(i=0; i<n-1; i=s)
	{
		s = n-1;
		for (j = n-1; j > i; j--)
		{
			if (a[j] < a[j-1])
			{
				swap2(&a[j-1],&a[j]);
				s = j;
			}
		}
		if(s < n-1)
			prt(a, n, s-1);
	}
	prt(a, n, s);
}
void main()
{
	int a[20], n, i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	printf("√∞≈›≈≈–Ú\n");
	bubble(a, n);
	system("pause");
}
/*
 ‰»Î ˝æ›1
6
5 4 1 2 8 7
√∞≈›≈≈–Ú
[1] 5  4  2  7  8
[1  2] 5  4  7  8
[1  2  4] 5  7  8
[1  2  4  5  7  8]

 ‰»Î ˝æ›2
9
2 3 4 1 5 6 7 8 9
√∞≈›≈≈–Ú
[1] 2  3  4  5  6  7  8  9
[1  2  3  4  5  6  7  8  9]
*/