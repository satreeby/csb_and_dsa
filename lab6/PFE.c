#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
/*词*/
struct Token
{
    int type;   //type=0:整数,type=1:运算符
    int value;
};
/*出错处理函数*/
error(char *string)
{
    printf("%s\n", string);
    exit(1);
}
/*栈，进栈函数，出栈函数*/
struct Stack
{
    struct Token tokens[N];
    int top;
};
void push(struct Stack* stack, struct Token token){
    if (stack->top >= N)
        error("overflow!");
    stack->tokens[++(stack->top)] = token;
}
struct Token pop(struct Stack* stack){
    if (stack->top < 0)
        error("underflow!");
    return (stack->tokens[stack->top--]);
}
/*后缀表达式队列，进队函数，出队函数*/
struct Queue_PFE
{
    struct Token tokens[N];
    int head;
    int tail;
};
void enqueue(struct Queue_PFE* queue, struct Token token){
    if (queue->tail==N-1)
        error("overflow!");
    if (queue->head<0)
    {
        queue->head++;
    }
    queue->tokens[++queue->tail]=token;
}
struct Token dequeue(struct Queue_PFE* queue){
    if ((queue->head > queue->tail) || (queue->head<0))
        error("underflow!");
    return (queue->tokens[queue->head++]);
}
/*从字符串中获取PFE队列*/
void getPFEqueue(struct Queue_PFE* PFE, char* str){
    struct Token t;
    int i, type_sti;
    for ( i = 0; i < strlen(str); i++)
    {
        if (str[i]==' ') type_sti=2;
        else if (str[i]>='0'&&str[i]<='9') type_sti=0;
        else if (str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/') type_sti=1;
        else error("PFE is wrong!");        
        if (i==0)
        {
            if (type_sti!=0) error("PFE is wrong!");
            t.type=0;
            t.value=str[i]-'0';
        }
        else
        {
            switch (type_sti)
            {
                case 0:
                    if (t.type==0) t.value=t.value*10+str[i]-'0';
                    else if (t.type==1) error("PFE is wrong!");
                    else
                    {
                        t.value=str[i]-'0';
                        t.type=0;
                    }
                break;
                case 1:
                    if (t.type!=2) error("PFE is wrong!");
                    t.type=1;
                    t.value=str[i];
                    enqueue(PFE, t);
                break;
                case 2:
                    if (t.type==0)
                    {
                        enqueue(PFE, t);
                        t.type=2;
                        t.value=0;
                    }
                    else if (t.type==1)
                    {
                        t.type=2;
                        t.value=0;
                    }
                    else error("PFE is wrong!");
                break;
                default:
                    break;
            }
        }
    }
}
/*计算PFE的值*/
int calculate(struct Queue_PFE* PFE){
    int op1, op2;
    int result;
    struct Stack stack;
    stack.top=-1;
    struct Token token;
    while (PFE->head<=PFE->tail)
    {
        token=dequeue(PFE);
        if (token.type==0)
        {
            push(&stack, token);
        }
        else
        {
            op2=pop(&stack).value;
            op1=pop(&stack).value;
            switch (token.value)
            {
            case (int)'+':
                result=op1+op2;
                token.type=0;
                token.value=result;
                break;
            case (int)'-':
                result=op1-op2;
                token.type=0;
                token.value=result;
                break;
            case (int)'*':
                result=op1*op2;
                token.type=0;
                token.value=result;
                break;
            case (int)'/':
                if (op2 == 0)
                {
                    error("cannot be devided by 0");
                }
                result=op1/op2;
                token.type=0;
                token.value=result;
            default:
                break;
            }
            push(&stack, token);
        }
    }
    if (stack.top!=0)
    {
        error("This PFE is wrong!");
    }
    return pop(&stack).value;
}
int main(){
    struct Queue_PFE PFE;
    PFE.head=PFE.tail=-1;
    char str[]={"3 2 + 6 *"};
    getPFEqueue(&PFE, str);
    int result;
    result=calculate(&PFE);
    printf("%d",result);
}
