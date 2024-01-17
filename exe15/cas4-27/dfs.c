/*	File: dfs.c
	[例4-27] 深度优先搜索法(Depth First Search)	*/

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
	char		key[10];	/* 字符型数据	*/
	int			flag;		/* 访问标记		*/
	EDGE		*edge;		/* 表链首指针	*/
	VTEX		*next;		/* 下一顶点指针	*/
};
EDGE
{
	VTEX		*vertex;	/* 顶点指针		*/
	EDGE		*next;		/* 表链指针		*/
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
	printf("输入哪个文件: ");
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
	printf("邻接表: \n");
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
输入哪个文件: G0.txt
邻接表:
 a:  b  c  h
 h:  a  d  e
 c:  a  e
 b:  a  d
 d:  b  e  h
 e:  d  c  h
dfs:
a b d e c f

输入哪个文件: G1.txt
邻接表:
 1:  2  3  6
 6:  1  4  5
 3:  1  4
 2:  1  4  5
 5:  2  4  6
 4:  2  3  5  6
dfs:
1 2 4 3 5 6

请输入文件名: G2.txt
邻接表:
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
