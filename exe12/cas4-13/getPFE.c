/* File: getPFE.c
    【例4-10,4-13】顺序栈应用：计算PFE(后缀表达式)	*/
#include <stdio.h>
#include <stdlib.h>
#define M 100
#define FULL M - 1
#define BTM 0
float S[M];
int Top = BTM - 1;
error(char *string) /* 出错处理函数		*/
{
    printf("%s\n", string);
    exit(1);
}
void push(float key) {
    if (Top >= FULL) /* 上溢出overflow	*/
        error("overflow!");
    S[++Top] = key;
    /* ifdebug
        printf("P:S[%d]=%5.2f\n", Top, S[Top]);
    */
}
float pop() {
    /* ifdebug
        printf("O:S[%d]=%5.2f\n", Top, S[Top]);
    */
    if (Top < BTM) /* 下溢出underflow	*/
        error("underflow!");
    return (S[Top--]);
}

void main() {
    float result, data;
    char str[50];
    while (scanf("%s", str) > 0) {
        if (str[0] == '+'
            || str[0] == '-' && str[1] == '\0'
            || str[0] == '*'
            || str[0] == '/') {
            data = pop();
            result = pop();
            switch (str[0]) {
            case '+':
                result = result + data;
                break;
            case '-':
                result = result - data;
                break;
            case '*':
                result = result * data;
                break;
            case '/':
                result = result / data;
                break;
            }
            push(result);
        } else {
            sscanf(str, "%f", &data);
            push((float)data);
        }
    }
    if (Top != BTM)
        error("data overflow!");
    result = pop();
    printf("PFE计算结果: %5.2f\n", result);
    system("pause");
}
/*
输入数据
4 8 9 7 1 4 5 7 2 8 - + * + - * + - +
^Z

PFE计算结果: 59.00

输入数据
4 5 7 - * 2 8 + - +
^Z

underflow!

输入数据
7 1 -  4 5 *
^Z

data overflow!

输入数据
-2 4 - -9 /
^Z

PFE计算结果:  0.67

输入数据
-2 4 * -7 -
^Z

PFE计算结果: -1.00

输入数据
-3 5 - 2 * 7 +
^Z

PFE计算结果: -9.00
*/