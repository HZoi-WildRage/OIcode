#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e6 + 2e4;
const int INF = 0x3f3f3f3f;
struct edge
{
    int END, next, cap;
}v[MAXN * 12];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b, v[p].next = first[a], v[p].cap = c, first[a] = p++;
    v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[MAXN];
bool vis[MAXN];
bool BFS(int S, int E)
{
    queue<int> Q;
    memset (vis, 0, sizeof (vis));
    memset (dis, -1, sizeof (dis));
    vis[S] = 1;
    dis[S] = 0;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (!vis[v[i].END] && v[i].cap > 0)
            {
                vis[v[i].END] = 1;
                dis[v[i].END] = dis[k] + 1;
                Q.push(v[i].END);
            }
        }
    }
    return vis[E];
}
int DFS(int S, int E, int a)
{
    if (S == E || a == 0) return a;
    int flow = 0, f;
    for (int i = first[S]; i != -1; i = v[i].next)
    {
        if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
        {
            a -= f;
            flow += f;
            v[i].cap -= f;
            v[i ^ 1].cap += f;
            if (a == 0) break;
        }
    }
    if (!flow) dis[S] = -1;
    return flow;
}
int Dinic(int S, int E)
{
    int ans = 0;
    while (BFS(S, E))
    {
        ans += DFS(S, E, INF);
    }
    return ans;
}
int ID(int x, int y)
{
    return (x - 1) * 1000 + y;
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++)
        {
            int x = read();
            add(ID(i, j), ID(i, j + 1), x);
            add(ID(i, j + 1), ID(i, j), x);
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++)
        {
            int x = read();
            add(ID(i, j), ID(i + 1, j), x);
            add(ID(i + 1, j), ID(i, j), x);
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
        {
            int x = read();
            add(ID(i, j), ID(i + 1, j + 1), x);
            add(ID(i + 1, j + 1), ID(i, j), x);
        }
    printf ("%d\n", Dinic(ID(1, 1), ID(n, m)));
}