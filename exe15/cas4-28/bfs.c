/*	File: bfs.c
	[例4-28] 广度优先搜索法(Breadth First Search)	*/

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
Q
{
	VTEX		*vertex;
	Q *next;
};
VTEX *Vertex;
Q *Head = NULL, *Tail = NULL;	/* 队列指针	*/
void error(char *error_msg)
{
	printf("**** %s ****\n", error_msg);
	exit(0);
}
void enQueue(VTEX *vertex)		/* 链接队列进队函数	*/
{
	Q *node;
	node = (Q *)malloc(sizeof(Q));			/* 动态申请结点		*/
	if(node == NULL) 						/* 上溢出			*/
		error("overflow!");
	if(Tail != NULL)						/* 更新指针：正常进队	*/
		Tail = Tail->next = node;
	else									/* 更新指针：空队进队	*/
		Tail = Head = node;
	Tail->vertex = vertex;					/* 进队：队尾插入结点	*/
	Tail->next = NULL;
}
VTEX *deQueue(void)			/* 链接队列出队函数	*/
{
	VTEX *vertex;
	if(Head == NULL)
		return(NULL); 		/* 下溢出			*/
	vertex = Head->vertex;	/* 取出队首结点		*/
	Head = Head->next;
	if(Head == NULL)		/* 出空操作			*/
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
void bfs(VTEX *vertex) 								/* BFS遍历函数			*/
{
	EDGE *edge;
	enQueue(vertex); 								/* vertex进队			*/
	while( vertex = deQueue() ) 					/* 只要队非空			*/
	{
		if(vertex->flag == UNVISITED)				/* 如果vertex未访问		*/
		{
			printf("%s ", vertex->key);				/* 打印顶点				*/
			vertex->flag = VISITED;					/* 标记vertex			*/
			for(edge=vertex->edge; edge; edge=edge->next)
				if(edge->vertex->flag == UNVISITED)
					enQueue(edge->vertex);			/* 未访问邻接顶点进队	*/
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
输入哪个文件: G1.txt
邻接表:
 1:  2  3  6
 6:  1  4  5
 3:  1  4
 2:  1  4  5
 5:  2  4  6
 4:  2  3  5  6
bfs:
1 2 3 6 4 5

请输入文件名: G2.txt
邻接表:
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
