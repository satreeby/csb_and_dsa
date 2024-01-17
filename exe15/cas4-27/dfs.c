/*	File: dfs.c
	[��4-27] �������������(Depth First Search)	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define UNVISITED	0
#define VISITED		1
#define VTEX struct vertex
#define EDGE struct edge
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
VTEX *Vertex;
void error(char *error_msg)
{
	printf("**** %s ****\n", error_msg);
	exit(0);
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
void dfs(VTEX *vertex)
{
	EDGE *edge;
	if(vertex == NULL)
		return;
	printf("%s ", vertex->key);
	vertex->flag = VISITED;
	for(edge=vertex->edge; edge!=NULL; edge=edge->next)
		if(edge->vertex->flag == UNVISITED)
			dfs(edge->vertex);
}

int main()
{
	input();
	printf("dfs:\n");
	dfs(Vertex->next);
	printf("\n");
	system("pause");
}
/*
�����ĸ��ļ�: G0.txt
�ڽӱ�:
 a:  b  c  h
 h:  a  d  e
 c:  a  e
 b:  a  d
 d:  b  e  h
 e:  d  c  h
dfs:
a b d e c f

�����ĸ��ļ�: G1.txt
�ڽӱ�:
 1:  2  3  6
 6:  1  4  5
 3:  1  4
 2:  1  4  5
 5:  2  4  6
 4:  2  3  5  6
dfs:
1 2 4 3 5 6

�������ļ���: G2.txt
�ڽӱ�:
 a:  b  d
 d:  a  b  e  f
 b:  a  c  d  e
 e:  b  c  d  f  h
 c:  b  e
 f:  d  e  h
 h:  e  f
dfs:
a b c e d f h
*/
