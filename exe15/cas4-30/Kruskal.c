/*	File: Kruskal.c
	[例4-30] 最小生成树生成算法Kruskal	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define M 5
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
	EDGE *edge;	  /* 以此顶点为终点的边	*/
	VTEX *next;		/* 下一个顶点		*/
};
EDGE *headE=NULL;	/* 边链表哨兵指针	*/
VTEX *headV=NULL;	/* 顶点链表哨兵指针	*/
int numPath=0;		/* 最短路径中的边数	*/
int numVtex=0;		/* 顶点数			*/
void error(char *error_msg)
{
	printf("**** %s ****\n", error_msg);
	system("pause");
	exit(0);
}
VTEX *makeVertex(char *key)
{
	VTEX *prev, *vertex;
	for(prev=headV; prev->next; prev=prev->next)
		if(strcmp(prev->next->key, key) == 0)
			return(prev->next);		/* 顶点已存在，返回顶点地址	*/
	if((vertex = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		error("no space");					/* 顶点不存在，分配顶点空间	*/
	strcpy(vertex->key, key);		/* 顶点名赋值				*/
	vertex->edge = NULL; 			/* 链接边初始为空			*/
	vertex->next = prev->next; 		/* 插入顶点					*/
	prev->next = vertex;
	numVtex++;						/* 顶点数递增				*/
	return(vertex); 				/* 返回顶点地址				*/
}
void insertEdge(EDGE *edge)
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
	printf("顶点: ");
	for(prev=headV->next; prev; prev=prev->next)
		printf("%s ", prev->key);
	printf("\n");
}
void prt()
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
VTEX *getRoot(VTEX *vertex)		/* 获取顶点所在树根的函数	*/
{
	if(vertex->edge == NULL)
		return(vertex);
	return( getRoot(vertex->edge->vs) );
}
void revEdge(EDGE *edge)		/* 反转edge的函数			*/
{
	EDGE *vt_edge;
	VTEX *vt;
	if(edge == NULL)
		return;
	vt = edge->vs;			/* 交换vs和vt	*/
	edge->vs = edge->vt;
	edge->vt = vt;
/*	if debug
*/
		printf("revEdge=%2s: %2s %2s %2d\n", vt->key,
				edge->vs->key, 
				edge->vt->key, edge->len);
	vt_edge = vt->edge;			/* 保存当前边	*/
	vt->edge = edge;			/* 更新当前边	*/
	revEdge(vt_edge);			/* 反转当前边	*/
}
void makeMST()					/* 生成最小生成树的函数		*/
{
	EDGE *edge;
	VTEX *vs, *vt, *vsRoot, *vtRoot;
	for(edge=headE->next; edge; edge=edge->next)
	{
		vsRoot = getRoot(edge->vs);	/* 获取vs的树根	*/
		vtRoot = getRoot(edge->vt);	/* 获取vt的树根	*/
		if(vsRoot == vtRoot)
			continue;				/* vs和vt为同根生，不连接 */
		vt = edge->vt;
		vs = edge->vs;
		if(vs->edge == NULL && vt->edge != NULL)
		{							/* vs是根 && vt不是根	*/
			edge->vt = edge->vs;	/* 交换vs和vt			*/
			edge->vs = vt;
		}
		if(vs->edge != NULL && vt->edge != NULL)
		{							/* vs不是根 && vt不是根	*/
			revEdge(vt->edge);		/* 反转vt所在边			*/
			vt->edge = NULL;		/* vt按根赋初值			*/
		}
		/* 经过以上处理，保证vt是根。						*/
		edge->vt->edge = edge;		/* 连接vs和vt			*/
		printf("Edge=%2s %2s %2d\n", edge->vs->key,  
			edge->vt->key, edge->len);
		numPath++;					/* 选入MST的边数递增	*/
		if(numPath >= numVtex - 1)	/* 已合并为一棵树		*/
			return;
	}
}
int main()
{
	input();						/* 调用生成边链表的函数	*/
	makeMST();						/* 调用生成MST的函数	*/
	prt();							/* 输出MST的函数		*/
	system("pause");
}
/*
请输入文件名: MST1.txt
顶点: a b d c e f h
Edge= d  a  5
Edge= c  e  5
Edge= f  d  6
Edge= a  b  7
revEdge= a:  b  a  7
revEdge= d:  a  d  5
revEdge= f:  d  f  6
Edge= e  b  7
Edge= e  h  9
最小生成树:
b-a     lenght= 7
e-b     lenght= 7
a-d     lenght= 5
c:		root of MST
c-e     lenght= 5
d-f     lenght= 6
e-h     lenght= 9
总边长：39

请输入文件名: MST2.txt
顶点: v0 v1 v4 v2 v3 v6 v5
Edge=v4 v0  1
Edge=v2 v6  2
Edge=v1 v3  4
Edge=v1 v2  6
Edge=v4 v5  9
revEdge=v2: v6 v2  2
revEdge=v1: v2 v1  6
Edge=v5 v6 10
最小生成树:
v4-v0   lenght= 1
v2-v1   lenght= 6
v4:		root of MST
v6-v2   lenght= 2
v1-v3   lenght= 4
v5-v6   lenght=10
v4-v5   lenght= 9
总边长: 32

请输入文件名: MST3.txt
顶点: v1 v3 v4 v6 v2 v5
Edge=v1 v3  1
Edge=v4 v6  2
Edge=v2 v5  3
revEdge=v4: v6 v4  2
Edge=v3 v6  4
Edge=v3 v2  5
最小生成树:
v1:		root of MST
v1-v3   lenght= 1
v6-v4   lenght= 2
v3-v6   lenght= 4
v3-v2   lenght= 5
v2-v5   lenght= 3
总边长: 15

请输入文件名: MST4.txt
顶点: B A G F C D E
Edge= E  F  2
Edge= D  C  3
Edge= D  E  4
Edge= F  B  7
Edge= E  G  8
Edge= B  A 12
最小生成树:
F-B     lenght= 7
B-A     lenght=12
E-G     lenght= 8
E-F     lenght= 2
D-C     lenght= 3
D:		root of MST
D-E     lenght= 4
总边长：36

请输入文件名: MST5.txt
顶点: a b k c h e d
Edge= d  h 30
Edge= e  k 40
Edge= h  c 42
Edge= c  b 45
Edge= k  a 50
Edge= h  e 50
最小生成树:
k-a     lenght=50
c-b     lenght=45
e-k     lenght=40
h-c     lenght=42
d-h     lenght=30
h-e     lenght=50
d:		root of MST
总边长：257

输入哪个文件: MST6.txt
顶点: v1 v2 v5 v6 v3 v4
Edge=v2 v3  5
Edge=v3 v4  6
Edge=v1 v2 10
Edge=v2 v6 11
Edge=v4 v5 18
最小生成树:
v1:		root of MST
v1-v2   lenght=10
v4-v5   lenght=18
v2-v6   lenght=11
v2-v3   lenght= 5
v3-v4   lenght= 6
总边长：50

输入哪个文件: MST7.txt
顶点: v0 v2 v1 v3 v4 v7 v5 v6
Edge=v0 v2  1
Edge=v1 v3  2
Edge=v7 v1  2
Edge=v3 v5  3
Edge=v2 v4  4
Edge=v1 v6  4
revEdge=v3: v5 v3  3
revEdge=v1: v3 v1  2
revEdge=v7: v1 v7  2
Edge=v4 v5  7
最小生成树:
v0:     root of MST
v0-v2   lenght= 1
v3-v1   lenght= 2
v5-v3   lenght= 3
v2-v4   lenght= 4
v1-v7   lenght= 2
v4-v5   lenght= 7
v1-v6   lenght= 4
总边长: 23
*/