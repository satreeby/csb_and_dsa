#include <stdio.h>
#define ROW 4
#define COL 4
int a[ROW][COL];
void out2in(int n_star,int n_stop,int m_star,int m_stop){
    if ( n_stop < n_star || m_stop < n_star )
        return;
    if ( n_star == n_stop )
    {
        int j;
        for ( j = m_star; j < m_stop+1; j++)
        {
            printf("%d ",a[n_star][j]);
        }
        return;
    }
    if (m_star == m_stop)
    {
        int i;
        for ( i = n_star; i < n_stop+1; i++)
        {
            printf("%d ",a[i][m_stop]);
        }
        return;
    }
    int i=0;
    int j=0;
    for ( j = m_star; j < m_stop+1; j++ )
        printf("%d ",a[n_star][j]);
    for ( i = n_star+1; i < n_stop+1; i++ )
        printf("%d ",a[i][m_stop]);
    for ( j = m_stop-1; j > m_star-1; j-- )
        printf("%d ",a[n_stop][j]);
    for ( i = n_stop-1; i > n_star; i-- )
        printf("%d ",a[i][m_star]);
    out2in(n_star+1, n_stop-1, m_star+1, m_stop-1);
    return;
}
int main(){
    a[0][0]=0;a[0][1]=1;a[0][2]=2;a[0][3]=3;
    a[1][0]=0;a[1][1]=1;a[1][2]=2;a[1][3]=3;
    a[2][0]=0;a[2][1]=1;a[2][2]=2;a[2][3]=3;
    a[3][0]=0;a[3][1]=1;a[3][2]=2;a[3][3]=3;
    out2in(0, 3, 0, 3);
    return 0;
}