/*	File: Prim.c
	[例4-29] 最小生成树生成算法Prim	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define M 5
#define UNMST 0		/* 未入MST			*/
#define INMST 1		/* 已入MST			*/
#define EDGE struct edge
#define VTEX struct vertex
EDGE
{
	int len; 		/* 边的长度			*/
	VTEX *vs, *vt; 	/* 起点和终点指针	*/
	EDGE *next;		/* 下一条边			*/
};
VTEX
{
	char key[M];	/* 顶点名			*/
	int flag;		/* MST标志			*/
	EDGE *edge;	  /* 以此顶点为终点的边	*/
	VTEX *next;		/* 下一个顶点		*/
};
EDGE *headE=NULL;	/* 边链表哨兵		*/
VTEX *headV=NULL;	/* 顶点链表哨兵		*/
int numEdge=0;		/* MST中的边数		*/
int numVtex=0;		/* 顶点数			*/
void error(char *error_msg)
{
	printf("**** %s ****\n", error_msg);
	system("pause");
	exit(0);
}
VTEX *makeVertex(char *key)			/* 获取顶点地址的函数		*/
{
	VTEX *prev, *vertex;
	for(prev=headV; prev->next; prev=prev->next)
		if(strcmp(prev->next->key, key) == 0)
			return(prev->next);		/* 顶点已存在，返回顶点地址	*/
	if((vertex = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		error("no space");			/* 顶点不存在，分配顶点空间	*/
	strcpy(vertex->key, key);		/* 顶点名赋值				*/
	vertex->flag = UNMST; 			/* 初始为未入MST			*/
	vertex->edge = NULL; 			/* 链接边初始为空			*/
	vertex->next = prev->next; 		/* 插入顶点					*/
	prev->next = vertex;
	numVtex++;						/* 顶点数递增				*/
	return(vertex); 				/* 返回顶点地址				*/
}
void insertEdge(EDGE *edge)			/* 在边链表中插入边的函数	*/
{
	EDGE *prev;
	for(prev=headE; prev->next; prev=prev->next)
		if(edge->len < prev->next->len)
			break;
	edge->next = prev->next;
	prev->next = edge;
}
void input()						/* 输入并生成边链表的函数	*/
{
	char keyS[M], keyT[M];
	int len;
	EDGE *edge;	
	VTEX *prev;
	FILE *fp;
	char filename[60];
	printf("输入哪个文件: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		error("no space");
	if((headE = (EDGE *)malloc(sizeof(EDGE))) == NULL)
		error("no space");
	headE->next = NULL;
	if((headV = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		error("no space");
	headV->next = NULL;
	while(fscanf(fp, "%s%s%d", keyS, keyT, &len) == 3)
	{
		if((edge = (EDGE *)malloc(sizeof(EDGE))) == NULL)
			error("no space");
		edge->vs = (makeVertex(keyS));
		edge->vt = (makeVertex(keyT));
		edge->len = len;
		insertEdge(edge);
	}
/*	printf("顶点: ");
	for(prev=headV->next; prev; prev=prev->next)
		printf("%s ", prev->key);
	printf("\n");
*/
	printf("边链表:\n");
	for(edge=headE->next; edge; edge=edge->next)
		printf("%2s %2s %2d\n", edge->vs->key, 
				edge->vt->key, edge->len);
}
void prt()							/* 输出最小生成树的函数		*/
{
	int len=0;
	VTEX *vertex;
	printf("最小生成树: \n");
	for(vertex=headV->next; vertex; vertex=vertex->next)
	{
		if(vertex->edge != NULL)
		{
			len += vertex->edge->len;
			printf("%s-%s", vertex->edge->vs->key, vertex->key);
			printf("\tlenght=%2d\n", vertex->edge->len);
		}
		else
			printf("%s:\troot of MST\n", vertex->key);
	}
	printf("总边长: %d\n", len);
}
void makeMST()						/* 生成最小生成树的函数		*/
{
	int vsMST, vtMST;
	EDGE *edge;
	VTEX *vertex;
	for(edge=headE->next; edge; edge=edge->next)
	{								/* 遍历边链表				*/
		vsMST = edge->vs->flag;
		vtMST = edge->vt->flag;
		if(vsMST == vtMST)			/* vs和vt同在U或S中			*/
			continue;	/* vsMST=vtMST==UNMST(=0)或INMST(=1)	*/
		if(vsMST < vtMST)			/* vs在U中，vt在S中			*/
		{	/* vsMST == UNMST(=0) && vtMST == INMST(=1)			*/
			vertex = edge->vt;		/* 交换edge中的vs和vt		*/
			edge->vt = edge->vs;
			edge->vs = vertex;
		}
		edge->vt->edge = edge;	/* 连接edge到vt，(vs,vt)接入MST	*/
		edge->vt->flag = INMST;		/* 标记MST，vt移入S			*/
		numEdge++;					/* 已入MST的边数递增		*/
		break;
	}
}
int main()
{
	input();						/* 调用生成边链表的函数		*/
	headE->next->vs->flag = INMST;	/* 设置根结点				*/
	while(numEdge < numVtex - 1)
		makeMST();					/* 调用生成MST的函数		*/
	prt();							/* 输出MST的函数			*/
	system("pause");
}
/*
请输入文件名: MST1.txt
边链表:
 a  d  5
 c  e  5
 f  d  6
 a  b  7
 e  b  7
 b  c  8
 f  e  8
 b  d  9
 e  h  9
 h  f 11
 d  e 15
最小生成树:
a:      root of MST
a-b     lenght= 7
a-d     lenght= 5
e-c     lenght= 5
b-e     lenght= 7
d-f     lenght= 6
e-h     lenght= 9
总边长：39

请输入文件名: MST2.txt
边链表:
v4 v0  1
v2 v6  2
v1 v3  4
v1 v2  6
v6 v3  8
v4 v5  9
v5 v6 10
v3 v5 12
v0 v1 20
最小生成树:
v4-v0   lenght= 1
v2-v1   lenght= 6
v4:     root of MST
v6-v2   lenght= 2
v1-v3   lenght= 4
v5-v6   lenght=10
v4-v5   lenght= 9
总边长：32

请输入文件名: MST3.txt
边链表:
v1 v3  1
v4 v6  2
v2 v5  3
v3 v6  4
v1 v4  5
v3 v4  5
v2 v3  5
v3 v5  6
v1 v2  6
v5 v6  6
最小生成树:
v1:     root of MST
v1-v3   lenght= 1
v6-v4   lenght= 2
v3-v6   lenght= 4
v3-v2   lenght= 5
v2-v5   lenght= 3
总边长：15

请输入文件名: MST4.txt
边链表:
 E  F  2
 D  C  3
 D  E  4
 C  E  5
 C  F  6
 F  B  7
 E  G  8
 G  F  9
 B  C 10
 B  A 12
 A  G 14
 A  F 16
最小生成树:
F-B     lenght= 7
B-A     lenght=12
E-G     lenght= 8
E-F     lenght= 2
D-C     lenght= 3
E-D     lenght= 4
E:      root of MST
总边长：36

请输入文件名: MST5.txt
边链表:
 d  h 30
 e  k 40
 c  h 42
 c  b 45
 a  k 50
 e  h 50
 b  h 52
 a  b 60
 k  h 65
 d  e 70
最小生成树:
k-a     lenght=50
c-b     lenght=45
e-k     lenght=40
h-c     lenght=42
d-h     lenght=30
h-e     lenght=50
d:      root of MST
总边长：257

输入哪个文件: MST6.txt
边链表:
v2 v3  5
v3 v4  6
v2 v4  6
v1 v2 10
v2 v6 11
v4 v6 14
v4 v5 18
v1 v5 19
v1 v6 21
v5 v6 33
最小生成树:
v2-v1   lenght=10
v2:     root of MST
v4-v5   lenght=18
v2-v6   lenght=11
v2-v3   lenght= 5
v3-v4   lenght= 6
总边长：50
*/