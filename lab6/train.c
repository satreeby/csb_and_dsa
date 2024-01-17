#include <stdio.h>
#include <stdlib.h>
#define N 5
/*出错处理函数*/
error(char *string)
{
    printf("%s\n", string);
    exit(1);
}
/*栈*/
struct Stack
{
    int numbers[N];
    int top;
};
/*进栈函数*/
void push(struct Stack* stack, int n){
    if (stack->top >= N)
        error("overflow!");
    stack->numbers[++(stack->top)] = n;
}
/*出栈函数*/
int pop(struct Stack* stack){
    if (stack->top < 0)
        error("underflow!");
    return (stack->numbers[stack->top--]);
}
/*火车队列*/
struct Queue
{
    int numbers[N];
    int head;
    int tail;
};
/*检查是否在栈里*/
int find(struct Stack* stack, int n){
    int i;
    for ( i = 0; i < stack->top; i++)
        if (stack->numbers[i]==n)
            return 1;
    return 0;
}
/*进队函数*/
void enqueue(struct Queue* queue, int n){
    if (queue->tail==N-1)
        error("overflow!");
    if (queue->head<0)
    {
        queue->head++;
    }
    queue->numbers[++queue->tail]=n;
}
/*出队函数*/
int dequeue(struct Queue* queue){
    if ((queue->head > queue->tail) || (queue->head<0))
        error("underflow!");
    return (queue->numbers[queue->head++]);
}

/*操作函数*/
void operation(struct Queue *inputs, struct Queue *outputs){
    int ops[2*N];//记录操作数目，0，1，2分别为"move push pop"
    struct Stack stack;
    stack.top=-1;
    int i=0, j=0, k=0;
    while (i!=N)
    {
        if ((stack.top>=0)&&(outputs->numbers[i]==stack.numbers[stack.top]))
        {
            do
            {
                pop(&stack);
                ops[k++]=2;         //"pop "
                i++;
            } while ((stack.top>=0)&&(outputs->numbers[i]==stack.numbers[stack.top]));
        }
        else if (find(&stack, outputs->numbers[i]))
            error("wrong!");
        else if ((j<N)&&(outputs->numbers[i]==inputs->numbers[j]))
        {
            do
            {
                ops[k++]=0;         //"move "
                i++;
                j++;
            } while ((j<N)&&(outputs->numbers[i]==inputs->numbers[j]));

        }
        else if (j<N)
        {
            do
            {
                push(&stack, inputs->numbers[j++]);
                ops[k++]=1;     //"push "
            } while ((j<N)&&(outputs->numbers[i]!=inputs->numbers[j]));
            
        }
        else
            error("wrong2!");
    }
    int end=k;
    for ( k = 0; k < end; k++)
    {
        switch (ops[k])
        {
        case 0: printf("move "); break;
        case 1: printf("push "); break;
        case 2: printf("pop "); break;
        default: break;
        }
    }
    return;
}

int main(){
    struct Queue inputs, outputs;
    /*初始化*/
    inputs.head=0;
    inputs.tail=N-1;
    inputs.numbers[0]=1;
    inputs.numbers[1]=2;
    inputs.numbers[2]=3;
    inputs.numbers[3]=4;
    inputs.numbers[4]=5;
    outputs.head=0;
    outputs.tail=N-1;
    outputs.numbers[0]=1;
    outputs.numbers[1]=2;
    outputs.numbers[2]=3;
    outputs.numbers[3]=5;
    outputs.numbers[4]=4;
    operation(&inputs, &outputs);
    return 0;
}