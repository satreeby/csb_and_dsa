#include <stdio.h>
#include <math.h>
struct Point {
    double x, y;
};
struct Points {
    struct Point P[100];
};
double getx(struct Point P) {
    return P.x;
}
double gety(struct Point P) {
    return P.y;
}
void setx(struct Point *P, double x) {
    P->x = x;
}
void sety(struct Point *P, double y) {
    P->y = y;
}
double getrou(struct Point P) {
    return sqrt(P.x * P.x + P.y * P.y);
}
double gettheta(struct Point P) {
    return atan(P.y / P.x);
}
void setrou(struct Point *P, double rou, double theta) {
    P->x = rou * cos(theta);
}
void settheta(struct Point *P, double rou, double theta) {
    P->y = rou * sin(theta);
}
struct Point getPoint(struct Points Ps, int n){
    if (n < 100 && n >= 0)
    {
        return Ps.P[n];
    }
} 
void setPoint(struct Points *Ps, int n, double x, double y){
    if (n < 100 && n >= 0)
    {
        setx(&Ps->P[n],x);
        sety(&Ps->P[n],y);
    }
}
int main() {
    struct Point P;
    struct Points Ps;
    setx(&P, 1);
    sety(&P, 1);
    printf("% f, % f", getx(P), gety(P));
    printf("% f, % f", getrou(P), gettheta(P));
    setPoint(&Ps, 0, 6, 8);
    printf("% f, % f", getx(Ps.P[5]), gety(Ps.P[5]));
    struct Point p1;
    p1=getPoint(Ps,5);
    printf("% f, % f", getrou(p1), gettheta(p1));
    double a=1, b=0;
    double k=atan(a/b);
    printf(" %f",k);
}
