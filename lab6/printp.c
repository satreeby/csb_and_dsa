#include <stdio.h>
struct Node
{
    int n;
    struct Node* next;
};

//假设单链表无表头
void forwardprint(struct Node* head){
    if (head)
    {
        printf("%d ", head->n);
        forwardprint(head->next);
    }
    return;
}
void backwardprint(struct Node* head){
    if (head)
    {
        backwardprint(head->next);
        printf("%d ", head->n);
    }
    return;
}
struct Node* reverse(struct Node* head){
    struct Node* newhead;
    if (head==NULL||head->next==NULL)
        return head;
    newhead=reverse(head->next);
    head->next->next=head;
    head->next=NULL;
    return newhead;
}

int main(){
    struct Node* head=NULL;
    int i;
    for ( i = 10; i > 0; i--)
    {
        struct Node* p=(struct Node*)malloc(sizeof(struct Node));
        p->n=i;
        p->next=head;
        head=p;
    }
    forwardprint(head);
    printf("\n");
    backwardprint(head);
    printf("\n");
    head=reverse(head);
    forwardprint(head);
    printf("\n");
    backwardprint(head);
    printf("\n");
}