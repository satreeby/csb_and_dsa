/* File: getPFE.c
    ����4-10,4-13��˳��ջӦ�ã�����PFE(��׺���ʽ)	*/
#include <stdio.h>
#include <stdlib.h>
#define M 100
#define FULL M - 1
#define BTM 0
float S[M];
int Top = BTM - 1;
error(char *string) /* ��������		*/
{
    printf("%s\n", string);
    exit(1);
}
void push(float key) {
    if (Top >= FULL) /* �����overflow	*/
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
    if (Top < BTM) /* �����underflow	*/
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
    printf("PFE������: %5.2f\n", result);
    system("pause");
}
/*
��������
4 8 9 7 1 4 5 7 2 8 - + * + - * + - +
^Z

PFE������: 59.00

��������
4 5 7 - * 2 8 + - +
^Z

underflow!

��������
7 1 -  4 5 *
^Z

data overflow!

��������
-2 4 - -9 /
^Z

PFE������:  0.67

��������
-2 4 * -7 -
^Z

PFE������: -1.00

��������
-3 5 - 2 * 7 +
^Z

PFE������: -9.00
*/