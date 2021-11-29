#include <cstdio>
const int maxe = 5e2 + 9;
int n, m, q, tree[maxe][maxe];
inline void add(int x, int y, int val) //注意不能直接调用y,双重循环
{
    for (int i = x; i <= n; i += i & -i)
    {
        for (int j = y; j <= m; j += j & -j)
        {
            tree[i][j] += val;
        }
    }
}
inline int sum(int x, int y)
{
    int ans = 0;
    for (int i = x; i > 0; i -= i & -i)
    {
        for (int j = y; j > 0; j -= j & -j)
        {
            ans += tree[i][j];
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int a;
            scanf("%d", &a);
            add(i, j, a);
        }
    }
    while (q--)
    {
        char aa[100];
        int a, b, c, d;
        scanf("%s%d%d%d", aa, &a, &b, &c);
        if (aa[0] == 'A')
            add(a, b, c);
        else
        {
            scanf("%d", &d);
            printf("%d\n", sum(b, d) + sum(a - 1, c - 1) - sum(b, c - 1) - sum(a - 1, d));
            //二维前缀和
            //减一不搞好,亲人两行泪
        }
    }
    return 0;
}