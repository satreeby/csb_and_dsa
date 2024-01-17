/*	File: Kruskal.c
	[��4-30] ��С�����������㷨Kruskal	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define M 5
#define EDGE struct edge
#define VTEX struct vertex
EDGE
{
	int len; 		/* �ߵĳ���			*/
	VTEX *vs, *vt; 	/* �����յ�ָ��	*/
	EDGE *next;		/* ��һ����			*/
};
VTEX
{
	char key[M];	/* ������			*/
	EDGE *edge;	  /* �Դ˶���Ϊ�յ�ı�	*/
	VTEX *next;		/* ��һ������		*/
};
EDGE *headE=NULL;	/* �������ڱ�ָ��	*/
VTEX *headV=NULL;	/* ���������ڱ�ָ��	*/
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
			return(prev->next);		/* �����Ѵ��ڣ����ض����ַ	*/
	if((vertex = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		error("no space");					/* ���㲻���ڣ����䶥��ռ�	*/
	strcpy(vertex->key, key);		/* ��������ֵ				*/
	vertex->edge = NULL; 			/* ���ӱ߳�ʼΪ��			*/
	vertex->next = prev->next; 		/* ���붥��					*/
	prev->next = vertex;
	numVtex++;						/* ����������				*/
	return(vertex); 				/* ���ض����ַ				*/
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
void input()						/* ���벢���ɱ�����ĺ���	*/
{
	char keyS[M], keyT[M];
	int len;
	EDGE *edge;	
	VTEX *prev;
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
	printf("����: ");
	for(prev=headV->next; prev; prev=prev->next)
		printf("%s ", prev->key);
	printf("\n");
}
void prt()
{
	int len=0;
	VTEX *vertex;
	printf("��С������: \n");
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
	printf("�ܱ߳�: %d\n", len);
}
VTEX *getRoot(VTEX *vertex)		/* ��ȡ�������������ĺ���	*/
{
	if(vertex->edge == NULL)
		return(vertex);
	return( getRoot(vertex->edge->vs) );
}
void revEdge(EDGE *edge)		/* ��תedge�ĺ���			*/
{
	EDGE *vt_edge;
	VTEX *vt;
	if(edge == NULL)
		return;
	vt = edge->vs;			/* ����vs��vt	*/
	edge->vs = edge->vt;
	edge->vt = vt;
/*	if debug
*/
		printf("revEdge=%2s: %2s %2s %2d\n", vt->key,
				edge->vs->key, 
				edge->vt->key, edge->len);
	vt_edge = vt->edge;			/* ���浱ǰ��	*/
	vt->edge = edge;			/* ���µ�ǰ��	*/
	revEdge(vt_edge);			/* ��ת��ǰ��	*/
}
void makeMST()					/* ������С�������ĺ���		*/
{
	EDGE *edge;
	VTEX *vs, *vt, *vsRoot, *vtRoot;
	for(edge=headE->next; edge; edge=edge->next)
	{
		vsRoot = getRoot(edge->vs);	/* ��ȡvs������	*/
		vtRoot = getRoot(edge->vt);	/* ��ȡvt������	*/
		if(vsRoot == vtRoot)
			continue;				/* vs��vtΪͬ������������ */
		vt = edge->vt;
		vs = edge->vs;
		if(vs->edge == NULL && vt->edge != NULL)
		{							/* vs�Ǹ� && vt���Ǹ�	*/
			edge->vt = edge->vs;	/* ����vs��vt			*/
			edge->vs = vt;
		}
		if(vs->edge != NULL && vt->edge != NULL)
		{							/* vs���Ǹ� && vt���Ǹ�	*/
			revEdge(vt->edge);		/* ��תvt���ڱ�			*/
			vt->edge = NULL;		/* vt��������ֵ			*/
		}
		/* �������ϴ�����֤vt�Ǹ���						*/
		edge->vt->edge = edge;		/* ����vs��vt			*/
		printf("Edge=%2s %2s %2d\n", edge->vs->key,  
			edge->vt->key, edge->len);
		numPath++;					/* ѡ��MST�ı�������	*/
		if(numPath >= numVtex - 1)	/* �Ѻϲ�Ϊһ����		*/
			return;
	}
}
int main()
{
	input();						/* �������ɱ�����ĺ���	*/
	makeMST();						/* ��������MST�ĺ���	*/
	prt();							/* ���MST�ĺ���		*/
	system("pause");
}
/*
�������ļ���: MST1.txt
����: a b d c e f h
Edge= d  a  5
Edge= c  e  5
Edge= f  d  6
Edge= a  b  7
revEdge= a:  b  a  7
revEdge= d:  a  d  5
revEdge= f:  d  f  6
Edge= e  b  7
Edge= e  h  9
��С������:
b-a     lenght= 7
e-b     lenght= 7
a-d     lenght= 5
c:		root of MST
c-e     lenght= 5
d-f     lenght= 6
e-h     lenght= 9
�ܱ߳���39

�������ļ���: MST2.txt
����: v0 v1 v4 v2 v3 v6 v5
Edge=v4 v0  1
Edge=v2 v6  2
Edge=v1 v3  4
Edge=v1 v2  6
Edge=v4 v5  9
revEdge=v2: v6 v2  2
revEdge=v1: v2 v1  6
Edge=v5 v6 10
��С������:
v4-v0   lenght= 1
v2-v1   lenght= 6
v4:		root of MST
v6-v2   lenght= 2
v1-v3   lenght= 4
v5-v6   lenght=10
v4-v5   lenght= 9
�ܱ߳�: 32

�������ļ���: MST3.txt
����: v1 v3 v4 v6 v2 v5
Edge=v1 v3  1
Edge=v4 v6  2
Edge=v2 v5  3
revEdge=v4: v6 v4  2
Edge=v3 v6  4
Edge=v3 v2  5
��С������:
v1:		root of MST
v1-v3   lenght= 1
v6-v4   lenght= 2
v3-v6   lenght= 4
v3-v2   lenght= 5
v2-v5   lenght= 3
�ܱ߳�: 15

�������ļ���: MST4.txt
����: B A G F C D E
Edge= E  F  2
Edge= D  C  3
Edge= D  E  4
Edge= F  B  7
Edge= E  G  8
Edge= B  A 12
��С������:
F-B     lenght= 7
B-A     lenght=12
E-G     lenght= 8
E-F     lenght= 2
D-C     lenght= 3
D:		root of MST
D-E     lenght= 4
�ܱ߳���36

�������ļ���: MST5.txt
����: a b k c h e d
Edge= d  h 30
Edge= e  k 40
Edge= h  c 42
Edge= c  b 45
Edge= k  a 50
Edge= h  e 50
��С������:
k-a     lenght=50
c-b     lenght=45
e-k     lenght=40
h-c     lenght=42
d-h     lenght=30
h-e     lenght=50
d:		root of MST
�ܱ߳���257

�����ĸ��ļ�: MST6.txt
����: v1 v2 v5 v6 v3 v4
Edge=v2 v3  5
Edge=v3 v4  6
Edge=v1 v2 10
Edge=v2 v6 11
Edge=v4 v5 18
��С������:
v1:		root of MST
v1-v2   lenght=10
v4-v5   lenght=18
v2-v6   lenght=11
v2-v3   lenght= 5
v3-v4   lenght= 6
�ܱ߳���50

�����ĸ��ļ�: MST7.txt
����: v0 v2 v1 v3 v4 v7 v5 v6
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
��С������:
v0:     root of MST
v0-v2   lenght= 1
v3-v1   lenght= 2
v5-v3   lenght= 3
v2-v4   lenght= 4
v1-v7   lenght= 2
v4-v5   lenght= 7
v1-v6   lenght= 4
�ܱ߳�: 23
*/