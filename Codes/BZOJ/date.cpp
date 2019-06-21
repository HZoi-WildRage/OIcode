#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
} v[200005];
int first[100005], p, n;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int size[100005];
int f[100005][30];
int dep[100005];
void dfs(int rt, int fa, int dp)
{
    dep[rt] = dp;
    f[rt][0] = fa;
    for (int i = 1; i <= 20; i++)
        f[rt][i] = f[f[rt][i - 1]][i - 1];
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (v[i].END != fa)
        {
            dfs(v[i].END, rt, dp + 1);
            size[rt] += size[v[i].END];
        }
}
int LCA(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    int t = dep[a] - dep[b];
    for (int i = 20; i >= 0; i--)
        if (t & (1 << i))
            a = f[a][i];
    if (a == b)
        return a;
    for (int i = 20; i >= 0; i--)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}
int Query(int a, int b)
{
    if (a == b)
        return n;
    if (dep[a] < dep[b])
        swap(a, b);
    int Lca = LCA(a, b);
    int l = dep[a] - dep[Lca];
    int r = dep[b] - dep[Lca];
    if ((l + r) & 1)
        return 0;
    int mid = l + r >> 1;
    int k = a;
    for (int i = 20; i >= 0; i--)
        if (mid & (1 << i))
            k = f[k][i];
    if (k == Lca)
    {
        int t = dep[a] - dep[Lca] - 1;
        for (int i = 20; i >= 0; i--)
            if (t & (1 << i))
                a = f[a][i], b = f[b][i];
        return n - size[a] - size[b];
    }
    else
    {
        int t = dep[a] - dep[k] - 1;
        for (int i = 20; i >= 0; i--)
            if (t & (1 << i))
                a = f[a][i];
        return size[k] - size[a];
    }
}
int main(int argc, char const *argv[])
{
    memset(first,-1,sizeof(first));
    int a, b;
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs(1, 0, 0);
    int m;
    scanf("%d",&m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        printf("%d\n", Query(a, b));
    }
    return 0;
}
