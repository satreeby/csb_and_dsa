/*	File: 顺序线性表.c
	【习题4-41】顺序存储线性表综合程序	*/


#include <stdio.h>
#include <stdlib.h>
#define M 100
void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
void createListS(int a[], int *n)
{
	FILE *fp;
	int  num;
	if((fp = fopen("inList.txt", "r")) == NULL)
		error("无法打开文件inList.txt");
	*n = 0;
	while(fscanf(fp, "%d", &num) == 1)
		a[(*n)++] = num;
}
int searchS(int a[], int n, int key) 	/* 查找函数		*/
{
	int i;
	for(i=0; i<n; i++)
		if(a[i] == key)
			return(i); 	/* 查找成功	*/
	return(-1);			/* 查找失败	*/
}
void addNodeS(int a[], int *n, int here, int key)
{
	int i, j;
	if((i = searchS(a, *n, here)) == -1)
	{
		printf("无法找到当前结点\n");
		return;
	}
	for(j=(*n)-1; j>=i; j--)			/* 向表尾移动	*/
		a[j+1] = a[j];
	a[i] = key;							/* 添加新结点	*/
	(*n)++;								/* 结点数加1	*/
}
void  deleteNodeS(int a[], int *n, int key)
{
	int i, k;
	if((i = searchS(a, *n, key)) == -1)
	{
		printf("无法找到待删除结点\n");
		return;
	}
	for(k=i+1; k<(*n); k++)
		a[k-1] = a[k]; /*向前移动*/
	(*n)--;
}
void prtListS(int a[], int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("a[%d]=%d ", i, a[i]);
	printf("\n");
}

void ExitTask(void)
{
	printf("再见！\n");
	system("pause");
	exit(0);
}
void main()
{
	int a[M], n, i, here, key;
	short MenuItem, nItem;
	char *MenuTitle[] = { "[1] 查找结点", 
						  "[2] 插入结点",
						  "[3] 删除结点",
						  "[4] 遍历线性表",
						  "[其他] 结束"};
	printf("## 顺序存储线性表综合程序 ##\n");
	printf("根据inList.txt创建线性表\n");
	createListS(a, &n);
	prtListS(a, n);
	while(1)
	{
		printf("\n");
		for(nItem=0; nItem<5; nItem++)			/* 输出菜单选项		*/
			printf("%s\n", MenuTitle[nItem]);
		printf("请选择：");
		scanf("%d", &MenuItem);					/* 输入命令选择		*/
		if(MenuItem == 1)						/* [1] 查找结点		*/
		{
			printf("查找哪个结点? key = ");
			scanf("%d", &key);
			if((i = searchS(a, n, key)) == -1)
				printf("查找失败\n");
			else
				printf("a[%d] = %d\n", i, key);
		}
		else if(MenuItem == 2)					/* [2] 插入结点		*/
		{ 
			printf("插入结点值? key = ");
			scanf("%d", &key);
			printf("插在哪个结点之前? here = ");
			scanf("%d", &here);
			addNodeS(a, &n, here, key);
		}
		else if(MenuItem == 3)					/* [3] 删除结点		*/
		{
			printf("删除哪个结点? key = ");
			scanf("%d", &key);
			deleteNodeS(a, &n, key);
		}
		else if(MenuItem == 4)					/* [4] 遍历线性表	*/
			prtListS(a, n);
		else
			error("再见！");
	}
}
