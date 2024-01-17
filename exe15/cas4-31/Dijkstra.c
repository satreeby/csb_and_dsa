/*	File: Dijkstra.c
	【例4-31】最短路径算法	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define M 5
#define UNPATH 0	/* 未入最短路径	*/
#define PATHED 1	/* 已入最短路径	*/
#define EDGE struct edge
#define VTEX struct vertex
int n=0;
EDGE
{
	int len; 		/* 边的长度			*/
	VTEX *vs, *vt; 	/* 起点和终点指针	*/
	EDGE *next;		/* 下一条边			*/
};
VTEX
{
	char key[M];	/* 顶点名			*/
	int len;		/* 路径长度			*/
	int flag;		/* 获得路径的标志	*/
	EDGE *edge;	/* 以此顶点为终点的边	*/
	VTEX *next;		/* 下一个顶点		*/
};
EDGE *headE=NULL;	/* 边链表哨兵		*/
VTEX *headV=NULL;	/* 顶点链表哨兵		*/
VTEX *source;		/* 最短路径的源点	*/
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
			return(prev->next);
	if((vertex = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		error("no space");
	strcpy(vertex->key, key);
	vertex->len = -1;
	vertex->flag = UNPATH;
	vertex->edge = NULL;
	vertex->next = prev->next;
	prev->next = vertex;
	numVtex++;
	return(vertex);
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
void input()						/* 生成边链表的函数			*/
{
	char keyS[M], keyT[M];
	int len;
	EDGE *edge;
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
}
void prtPath(VTEX *vertex)			/* 递归输出最短路径的函数	*/
{
	if(vertex->edge == NULL)
		return;
	prtPath(vertex->edge->vs);
	printf("%s->", vertex->edge->vs->key);
}
void prt(char *title)				/* 输出最短路径的函数		*/
{
	VTEX *vertex;
	printf("%s: \n", title);
	for(vertex=headV->next; vertex; vertex=vertex->next)
	{
		if(vertex->edge != NULL)
		{
			printf("Vertex=%2s len=%2d path=", vertex->key, vertex->len);
			prtPath(vertex);
			printf("%s\n", vertex->key);
		}
		else
			printf("Vertex=%2s source vertex\n", vertex->key);
	}
}
void getSource()					/* 获取源点的函数		*/
{
	VTEX *prev;
	char keyS[M];
	printf("顶点: ");
	for(prev=headV->next; prev; prev=prev->next)
		printf("%s ", prev->key);
	printf("\n");
	printf("请选择源点: ");
	scanf("%s", keyS);
	for(prev=headV; prev->next; prev=prev->next)
		if(strcmp(keyS, prev->next->key) == 0)
			break;
	if(prev->next == NULL)
		error("cannot found source vertex");
	source = prev->next;
	source->flag = PATHED;
	source->len = 0;
}
void shortPath()					/* 求取最短路径的函数	*/
{
	int vsPathed, vtPathed;
	EDGE *edge;
	VTEX *vertex;
	for(edge=headE->next; edge; edge=edge->next)
	{
		vsPathed = edge->vs->flag;
		vtPathed = edge->vt->flag;
		if(vsPathed == vtPathed)	/* vs和vt同在U或同在P	*/
			continue; 
		if(vsPathed < vtPathed)		/* vs在U中，vt在P中		*/
		{							/* 互换vs和vt			*/
			vertex = edge->vt;
			edge->vt = edge->vs;
			edge->vs = vertex;
		}
		edge->vt->edge = edge;		/* 链接vs到vt			*/
		edge->vt->len =	edge->vs->len + edge->len;	/* 计算路径长度 */
		edge->vt->flag = PATHED;	/* vt从U移入P			*/
		numPath++;					/* 最短路径数递增		*/
		break;
	}
}
void relax()						/* 松弛操作的函数		*/
{
	EDGE *edge;
	VTEX *vertex;
	int nRelax;						/* 发生松弛的次数		*/
	int len, vsPath, vtPath;
	do
	{
		nRelax = 0;
		for(edge=headE->next; edge; edge=edge->next)
		{
			len = edge->len;
			vsPath = edge->vs->len;
			vtPath = edge->vt->len;
			if(vsPath > vtPath + len)
			{								/* 交换vs和vt	*/
				vertex = edge->vt;
				edge->vt = edge->vs;
				edge->vs = vertex;
			}
			if(vtPath > vsPath + len)
			{
				edge->vt->edge = edge;		/* 更换vt所在边	*/
				edge->vt->len = edge->len + edge->vs->len;	/* 更新最短路径	*/
				nRelax++;
				//printf("%s->%s ",edge->vs->key,edge->vt->key);
			}
		}
		//n++;
		//printf("%d\n",nRelax);
	}
	while(nRelax > 0) ;						/* 直至无松弛为止	*/
	//printf("%d\n",n);
}
int main()
{
	input();						/* 调用生成边链表的函数		*/
	getSource();					/* 调用获取源点的函数		*/
	while(numPath < numVtex - 1)
		shortPath();				/* 调用生成最短路径的函数	*/
	prt("松弛前的最短路径");		/* 调用打印最短路径的函数	*/
	relax();						/* 调用松弛操作的函数		*/
	prt("松弛后的最短路径");		/* 调用打印最短路径的函数	*/
	system("pause");
}
/*
请输入文件名: Dijkstra1.txt
顶点: a b d c e f h
请选择源点: a
松弛前的最短路径:
Vertex= a source vertex
Vertex= b len= 7 path=a->b
Vertex= d len= 5 path=a->d
Vertex= c len=19 path=a->b->e->c
Vertex= e len=14 path=a->b->e
Vertex= f len=11 path=a->d->f
Vertex= h len=23 path=a->b->e->h
松弛后的最短路径:
Vertex= a source vertex
Vertex= b len= 7 path=a->b
Vertex= d len= 5 path=a->d
Vertex= c len=15 path=a->b->c
Vertex= e len=14 path=a->b->e
Vertex= f len=11 path=a->d->f
Vertex= h len=22 path=a->d->f->h

请输入文件名: Dijkstra2.txt
顶点: 12 15 13 10 11 14
请选择源点: 10
松弛前的最短路径:
Vertex=12 len=10 path=10->11->13->14->15->12
Vertex=15 len= 9 path=10->11->13->14->15
Vertex=13 len= 3 path=10->11->13
Vertex=10 source vertex
Vertex=11 len= 1 path=10->11
Vertex=14 len= 6 path=10->11->13->14
松弛后的最短路径:
Vertex=12 len= 8 path=10->11->13->12
Vertex=15 len= 7 path=10->14->15
Vertex=13 len= 3 path=10->11->13
Vertex=10 source vertex
Vertex=11 len= 1 path=10->11
Vertex=14 len= 4 path=10->14

请输入文件名: Dijkstra3.txt
顶点: A B C F D E
请选择源点: A
松弛前的最短路径:
Vertex= A source vertex
Vertex= B len= 7 path=A->B
Vertex= C len= 9 path=A->C
Vertex= F len=11 path=A->C->F
Vertex= D len=26 path=A->C->F->E->D
Vertex= E len=20 path=A->C->F->E
松弛后的最短路径:
Vertex= A source vertex
Vertex= B len= 7 path=A->B
Vertex= C len= 9 path=A->C
Vertex= F len=11 path=A->C->F
Vertex= D len=20 path=A->C->D
Vertex= E len=20 path=A->C->F->E

请输入文件名: Dijkstra4.txt
顶点: v0 v1 v4 v2 v3 v6 v5
请选择源点: v0
松弛前的最短路径:
Vertex=v0 source vertex
Vertex=v1 len=34 path=v0->v4->v5->v6->v2->v1
Vertex=v4 len= 1 path=v0->v4
Vertex=v2 len=28 path=v0->v4->v5->v6->v2
Vertex=v3 len=38 path=v0->v4->v5->v6->v2->v1->v3
Vertex=v6 len=26 path=v0->v4->v5->v6
Vertex=v5 len=16 path=v0->v4->v5
松弛后的最短路径:
Vertex=v0 source vertex
Vertex=v1 len=20 path=v0->v1
Vertex=v4 len= 1 path=v0->v4
Vertex=v2 len=26 path=v0->v1->v2
Vertex=v3 len=24 path=v0->v1->v3
Vertex=v6 len=26 path=v0->v4->v5->v6
Vertex=v5 len=16 path=v0->v4->v5

请输入文件名: Dijkstra5.txt
顶点: a b c d e h
请选择源点: a
松弛前的最短路径:
Vertex= a source vertex
Vertex= b len= 1 path=a->b
Vertex= c len= 3 path=a->b->c
Vertex= d len= 7 path=a->b->c->e->d
Vertex= e len= 4 path=a->b->c->e
Vertex= h len= 9 path=a->b->c->e->d->h
松弛后的最短路径:
Vertex= a source vertex
Vertex= b len= 1 path=a->b
Vertex= c len= 3 path=a->b->c
Vertex= d len= 7 path=a->b->c->e->d
Vertex= e len= 4 path=a->b->c->e
Vertex= h len= 9 path=a->b->c->e->d->h

输入哪个文件: Dijkstra6.txt
顶点: v0 v1 v3 v4 v2
请选择源点: v0
松弛前的最短路径:
Vertex=v0 source vertex
Vertex=v1 len=10 path=v0->v1
Vertex=v3 len=20 path=v0->v1->v3
Vertex=v4 len=50 path=v0->v1->v3->v2->v4
Vertex=v2 len=40 path=v0->v1->v3->v2
松弛后的最短路径:
Vertex=v0 source vertex
Vertex=v1 len=10 path=v0->v1
Vertex=v3 len=20 path=v0->v1->v3
Vertex=v4 len=50 path=v0->v1->v3->v2->v4
Vertex=v2 len=40 path=v0->v1->v3->v2
*/
