#include <stdio.h>
#define ROW 4
#define COL 4
int a[ROW][COL];
void in2out(int n_start, int n_stop, int m_start, int m_stop){
    if ( n_stop < n_start || m_stop < n_start )
        return;
    if ( n_start == n_stop )
    {
        int j;
        for (j = m_stop; j > m_start-1; j--)
            printf("%d ",a[n_start][j]);
        return;
    }
    if ( m_start == m_stop )
    {
        int i;
        for (i = n_stop; i > n_start-1; i--)
            printf("%d ",a[i][m_stop]);
        return;
    }
    in2out(n_start+1, n_stop-1, m_start+1, m_stop-1);
    int i=0,j=0;
    for ( i = n_start+1; i < n_stop; i++ )
        printf("%d ",a[i][m_start]);
    for ( j = m_start; j < m_stop; j++ )
        printf("%d ",a[n_stop][j]);
    for ( i = n_stop; i > n_start; i-- )
        printf("%d ",a[i][m_stop]);  
    for ( j = m_stop; j > m_start-1; j-- )
        printf("%d ",a[n_start][j]);
    return;
}
int main(){
    a[0][0]=1;a[0][1]=2;a[0][2]=3;a[0][3]=4;
    a[1][0]=5;a[1][1]=6;a[1][2]=7;a[1][3]=8;
    a[2][0]=9;a[2][1]=10;a[2][2]=11;a[2][3]=12;
    a[3][0]=13;a[3][1]=14;a[3][2]=15;a[3][3]=16;
    in2out(0, 3, 0, 3);
    return 0;
}