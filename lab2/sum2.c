#include <stdio.h>
#define N 43338
int a[N];
int sum(int n){
    if (n==0)
    {
        return 0;
    }
    if (n> N)
    {
        return sum(N);
    }
    return (sum(n-1)+a[n-1]);
}
void main(){
    int i;
    for (i = 0; i < N; i++)
    {
        a[i]=1;
    }
    printf("%d\n",sum(N));
}
