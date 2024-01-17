#include <stdio.h>
#define N 100
int a[N];
int sum(int n){
    int i;
    int sum=0;
    for ( i = 0; i < N; i++)
    {
        sum=sum+a[i];
    }
    return sum;
}
void main(){
    int i;
    for ( i = 0; i < N; i++)
    {
        a[i]=i;
    }
    printf("%d\n",sum(100));
}