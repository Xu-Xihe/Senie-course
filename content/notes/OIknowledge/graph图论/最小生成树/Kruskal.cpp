#include <cstdio>
#include <algorithm>
int n, m, fa[6000], ans, cnt; //n个节点,m条边,已经选择cnt条边
struct edge
{
    int a, b, value;
} edges[200009];                //有一条端点是a和b,权重为value的边
inline bool cmp(edge a, edge b) //比较函数
{
    return a.value < b.value;
}
inline int find(int x) //并查集
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void together(int x, int y)
{
    x = find(x);
    y = find(y);
    fa[x] = y;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].value);
    }
    std::sort(edges, edges + m, cmp); //按边权排序
    for (int i = 0; i < m; i++)
    {
        if (find(edges[i].a) != find(edges[i].b)) //如果两个端点不再同一集合
        {
            ans += edges[i].value; //选中这条边
            cnt++;
            together(edges[i].a, edges[i].b); //合并两个集合
        }
        if (cnt == n) //最小生成树边数等于总节点数-1
            break;
    }
    if (cnt == n - 1) //最小生成树边数等于总节点数-1
        printf("%d", ans);
    else
        printf("orz");
    return 0;
}