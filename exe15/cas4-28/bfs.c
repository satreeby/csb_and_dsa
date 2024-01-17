/*	File: bfs.c
	[��4-28] �������������(Breadth First Search)	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define UNVISITED	0
#define VISITED		1
#define VTEX struct vertex
#define EDGE struct edge
#define Q struct queue
VTEX
{
	char		key[10];	/* �ַ�������	*/
	int			flag;		/* ���ʱ��		*/
	EDGE		*edge;		/* ������ָ��	*/
	VTEX		*next;		/* ��һ����ָ��	*/
};
EDGE
{
	VTEX		*vertex;	/* ����ָ��		*/
	EDGE		*next;		/* ����ָ��		*/
};
Q
{
	VTEX		*vertex;
	Q *next;
};
VTEX *Vertex;
Q *Head = NULL, *Tail = NULL;	/* ����ָ��	*/
void error(char *error_msg)
{
	printf("**** %s ****\n", error_msg);
	exit(0);
}
void enQueue(VTEX *vertex)		/* ���Ӷ��н��Ӻ���	*/
{
	Q *node;
	node = (Q *)malloc(sizeof(Q));			/* ��̬������		*/
	if(node == NULL) 						/* �����			*/
		error("overflow!");
	if(Tail != NULL)						/* ����ָ�룺��������	*/
		Tail = Tail->next = node;
	else									/* ����ָ�룺�նӽ���	*/
		Tail = Head = node;
	Tail->vertex = vertex;					/* ���ӣ���β������	*/
	Tail->next = NULL;
}
VTEX *deQueue(void)			/* ���Ӷ��г��Ӻ���	*/
{
	VTEX *vertex;
	if(Head == NULL)
		return(NULL); 		/* �����			*/
	vertex = Head->vertex;	/* ȡ�����׽��		*/
	Head = Head->next;
	if(Head == NULL)		/* ���ղ���			*/
		Tail = NULL;
	return(vertex); 
}
VTEX *getVertex(char *key)
{
	VTEX *prev, *vertex;
	for(prev=Vertex; prev->next; prev=prev->next)
		if(strcmp(prev->next->key, key) == 0)
			return(prev->next);
	if((vertex = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		exit(0);
	strcpy(vertex->key, key);
	vertex->flag = UNVISITED;
	vertex->edge = NULL;
	vertex->next = prev->next;
	prev->next = vertex;
	return(vertex);
}
void input()
{
	VTEX *vtex;
	EDGE *edge;
	char keyS[10], keyT[10];
	FILE *fp;
	char filename[60];
	printf("�����ĸ��ļ�: ");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
		exit(0);
	if((Vertex = (VTEX *)malloc(sizeof(VTEX))) == NULL)
		exit(0);
	Vertex->next = NULL;
	while(fscanf(fp, "%s%s", keyS, keyT) == 2)
	{
		if((edge = (EDGE *)malloc(sizeof(EDGE))) == NULL)
			exit(0);
		vtex = getVertex(keyS);
		edge->vertex = getVertex(keyT);
		edge->next = vtex->edge;
		vtex->edge = edge;
	}
	printf("�ڽӱ�: \n");
	for(vtex=Vertex->next; vtex; vtex=vtex->next)
	{
		printf("%2s: ", vtex->key);
		for(edge=vtex->edge; edge; edge=edge->next)
			printf("%2s ", edge->vertex->key);
		printf("\n");
	}
}
void bfs(VTEX *vertex) 								/* BFS��������			*/
{
	EDGE *edge;
	enQueue(vertex); 								/* vertex����			*/
	while( vertex = deQueue() ) 					/* ֻҪ�ӷǿ�			*/
	{
		if(vertex->flag == UNVISITED)				/* ���vertexδ����		*/
		{
			printf("%s ", vertex->key);				/* ��ӡ����				*/
			vertex->flag = VISITED;					/* ���vertex			*/
			for(edge=vertex->edge; edge; edge=edge->next)
				if(edge->vertex->flag == UNVISITED)
					enQueue(edge->vertex);			/* δ�����ڽӶ������	*/
		}
	}
}
int main()
{
	input();
	printf("bfs:\n");
	bfs(Vertex->next);
	printf("\n");
	system("pause");
}
/*
�����ĸ��ļ�: G1.txt
�ڽӱ�:
 1:  2  3  6
 6:  1  4  5
 3:  1  4
 2:  1  4  5
 5:  2  4  6
 4:  2  3  5  6
bfs:
1 2 3 6 4 5

�������ļ���: G2.txt
�ڽӱ�:
 a:  b  d
 d:  a  b  e  f
 b:  a  c  d  e
 e:  b  c  d  f  h
 c:  b  e
 f:  d  e  h
 h:  e  f
bfs:
a b d c e f h
*/
