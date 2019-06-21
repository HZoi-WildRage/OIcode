#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 305;
const double eps = 1e-20;
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator - (const Point &a)
    {
        return Point(x - a.x, y - a.y);
    }
    double operator * (const Point &a) 
    {
        return x * a.y - y * a.x;
    }
}a[MAXN], c[MAXN];
struct line
{
    Point a, b;
    line(){}
    line(Point _a, Point _b)
    {
        a = _a;
        b = _b;
    }
    double k;
}l[MAXN];
bool cmp(line a, line b)
{
    if (a.k == b.k) return (b.a - a.a) * (b.b - a.a) >= eps;
    return a.k < b.k;
}
Point Get_Point(line a, line b)
{
    Point x;
    double dot1, dot2;
    dot1 = (b.a - a.a) * (b.b - a.a);
    dot2 = (b.b - a.b) * (b.a - a.b);
    x.x = (a.a.x * dot2 + a.b.x * dot1) / (dot1 + dot2);
    x.y = (a.a.y * dot2 + a.b.y * dot1) / (dot1 + dot2);
    return x;
}
bool Judge(line a, line b, line c)
{
    Point x = Get_Point(b, c);
    return (a.b - x) * (a.a - x) >= eps;
}
int Q[MAXN];
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i].x = read();
    for (int i = 1; i <= n; i++)
        a[i].y = read();
    a[0].x = a[1].x - 1, a[0].y = 10000000;
    a[n + 1].x = a[n].x + 1, a[n + 1].y = 10000000;
    n++;
    for (int i = 1; i <= n; i++)
    {
        l[i].a = a[i - 1], l[i].b = a[i];
        l[i].k = atan2(a[i].y - a[i - 1].y, a[i].x - a[i - 1].x);
    }
    int cnt = 1;
    sort(l + 1, l + n + 1, cmp);
    for (int i = 2; i <= n; i++)
        if (l[i].k - l[i - 1].k >= eps)
            l[++cnt] = l[i];
    int h = 1, t = 2;
    Q[1] = 1, Q[2] = 2;
    for (int i = 3; i <= cnt; i++)
    {
        while (t > h && Judge(l[i], l[Q[t - 1]], l[Q[t]])) t--;
        while (t > h && Judge(l[i], l[Q[h + 1]], l[Q[h]])) h++;
        Q[++t] = i;
    }
    while (t > h && Judge(l[h], l[Q[t - 1]], l[Q[t]])) t--;
    while (t > h && Judge(l[t], l[Q[h + 1]], l[Q[h]])) h++;
    int tot = 0;
    for (int i = h + 1; i <= t; i++)
        c[++tot] = Get_Point(l[Q[i - 1]], l[Q[i]]);
    double ans = 1e60;
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j <= tot; j++)
            if (a[i].x <= c[j].x && c[j].x <= a[i + 1].x)
            {
                Point t(c[j].x, -1);
                ans = min(ans, c[j].y - Get_Point(line(a[i + 1], a[i]), line(c[j], t)).y);
            }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j < n; j++)
            if (c[i].x <= a[j].x && a[j].x <= c[i + 1].x)
            {
                Point t(a[j].x, -1);
                ans = min(ans, Get_Point(line(c[i], c[i + 1]), line(a[j], t)).y - a[j].y);
            }
    printf ("%.3f\n", ans);
    // while (1);
}