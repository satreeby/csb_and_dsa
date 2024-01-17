/*	File: 无哨兵链表.c
	【习题4-42】无哨兵链表综合程序
	相关文件：addNodeL.c	*/

#include <stdio.h>
#include <stdlib.h>
#define NODE struct node

NODE
{
	int num;
	NODE  *next; 
};


void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
NODE *createListL(NODE *first)
{
	FILE *fp;
	NODE *node;
	int  num; 
	if((fp = fopen("inList.txt", "r")) == NULL)
		error("无法打开文件inList.txt");
	while(fscanf(fp, "%d", &num) == 1)
	{
		if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
			error("内存分配失败");
		node->num = num;
		node->next = first;
		first = node;
	}
	return(first);
}
NODE *searchL(NODE *first, int key)
{
	NODE *node;
	for(node=first; node; node=node->next)
		if(node->num == key)
			return(node); 		/* 查找成功		*/
	return(NULL);				/* 查找失败		*/
}
NODE *deleteNodeL(NODE *first, int key)
{
	NODE *prev, *node;
	if(first == NULL)
		return(first);
	if(first->num == key)
	{
		node = first;
		first = node->next;
		free(node);
		return(first);
	}
	for(prev=first; prev->next; prev=prev->next)
	{
		if(prev->next->num == key)
		{
			node = prev->next;	
			prev->next = node->next;	
			free(node);
			return(first);
		}
	}
	printf("待删除结点不存在\n");
	return(first);
}

NODE *addNodeL(NODE *first, int here, int key)
{
	NODE *prev, *node;
	/* 补齐以下程序		*/
	if (first == NULL)
	{
		printf("无法确定插入位置\n");
		return(first);
	}
	if(first->num == here)
	{
		if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
			error("内存分配失败"); 
		node->num = key;	
		node->next = first;	
		return(node);
	}
	for(prev=first; prev->next; prev=prev->next)
	{
		if(prev->next->num == here)
		{
			if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
				error("内存分配失败"); 
			node->num = key;	
			node->next = prev->next;	
			prev->next = node;	
			return(first);
		}
	}
	printf("无法确定插入位置\n");
	return(first);

}

void prtListL(NODE *first)
{
	NODE *node;
	for(node=first; node; node=node->next)
		printf("%d ", node->num);
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
	NODE *First=NULL, *Tail=NULL, *node;
	int key, here;
	short MenuItem, nItem;
	char *MenuTitle[] = { "[1] 查找结点", 
						  "[2] 插入结点",
						  "[3] 删除结点",
						  "[4] 遍历线性表",
						  "[其他] 结束"};
	printf("## 无哨兵链表综合程序 ##\n");
	printf("根据inList.txt创建链表\n");
	First = createListL(First);
	prtListL(First);
	while(1)
	{
		printf("\n");
		for(nItem=0; nItem<5; nItem++)			/* 输出菜单选项		*/
			printf("%s\n", MenuTitle[nItem]);
		printf("请选择：");
		scanf("%d", &MenuItem);					/* 输入命令选择		*/
		if(MenuItem == 1)						/* [1] 查找结点		*/
		{
			printf("插入结点值? key = ");
			scanf("%d", &key);
			if((node = searchL(First, key)) == NULL)
				printf("查找失败\n");
			else
				printf("node = %d\n", node->num);
		}
		else if(MenuItem == 2)					/* [2] 插入结点		*/
		{ 
			printf("插入结点值? key = ");
			scanf("%d", &key);
			printf("插在哪个结点之前? here = ");
			scanf("%d", &here);
			First = addNodeL(First, here, key);
		}
		else if(MenuItem == 3)					/* [3] 删除结点		*/
		{
			printf("删除哪个结点? key = ");
			scanf("%d", &key);
			First = deleteNodeL(First, key);
		}
		else if(MenuItem == 4)					/* [4] 遍历线性表	*/
			prtListL(First);
		else
			error("再见！");
	}
}
