/*	File: exe3-10��άɨ������Ϸ.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 4		/* �������� = N x N	*/
void laymine(int mine[][N], int n, int allMine)
{
	int j, k, random, m;
	time_t w;
	for(j=0; j<n; j++)
	for(k=0; k<n; k++)
		mine[j][k] = 0;
	srand((unsigned int)time(&w));
	for(m=0; m<allMine; )
	{
		/* complete code here	*/
		random = rand() % (n*n) + 1;
		if (mine[((random-1)/n)][((random-1)%n)] == 0)
		{
			/* code */
			mine[((random-1)/n)][((random-1)%n)] = random;
			m++;
		}
		
	
	}
}
void sweepmine(int mine[][N], int n, int *allMine)	/* ���ɨ�׺���	*/
{
	int j, k;
	printf("��ɨ��[��1-%d�е�1-%d��]��", n, n);
	scanf("%d%d", &j, &k);
	/* complete code here	*/
	if (j > 0 && j <= n && k > 0 && k <= n && mine[j-1][k-1] )
	{
		/* code */
		mine[j-1][k-1] = 0;
		(*allMine)--;
	}
	



}

void prt(int mine[][N], int n, int allMine)
{
	short j, k;
	printf("ɨ�׽�����ʣ��%d�����ף��ֲ�Ϊ:\n", allMine);
	for(j=0; j<n; j++)
	{
		for(k=0; k<n; k++)
			printf("%3d", mine[j][k]);
		printf("\n");
	}
}
void main()
{
	int mine[N][N], n=N, allMine=n, tryTime, allTime;
	printf("****��ӭ���Զ�άɨ������Ϸ****\n\n");
	while(allMine > 2)
	{
		printf("���벼��������?[2-%2d��Ϊ��Ч,�����ʾ������Ϸ]: ", n*n-3);
		scanf("%d", &allMine);
		if(allMine < 2 || allMine > n*n-3)
			break;
		allTime = allMine + 2;	/* ���ɨ�״���=��������+2	*/
		tryTime = 0;
		laymine(mine, n, allMine);
		while(allMine > 0 && tryTime < allTime)
		{
			printf("����%2d������. ", allMine);
			printf("�㻹��%2d�λ���. ", allTime-tryTime);
			sweepmine(mine, n, &allMine);
			++tryTime;
		}
		prt(mine, n, allMine);
		allMine = n;
		printf("\n��ӭ����һ��\n");
	}
	printf("\n****��ӭ�´���������ɨ������Ϸ****\n\n");
	system("pause");
}
/*
****��ӭ����ɨ������Ϸ****

���벼��������?[2-13��Ϊ��Ч,�����ʾ������Ϸ]: 3
���� 3������. �㻹�� 5�λ���. ��ɨ��[��1-4�е�1-4��]��1 1
���� 3������. �㻹�� 4�λ���. ��ɨ��[��1-4�е�1-4��]��1 2
���� 3������. �㻹�� 3�λ���. ��ɨ��[��1-4�е�1-4��]��1 3
���� 3������. �㻹�� 2�λ���. ��ɨ��[��1-4�е�1-4��]��1 4
���� 3������. �㻹�� 1�λ���. ��ɨ��[��1-4�е�1-4��]��2 1
ɨ�׽�����ʣ��3�����ף��ֲ�Ϊ:
  0  0  0  0
  0  0  7  0
  0 10 11  0
  0  0  0  0

��ӭ����һ��
���벼��������?[2-13��Ϊ��Ч,�����ʾ������Ϸ]: 4
���� 4������. �㻹�� 6�λ���. ��ɨ��[��1-4�е�1-4��]��1 1
���� 4������. �㻹�� 5�λ���. ��ɨ��[��1-4�е�1-4��]��1 2
���� 3������. �㻹�� 4�λ���. ��ɨ��[��1-4�е�1-4��]��1 3
���� 3������. �㻹�� 3�λ���. ��ɨ��[��1-4�е�1-4��]��1 4
���� 3������. �㻹�� 2�λ���. ��ɨ��[��1-4�е�1-4��]��2 1
���� 2������. �㻹�� 1�λ���. ��ɨ��[��1-4�е�1-4��]��2 2
ɨ�׽�����ʣ��2�����ף��ֲ�Ϊ:
  0  0  0  0
  0  0  0  0
  9 10  0  0
  0  0  0  0

��ӭ����һ��
���벼��������?[2-13��Ϊ��Ч,�����ʾ������Ϸ]: 0

****��ӭ�´���������ɨ������Ϸ****
*/