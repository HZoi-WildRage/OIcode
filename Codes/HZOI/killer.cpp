#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
struct edge
{
    int END, next;
} v[1000005], E[1000005];
int first[100005], Efirst[100005], p, Ep;
void add(int a, int c)
{
    v[p].END = c;
    v[p].next = first[a];
    first[a] = p++;
}
void add1(int a, int c)
{
    E[Ep].END = c;
    E[Ep].next = Efirst[a];
    Efirst[a] = Ep++;
}
int S[100005];
int low[100005], dfsn[100005], Index;
bool flag[100005];
int T;
int belong[100005];
stack<int> st;
void tarjan(int rt)
{
    low[rt] = dfsn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfsn[v[i].END])
        {
            tarjan(v[i].END);
            low[rt] = min(low[rt], low[v[i].END]);
        }
        else if (flag[v[i].END])
            low[rt] = min(low[rt], dfsn[v[i].END]);
    }
    if (dfsn[rt] == low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
            S[T]++;
        } while (dfsn[v] != low[v]);
    }
}
int isnroot[100005], ithason[100005];
int main()
{
    memset(first, -1, sizeof(first));
    memset(Efirst, -1, sizeof(Efirst));
    //freopen("killer.in", "r", stdin);
    //freopen("killer.out", "w", stdout);
    int n, m;
    int s, e;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        add(s, e);
    }
    for (int i = 1; i <= n; i++)
        if (!dfsn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
    {
        for (int j = first[i]; j != -1; j = v[j].next)
        {
            if (belong[i] != belong[v[j].END])
            {
                add1(belong[i], belong[v[j].END]);
                isnroot[belong[v[j].END]]++;
                ithason[belong[i]]++;
            }
        }
    }
    int ans = 0;
    bool flags = 0;
    for (int i = 1; i <= T; i++)
    {
        if (!isnroot[i])
        {
            ans++;
            if (flags)
                continue;
            //if (!ithason[i])
            //    flags = 1;
            if (S[i] == 1)
            {
                if (!ithason[i])
                    flags = 1;
                else
                {
                    bool e = 0;
                    for (int j = Efirst[i]; j != -1; j = E[j].next)
                    {
                        if (isnroot[E[j].END] == 1)
                            e = 1;
                    }
                    if (!e)
                        flags = 1;
                }
            }
        }
    }
    // if (!ans)
    //     ans = 1;
    if (flags)
        ans -= 1;
    printf("%.6lf", (double)(n - ans) / n);
}