#include <cstdio>
const int maxe = 10009;
int n, m, fa[maxe];
inline int find(int x) //find函数和路径压缩的完美结合,递归思想
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void together(int a, int b) //应该是最短的写法
{
    fa[find(a)] = find(b);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) //初始化,最开始每个人都是一个门派
    {
        fa[i] = i;
    }
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1)
            together(b, c);
        else
            printf("%c\n", find(b) == find(c) ? 'Y' : 'N');
    }
    return 0;
}