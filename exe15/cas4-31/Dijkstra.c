/*	File: Dijkstra.c
	����4-31�����·���㷨	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define M 5
#define UNPATH 0	/* δ�����·��	*/
#define PATHED 1	/* �������·��	*/
#define EDGE struct edge
#define VTEX struct vertex
int n=0;
EDGE
{
	int len; 		/* �ߵĳ���			*/
	VTEX *vs, *vt; 	/* �����յ�ָ��	*/
	EDGE *next;		/* ��һ����			*/
};
VTEX
{
	char key[M];	/* ������			*/
	int len;		/* ·������			*/
	int flag;		/* ���·���ı�־	*/
	EDGE *edge;	/* �Դ˶���Ϊ�յ�ı�	*/
	VTEX *next;		/* ��һ������		*/
};
EDGE *headE=NULL;	/* �������ڱ�		*/
VTEX *headV=NULL;	/* ���������ڱ�		*/
VTEX *source;		/* ���·����Դ��	*/
int numPath=0;		/* ���·���еı���	*/
int numVtex=0;		/* ������			*/
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
void input()						/* ���ɱ�����ĺ���			*/
{
	char keyS[M], keyT[M];
	int len;
	EDGE *edge;
	FILE *fp;
	char filename[60];
	printf("�����ĸ��ļ�: ");
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
void prtPath(VTEX *vertex)			/* �ݹ�������·���ĺ���	*/
{
	if(vertex->edge == NULL)
		return;
	prtPath(vertex->edge->vs);
	printf("%s->", vertex->edge->vs->key);
}
void prt(char *title)				/* ������·���ĺ���		*/
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
void getSource()					/* ��ȡԴ��ĺ���		*/
{
	VTEX *prev;
	char keyS[M];
	printf("����: ");
	for(prev=headV->next; prev; prev=prev->next)
		printf("%s ", prev->key);
	printf("\n");
	printf("��ѡ��Դ��: ");
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
void shortPath()					/* ��ȡ���·���ĺ���	*/
{
	int vsPathed, vtPathed;
	EDGE *edge;
	VTEX *vertex;
	for(edge=headE->next; edge; edge=edge->next)
	{
		vsPathed = edge->vs->flag;
		vtPathed = edge->vt->flag;
		if(vsPathed == vtPathed)	/* vs��vtͬ��U��ͬ��P	*/
			continue; 
		if(vsPathed < vtPathed)		/* vs��U�У�vt��P��		*/
		{							/* ����vs��vt			*/
			vertex = edge->vt;
			edge->vt = edge->vs;
			edge->vs = vertex;
		}
		edge->vt->edge = edge;		/* ����vs��vt			*/
		edge->vt->len =	edge->vs->len + edge->len;	/* ����·������ */
		edge->vt->flag = PATHED;	/* vt��U����P			*/
		numPath++;					/* ���·��������		*/
		break;
	}
}
void relax()						/* �ɳڲ����ĺ���		*/
{
	EDGE *edge;
	VTEX *vertex;
	int nRelax;						/* �����ɳڵĴ���		*/
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
			{								/* ����vs��vt	*/
				vertex = edge->vt;
				edge->vt = edge->vs;
				edge->vs = vertex;
			}
			if(vtPath > vsPath + len)
			{
				edge->vt->edge = edge;		/* ����vt���ڱ�	*/
				edge->vt->len = edge->len + edge->vs->len;	/* �������·��	*/
				nRelax++;
				//printf("%s->%s ",edge->vs->key,edge->vt->key);
			}
		}
		//n++;
		//printf("%d\n",nRelax);
	}
	while(nRelax > 0) ;						/* ֱ�����ɳ�Ϊֹ	*/
	//printf("%d\n",n);
}
int main()
{
	input();						/* �������ɱ�����ĺ���		*/
	getSource();					/* ���û�ȡԴ��ĺ���		*/
	while(numPath < numVtex - 1)
		shortPath();				/* �����������·���ĺ���	*/
	prt("�ɳ�ǰ�����·��");		/* ���ô�ӡ���·���ĺ���	*/
	relax();						/* �����ɳڲ����ĺ���		*/
	prt("�ɳں�����·��");		/* ���ô�ӡ���·���ĺ���	*/
	system("pause");
}
/*
�������ļ���: Dijkstra1.txt
����: a b d c e f h
��ѡ��Դ��: a
�ɳ�ǰ�����·��:
Vertex= a source vertex
Vertex= b len= 7 path=a->b
Vertex= d len= 5 path=a->d
Vertex= c len=19 path=a->b->e->c
Vertex= e len=14 path=a->b->e
Vertex= f len=11 path=a->d->f
Vertex= h len=23 path=a->b->e->h
�ɳں�����·��:
Vertex= a source vertex
Vertex= b len= 7 path=a->b
Vertex= d len= 5 path=a->d
Vertex= c len=15 path=a->b->c
Vertex= e len=14 path=a->b->e
Vertex= f len=11 path=a->d->f
Vertex= h len=22 path=a->d->f->h

�������ļ���: Dijkstra2.txt
����: 12 15 13 10 11 14
��ѡ��Դ��: 10
�ɳ�ǰ�����·��:
Vertex=12 len=10 path=10->11->13->14->15->12
Vertex=15 len= 9 path=10->11->13->14->15
Vertex=13 len= 3 path=10->11->13
Vertex=10 source vertex
Vertex=11 len= 1 path=10->11
Vertex=14 len= 6 path=10->11->13->14
�ɳں�����·��:
Vertex=12 len= 8 path=10->11->13->12
Vertex=15 len= 7 path=10->14->15
Vertex=13 len= 3 path=10->11->13
Vertex=10 source vertex
Vertex=11 len= 1 path=10->11
Vertex=14 len= 4 path=10->14

�������ļ���: Dijkstra3.txt
����: A B C F D E
��ѡ��Դ��: A
�ɳ�ǰ�����·��:
Vertex= A source vertex
Vertex= B len= 7 path=A->B
Vertex= C len= 9 path=A->C
Vertex= F len=11 path=A->C->F
Vertex= D len=26 path=A->C->F->E->D
Vertex= E len=20 path=A->C->F->E
�ɳں�����·��:
Vertex= A source vertex
Vertex= B len= 7 path=A->B
Vertex= C len= 9 path=A->C
Vertex= F len=11 path=A->C->F
Vertex= D len=20 path=A->C->D
Vertex= E len=20 path=A->C->F->E

�������ļ���: Dijkstra4.txt
����: v0 v1 v4 v2 v3 v6 v5
��ѡ��Դ��: v0
�ɳ�ǰ�����·��:
Vertex=v0 source vertex
Vertex=v1 len=34 path=v0->v4->v5->v6->v2->v1
Vertex=v4 len= 1 path=v0->v4
Vertex=v2 len=28 path=v0->v4->v5->v6->v2
Vertex=v3 len=38 path=v0->v4->v5->v6->v2->v1->v3
Vertex=v6 len=26 path=v0->v4->v5->v6
Vertex=v5 len=16 path=v0->v4->v5
�ɳں�����·��:
Vertex=v0 source vertex
Vertex=v1 len=20 path=v0->v1
Vertex=v4 len= 1 path=v0->v4
Vertex=v2 len=26 path=v0->v1->v2
Vertex=v3 len=24 path=v0->v1->v3
Vertex=v6 len=26 path=v0->v4->v5->v6
Vertex=v5 len=16 path=v0->v4->v5

�������ļ���: Dijkstra5.txt
����: a b c d e h
��ѡ��Դ��: a
�ɳ�ǰ�����·��:
Vertex= a source vertex
Vertex= b len= 1 path=a->b
Vertex= c len= 3 path=a->b->c
Vertex= d len= 7 path=a->b->c->e->d
Vertex= e len= 4 path=a->b->c->e
Vertex= h len= 9 path=a->b->c->e->d->h
�ɳں�����·��:
Vertex= a source vertex
Vertex= b len= 1 path=a->b
Vertex= c len= 3 path=a->b->c
Vertex= d len= 7 path=a->b->c->e->d
Vertex= e len= 4 path=a->b->c->e
Vertex= h len= 9 path=a->b->c->e->d->h

�����ĸ��ļ�: Dijkstra6.txt
����: v0 v1 v3 v4 v2
��ѡ��Դ��: v0
�ɳ�ǰ�����·��:
Vertex=v0 source vertex
Vertex=v1 len=10 path=v0->v1
Vertex=v3 len=20 path=v0->v1->v3
Vertex=v4 len=50 path=v0->v1->v3->v2->v4
Vertex=v2 len=40 path=v0->v1->v3->v2
�ɳں�����·��:
Vertex=v0 source vertex
Vertex=v1 len=10 path=v0->v1
Vertex=v3 len=20 path=v0->v1->v3
Vertex=v4 len=50 path=v0->v1->v3->v2->v4
Vertex=v2 len=40 path=v0->v1->v3->v2
*/
