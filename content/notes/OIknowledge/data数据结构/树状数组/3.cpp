#include <cstdio>
const int maxe = 1e6 + 9;
int tree[maxe], len, q;
long long treei[maxe];
template <class T>
inline void add(int x, T val, T *num)
{
    for (; x <= len; x += x & -x)
        num[x] += val;
}
template <class T>
inline auto find(int x, T *num)
{
    long long ans = 0;
    for (; x > 0; x -= x & -x)
        ans += num[x];
    return ans;
}
inline auto sum(int x) { return (x + 1) * find(x, tree) - find(x, treei); }
int main()
{
    scanf("%d%d", &len, &q);
    int a, last = 0;
    for (int i = 1; i <= len; i++)
    {
        scanf("%d", &a);
        add(i, a - last, tree);
        add(i, (long long)(a - last) * i, treei);
        last = a;
    }
    while (q--)
    {
        int a, b, c, d;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1)
        {
            scanf("%d", &d);
            add(b, d, tree);
            add(b, (long long)d * b, treei);
            add(c + 1, -d, tree);
            add(c + 1, (long long)-d * (c + 1), treei);
        }
        else
            printf("%lld\n", sum(c) - sum(b - 1));
    }
    return 0;
}