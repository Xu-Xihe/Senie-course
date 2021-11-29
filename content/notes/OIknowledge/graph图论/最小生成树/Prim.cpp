#include <cstdio>
const int maxe = 6000; //n的最大值
int n, m, head[maxe], cnt;
//n个点,m条边,head[i]表示已i为端点最后读入的一条边的编号,已经读入cnt条边
bool vis[maxe]; //vis[i]标记i节点是否在最小生成树点集中
struct node
{
    int value, last, sign; //value表示边权,last表示同一起点的上一条读入的边的编号,sign表示当前节点编号
} edge[400009];
//m最大值*2
void add_edge(int start, int end, int value) //链式前向星
{
    edge[++cnt].value = value;
    edge[cnt].sign = end;
    edge[cnt].last = head[start];
    head[start] = cnt;
    return;
}
int prim()
{
    int dis[maxe], ans = -1e9;
    //dis[i]表示连接未加入点集的i号节点和点集中任意点最短路径长,ans = -1e9抵消选择第一个点溢出
    for (int i = 1; i <= n; i++)
    {
        dis[i] = 2e9; //初始化dis数组
    }
    int k = 1, min;             //k记录所选择的点的编号,min记录最小值,k初始值为第一个加入点集的点的编号
    vis[1] = 1;                 //将第一个点加入点集
    for (int i = 0; i < n; i++) //循环n次,将所有点加入点集
    {
        min = 1e9;                   //别忘了qwq,注意小于dis初始者,判断是否无法建树
        for (int j = 1; j <= n; j++) //暴力搜索最小点,可用堆/平衡树(优先队列、set等)优化
        {
            if (!vis[j] && dis[j] < min)
            {
                min = dis[j];
                k = j;
            }
        }
        if (min == 1e9 && k != 1) //除第一个点外,如果没有未加入点集的点有连接且点集中小于n个点,证明有点无法连同
        {
            return 0;
        }
        ans += min;
        vis[k] = 1;
        for (int i = head[k]; i; i = edge[i].last) //用新加入的点更新dis数组
        {
            if (!vis[edge[i].sign] && dis[edge[i].sign] > edge[i].value)
            {
                dis[edge[i].sign] = edge[i].value;
            }
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int a, b, value;
        scanf("%d%d%d", &a, &b, &value);
        add_edge(a, b, value); //无向边,任意端点可作为起止点
        add_edge(b, a, value);
    }
    int ans = prim();
    if (ans)
        printf("%d", ans);
    else
        printf("orz");//无法连同所有点
    return 0;
}