#include <cstdio>
const int maxe = 5e5 + 9;
int tree[maxe], n, m;
inline void add(int x, int val) //一直更新直到最上层
{
    for (; x <= n; x += x & -x)
        tree[x] += val;
}
inline int sum(int x) //一直加到下标为0
{
    int ans = 0; //注意赋初始值为0，防止奇奇怪怪的事情
    for (; x > 0; x -= x & -x)
        ans += tree[x];
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int a;
        scanf("%d", &a);
        add(i, a);
    }
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1)
            add(b, c);
        else
            printf("%d\n", sum(c) - sum(b - 1));
    }
    return 0;
}