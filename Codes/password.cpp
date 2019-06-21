#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
bool isnprime[1000005];
int prime[200005], Idx;
void Get_Prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 1000000; i++)
    {
        if (!isnprime[i])
        {
            prime[++Idx] = i;
        }
        for (int j = 1; j <= Idx; j++)
        {
            if (prime[j] * i > 1000000)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
long long Get_Phi(long long x)
{
    if (x == 1)
        return 0;
    int i = 1;
    int Sq = sqrt(x);
    long long ans = x;
    while (x != 1)
    {
        if (prime[i] > Sq)
        {
            ans = ans - ans / x;
            break;
        }
        if (x % prime[i] == 0)
        {
            ans = ans - ans / prime[i];
            while (x % prime[i] == 0)
                x /= prime[i];
        }
        ++i;
    }
    return ans;
}
long long phi;
class Martix
{
  public:
    int n, m;
    long long a[3][3];
    Martix(int n1, int m1)
    {
        n = n1, m = m1;
        memset(a, 0, sizeof(a));
    }
    Martix operator*(const Martix &A)
    {
        Martix ans(n, A.m);
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= A.m; k++)
            {
                for (int j = 1; j <= m; j++)
                    ans.a[i][k] += a[i][j] * A.a[j][k];
                if (ans.a[i][k] >= phi)
                    ans.a[i][k] = ans.a[i][k] % phi/* + phi*/;
            }
        return ans;
    }
    Martix operator^(const long long &b)
    {
        long long k = b;
        Martix ans(n, m);
        for (int i = 1; i <= n; i++)
        {
            ans.a[i][i] = 1;
        }
        Martix A = *this;
        while (k)
        {
            if (k & 1)
                ans = ans * A;
            k >>= 1;
            A = A * A;
        }
        return ans;
    }
};
long long pow_mod(long long a, long long b, long long mod)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}
int main()
{
    freopen("password.in", "r", stdin);
    freopen("password.out", "w", stdout);
    long long m, p;
    Get_Prime();
    Martix O(2, 2);
    O.a[1][1] = O.a[1][2] = O.a[2][1] = 1;
    Martix L(2, 1);
    L.a[1][1] = 1;
    scanf("%lld%lld", &m, &p);
    while (m--)
    {
        long long n, q;
        scanf("%lld%lld", &n, &q);
        if (q == 1)
        {
            printf("0\n");
            continue;
        }
        int t = p - q;
        if (t == 1)
        {
            printf("1\n");
            continue;
        }
        phi = Get_Phi(q);
        printf("%lld\n", pow_mod(p, ((O ^ n) * L).a[2][1], q));
    }
}
