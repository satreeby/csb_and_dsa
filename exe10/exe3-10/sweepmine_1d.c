/*	File: exe3-10扫地雷游戏.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10		/* 布雷区域长度	*/
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
void sweepmine(int mine[], int n, int *allMine)	/* 玩家扫雷函数	*/
{
	int goal;
	printf("请扫雷[1-%d]：", n-1);
	scanf("%d", &goal);
	if(goal > 0 && goal <= n && mine[goal-1])
	{
		mine[goal-1] = 0; 						/* 扫雷成功		*/
		(*allMine)--;							/* 令地雷数减1	*/
	}
}
void prt(int mine[], int n, int allMine)
{
	short k;
	printf("扫雷结束。剩余%d个地雷，分布为:", allMine);
	for(k=0; k<n; k++)
		printf("%3d", mine[k]);
	printf("\n");
}
void main()
{
	int mine[N], n=N, allMine=n, tryTime, allTime;
	printf("****欢迎尝试扫地雷游戏****\n\n");
	while(allMine > 2)
	{
		printf("你想布几个地雷?[2-%2d个为有效,否则表示结束游戏]: ", n-3);
		scanf("%d", &allMine);
		if(allMine < 2 || allMine > n-3)
			break;
		allTime = allMine + 2;	/* 最多扫雷次数=地雷总数+2	*/
		tryTime = 0;
		laymine(mine, n, allMine);
		while(allMine > 0 && tryTime < allTime)
		{
			printf("现有%d个地雷. ", allMine);
			printf("你还有%d次机会. ", allTime-tryTime);
			sweepmine(mine, n, &allMine);
			++tryTime;
		}
		prt(mine, n, allMine);
		allMine = n;
		printf("\n再来一次吗?\n");
	}
	printf("\n****欢迎下次再来尝试扫地雷游戏****\n\n");
	system("pause");
}
/*
****欢迎尝试扫地雷游戏****

你想布几个地雷?[2- 7个为有效,否则表示结束游戏]: 5
现有5个地雷. 你还有7次机会. 请扫雷[1-9]：1
现有4个地雷. 你还有6次机会. 请扫雷[1-9]：2
现有4个地雷. 你还有5次机会. 请扫雷[1-9]：3
现有3个地雷. 你还有4次机会. 请扫雷[1-9]：4
现有3个地雷. 你还有3次机会. 请扫雷[1-9]：5
现有3个地雷. 你还有2次机会. 请扫雷[1-9]：6
现有2个地雷. 你还有1次机会. 请扫雷[1-9]：7
扫雷结束。剩余1个地雷，分布为:  0  0  0  0  0  0  0  8  0  0

再来一次吗?
你想布几个地雷?[2- 7个为有效,否则表示结束游戏]: 0

****欢迎下次再来尝试扫地雷游戏****

请按任意键继续. . .
*/