/*	File: exe3-10ɨ������Ϸ.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10		/* �������򳤶�	*/
void laymine(int mine[], int n, int allMine)
{
	int k, random, m;
	time_t w;
	for(k=0; k<n; k++)
		mine[k] = 0;
	srand((unsigned int)time(&w));
	for(m=0; m<allMine; )
	{
		random = rand() % n + 1;
		if(mine[random-1] == 0)
		{
			mine[random-1] = random;
			m++;
		}
	}
}
void sweepmine(int mine[], int n, int *allMine)	/* ���ɨ�׺���	*/
{
	int goal;
	printf("��ɨ��[1-%d]��", n-1);
	scanf("%d", &goal);
	if(goal > 0 && goal <= n && mine[goal-1])
	{
		mine[goal-1] = 0; 						/* ɨ�׳ɹ�		*/
		(*allMine)--;							/* ���������1	*/
	}
}
void prt(int mine[], int n, int allMine)
{
	short k;
	printf("ɨ�׽�����ʣ��%d�����ף��ֲ�Ϊ:", allMine);
	for(k=0; k<n; k++)
		printf("%3d", mine[k]);
	printf("\n");
}
void main()
{
	int mine[N], n=N, allMine=n, tryTime, allTime;
	printf("****��ӭ����ɨ������Ϸ****\n\n");
	while(allMine > 2)
	{
		printf("���벼��������?[2-%2d��Ϊ��Ч,�����ʾ������Ϸ]: ", n-3);
		scanf("%d", &allMine);
		if(allMine < 2 || allMine > n-3)
			break;
		allTime = allMine + 2;	/* ���ɨ�״���=��������+2	*/
		tryTime = 0;
		laymine(mine, n, allMine);
		while(allMine > 0 && tryTime < allTime)
		{
			printf("����%d������. ", allMine);
			printf("�㻹��%d�λ���. ", allTime-tryTime);
			sweepmine(mine, n, &allMine);
			++tryTime;
		}
		prt(mine, n, allMine);
		allMine = n;
		printf("\n����һ����?\n");
	}
	printf("\n****��ӭ�´���������ɨ������Ϸ****\n\n");
	system("pause");
}
/*
****��ӭ����ɨ������Ϸ****

���벼��������?[2- 7��Ϊ��Ч,�����ʾ������Ϸ]: 5
����5������. �㻹��7�λ���. ��ɨ��[1-9]��1
����4������. �㻹��6�λ���. ��ɨ��[1-9]��2
����4������. �㻹��5�λ���. ��ɨ��[1-9]��3
����3������. �㻹��4�λ���. ��ɨ��[1-9]��4
����3������. �㻹��3�λ���. ��ɨ��[1-9]��5
����3������. �㻹��2�λ���. ��ɨ��[1-9]��6
����2������. �㻹��1�λ���. ��ɨ��[1-9]��7
ɨ�׽�����ʣ��1�����ף��ֲ�Ϊ:  0  0  0  0  0  0  0  8  0  0

����һ����?
���벼��������?[2- 7��Ϊ��Ч,�����ʾ������Ϸ]: 0

****��ӭ�´���������ɨ������Ϸ****

�밴���������. . .
*/