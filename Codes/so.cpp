#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <list>

using namespace std;

#define LL long long

struct data
{
    LL Num;
    int pos;
    bool operator<(const data &a) const
    {
        return Num == a.Num ? pos < a.pos : Num > a.Num;
    }
};

set<data> st;

LL a[100005];
int nex[100005], fre[100005];

LL Merge()
{
    int A = st.begin()->pos;
    LL ans = a[A];
    a[A] = -a[A];
    a[A] += a[fre[A]], a[A] += a[nex[A]];
    st.erase(st.begin());
    st.erase((data){a[fre[A]], fre[A]});
    st.erase((data){a[nex[A]], nex[A]});
    st.insert((data){a[A], A});
    if (fre[fre[A]])
        nex[fre[fre[A]]] = A;
    if (nex[nex[A]])
        fre[nex[nex[A]]] = A;
    fre[A] = fre[fre[A]];
    nex[A] = nex[nex[A]];
    return ans;
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        fre[i] = i - 1;
        nex[i] = i + 1;
        st.insert((data){a[i], i});
    }
    nex[n] = 0;
    a[0] = 0x8080808080808080ll;
    LL ans = 0;
    while (k--)
    {
        ans += Merge();
    }
    printf("%lld", ans);
}
