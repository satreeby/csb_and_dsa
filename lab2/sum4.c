#include <stdio.h>
#define N 43338
int a[N];
int sum(int n,int result){
    if (n==0)
    {
        return result;
    }
    if (n>N)
    {
        return sum(N,0);
    }
    return (sum((n-1),a[n-1]+result));    
}
void main(){
    int i;
    for ( i = 0; i < N; i++)
    {
        a[i]=2;
    }
    int s;
    s=sum(N,0);
    printf("%d\n",s);
}