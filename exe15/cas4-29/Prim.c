/*	File: Prim.c
	[��4-29] ��С�����������㷨Prim	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define M 5
#define UNMST 0		/* δ��MST			*/
#define INMST 1		/* ����MST			*/
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
	int flag;		/* MST��־			*/
	EDGE *edge;	  /* �Դ˶���Ϊ�յ�ı�	*/
	VTEX *next;		/* ��һ������		*/
};
EDGE *headE=NULL;	/* �������ڱ�		*/
VTEX *headV=NULL;	/* ���������ڱ�		*/
int numEdge=0;		/* MST�еı���		*/
int numVtex=0;		/* ������			*/
void error(char *error_msg)
{
	printf("**** %s ****\n", error_msg);
	system("pause");
	exit(0);
}
VTEX *makeVertex(char *key)			/* ��ȡ�����ַ�ĺ���		*/
{
	VTEX *prev, *vertex;
	for(prev=headV; prev->next; prev=prev->next)
		if(strcmp(prev->next->key, key) == 0)
			return(prev->next);		/* �����Ѵ��ڣ����ض����ַ	*/
	if((vertex = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		error("no space");			/* ���㲻���ڣ����䶥��ռ�	*/
	strcpy(vertex->key, key);		/* ��������ֵ				*/
	vertex->flag = UNMST; 			/* ��ʼΪδ��MST			*/
	vertex->edge = NULL; 			/* ���ӱ߳�ʼΪ��			*/
	vertex->next = prev->next; 		/* ���붥��					*/
	prev->next = vertex;
	numVtex++;						/* ����������				*/
	return(vertex); 				/* ���ض����ַ				*/
}
void insertEdge(EDGE *edge)			/* �ڱ������в���ߵĺ���	*/
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
/*	printf("����: ");
	for(prev=headV->next; prev; prev=prev->next)
		printf("%s ", prev->key);
	printf("\n");
*/
	printf("������:\n");
	for(edge=headE->next; edge; edge=edge->next)
		printf("%2s %2s %2d\n", edge->vs->key, 
				edge->vt->key, edge->len);
}
void prt()							/* �����С�������ĺ���		*/
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
void makeMST()						/* ������С�������ĺ���		*/
{
	int vsMST, vtMST;
	EDGE *edge;
	VTEX *vertex;
	for(edge=headE->next; edge; edge=edge->next)
	{								/* ����������				*/
		vsMST = edge->vs->flag;
		vtMST = edge->vt->flag;
		if(vsMST == vtMST)			/* vs��vtͬ��U��S��			*/
			continue;	/* vsMST=vtMST==UNMST(=0)��INMST(=1)	*/
		if(vsMST < vtMST)			/* vs��U�У�vt��S��			*/
		{	/* vsMST == UNMST(=0) && vtMST == INMST(=1)			*/
			vertex = edge->vt;		/* ����edge�е�vs��vt		*/
			edge->vt = edge->vs;
			edge->vs = vertex;
		}
		edge->vt->edge = edge;	/* ����edge��vt��(vs,vt)����MST	*/
		edge->vt->flag = INMST;		/* ���MST��vt����S			*/
		numEdge++;					/* ����MST�ı�������		*/
		break;
	}
}
int main()
{
	input();						/* �������ɱ�����ĺ���		*/
	headE->next->vs->flag = INMST;	/* ���ø����				*/
	while(numEdge < numVtex - 1)
		makeMST();					/* ��������MST�ĺ���		*/
	prt();							/* ���MST�ĺ���			*/
	system("pause");
}
/*
�������ļ���: MST1.txt
������:
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
��С������:
a:      root of MST
a-b     lenght= 7
a-d     lenght= 5
e-c     lenght= 5
b-e     lenght= 7
d-f     lenght= 6
e-h     lenght= 9
�ܱ߳���39

�������ļ���: MST2.txt
������:
v4 v0  1
v2 v6  2
v1 v3  4
v1 v2  6
v6 v3  8
v4 v5  9
v5 v6 10
v3 v5 12
v0 v1 20
��С������:
v4-v0   lenght= 1
v2-v1   lenght= 6
v4:     root of MST
v6-v2   lenght= 2
v1-v3   lenght= 4
v5-v6   lenght=10
v4-v5   lenght= 9
�ܱ߳���32

�������ļ���: MST3.txt
������:
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
��С������:
v1:     root of MST
v1-v3   lenght= 1
v6-v4   lenght= 2
v3-v6   lenght= 4
v3-v2   lenght= 5
v2-v5   lenght= 3
�ܱ߳���15

�������ļ���: MST4.txt
������:
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
��С������:
F-B     lenght= 7
B-A     lenght=12
E-G     lenght= 8
E-F     lenght= 2
D-C     lenght= 3
E-D     lenght= 4
E:      root of MST
�ܱ߳���36

�������ļ���: MST5.txt
������:
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
��С������:
k-a     lenght=50
c-b     lenght=45
e-k     lenght=40
h-c     lenght=42
d-h     lenght=30
h-e     lenght=50
d:      root of MST
�ܱ߳���257

�����ĸ��ļ�: MST6.txt
������:
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
��С������:
v2-v1   lenght=10
v2:     root of MST
v4-v5   lenght=18
v2-v6   lenght=11
v2-v3   lenght= 5
v3-v4   lenght= 6
�ܱ߳���50
*/