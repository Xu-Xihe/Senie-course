#include <cstdio>
const int maxe = 5e5 + 9;
int tree[maxe], n, m;
inline void add(int x, int val) //没啥不一样
{
    for (; x <= n; x += x & -x)
        tree[x] += val;
}
inline int sum(int x)
{
    int ans = 0;
    for (; x > 0; x -= x & -x)
        ans += tree[x];
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    int a, last = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        add(i, a - last); //建立差分数组
        last = a;
    }
    while (m--)
    {
        int a, b, c, d;
        scanf("%d%d", &a, &b);
        if (a == 1)
        {
            scanf("%d%d", &c, &d);
            add(b, d);      //将区间起点加val
            add(c + 1, -d); //将区间终点后一位减val,消除贡献
        }
        else
            printf("%d\n", sum(b));
    }
    return 0;
}