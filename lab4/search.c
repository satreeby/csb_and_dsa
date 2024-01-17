#include <stdio.h>
#define N 10        //设置链表长度
struct Node
{
    int value;
    struct Node* next;
};
//循环方法
struct Node* find1(struct Node* head, int i){
    struct Node* p=head->next;
    int j=0;
    for (; (j < i)&&(p != NULL); j++)
        p=p->next;
    return p;
}
//递归方法
struct Node* MaybeNode(struct Node* node1){
    return (node1==NULL) ? NULL : node1->next; 
}
struct Node* find2(struct Node* head, int i){
    return (i==0) ? head->next : MaybeNode(find2(head, i-1)); 
}
int main(){
    struct Node* head=(struct Node*)malloc(sizeof(struct Node));
    struct Node* tail=head;
    tail->next=NULL;
    int i;
    for ( i = 0; i < N; i++)
    {
        struct Node* p= (struct Node*) malloc (sizeof(struct Node));
        p->next=NULL;
        p->value=i; //赋value值为对应表的编号，以便于检查函数的正确性 
        tail->next=p;      
        tail=p; 
    }
    struct Node *p1, *p2;
    int k;          //寻找编号为k的结点
    k=0;            //测试k=0的情况
    p1=find1(head,k);
    printf("使用循环方法找到编号为%d的结点的地址为%hx，结点的value为%d\n",k,p1,p1->value);
    p2=find2(head,k);
    printf("使用递归方法找到编号为%d的结点的地址为%hx，结点的value为%d\n",k,p2,p2->value);
    k=9;            //测试k=9的情况
    p1=find1(head,k);
    printf("使用循环方法找到编号为%d的结点的地址为%hx，结点的value为%d\n",k,p1,p1->value);
    p2=find2(head,k);
    printf("使用递归方法找到编号为%d的结点的地址为%hx，结点的value为%d\n",k,p2,p2->value);
    k=15;            //测试k=15的情况
    p1=find1(head,k);
    printf("使用循环方法找到编号为%d的结点的地址为%hx\n",k,p1);
    p2=find2(head,k);
    printf("使用递归方法找到编号为%d的结点的地址为%hx\n",k,p2);
}