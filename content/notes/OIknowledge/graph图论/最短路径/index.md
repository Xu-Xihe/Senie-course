---
title: "最短路径"
linkTitle: "最短路径"
type: blog
weight: 4
date: 2021-10-18
description: >
  为了防止跑断腿儿，我们要学聪明一点。
---

# 最短路径

## 是个啥

这种问题恰如其名，问如何走才能用最小的代价达到目的。~~(人生哲学)~~

给你一张有边权的图(无权图可看做所有边边权均为1；无向图可将所有边拆分成两条有向边)，求$i$节点到$j$​节点的最短路径。

直接上算法。

## DFS

*BFS就涉及到其他算法了。*

只能求解单源单尽~~(自创)~~最短路(固定起点和终点)并且通常情况下过于暴力。

想法很简单，遍历两点之间的所有路径，选择最短的那条。

```c++
#include <cstdio>
#include <vector>
const int maxe = 1e4 + 9;
struct node
{
    int next, val;
};
std::vector<node> edge[maxe];
int len, m, ans = 2e9, sta, end;
bool ji[maxe];
inline void dfs(int now, int val)
{
    if (val >= ans || now == end) //结束条件和一点点剪枝
    {
        ans = ans > val ? val : ans;
        return;
    }
    int n = edge[now].size();
    ji[now] = 1; //记录访问过的节点,防止环
    for (int i = 0; i < n; i++)
    {
        if (ji[edge[now][i].next]) //如果出现环,终止
            continue;
        dfs(edge[now][i].next, edge[now][i].val + val); //继续递归
    }
    ji[now] = 0; //访问归零
}
int main()
{
    scanf("%d%d%d%d", &len, &m, &sta, &end);
    for (int i = 0; i < m; i++)
    {
        int a, b, v;
        scanf("%d%d%d", &a, &b, &v);
        edge[a].push_back(node{b, v});
    }
    dfs(sta, 0);
    printf("%d", ans);
    return 0;
}
```

## Floyd(弗洛伊德)算法

多源最短路(任意起止点)算法，时间复杂度 $O(n^3)$​，空间复杂度 $O(n^2)$​​。

适用于具有正或负边缘权重，但**没有负周期(负环)**的加权图中。在稠密图中效率较高。

运用dp思想，最开始只允许经过1号顶点进行中转，接下来只允许经过1号和2号顶点进行中转......允许经过$1\sim n$​号所有顶点进行中转，来不断动态更新任意两点之间的最短路程。

dp[i]\[j]表示从 $i$ 号节点到 $j$ 号节点的最短路径长度。

1. 首先构建邻接矩阵(存图)，假如现在只允许经过1号结点，求任意两点间的最短路程，很显然

$$
dp[i][j]=\min{dp[i][j],dp[i][1]+dp[1][j]}
$$

2. 接下来继续求在只允许经过1和2号两个顶点的情况下任意两点之间的最短距离，在已经实现了从 $i$ 号顶点到 $j$ 号顶点只经过$1$号节点的最短路程的前提下，现在再插入第$2$号结点，来更新更短路径，故只需在步骤1求得的基础上求
$$
dp[i][j]=\min{dp[i][j],dp[i][2]+dp[2][j]}
$$
3. $n$次更新后，表示依次插入了1号，2号......n号结点，最后求得的dp[i]\[j]是从 $i$ 号顶点到 $j$​ 号顶点只经过前 $n$ 号点的最短路程。

如需要记录详细路径，可使用另外一个二维数组存贮中转节点。

```c++
#include <cstdio>
#include <algorithm>
using std::min;
const int maxe = 3000, INF = 1000000009;
int n, m, dp[maxe][maxe], pot[maxe][maxe]; //如不需记录详细路径，不用pot
inline void pr_dis(int dp[maxe][maxe]) //最短路径输出
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dp[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
}
inline void pr_way(int sta, int end) //递归重建路径
{
    if (pot[sta][end] == 0) //若有边连接,则终止递归
        return;
    pr_way(sta, pot[sta][end]);   //递归输出左侧
    printf("%d ", pot[sta][end]); //输出本位
    pr_way(pot[sta][end], end);   //递归输出右侧
}
int main()
{
    scanf("%d%d", &n, &m);
    int sta;
    scanf("%d", &sta);
    for (int i = 1; i <= n; i++) //初始化
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = i == j ? 0 : INF;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int a, b, v;
        scanf("%d%d%d", &a, &b, &v);
        dp[a][b] = min(dp[a][b], v); //判断重边
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dp[i][j] > dp[i][k] + dp[k][j])
                {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    pot[i][j] = k; //更新节点记录
                }
            }
        }
    }
    for (int i = 0; i < n; i++) //输出
    {
        for (int j = 0; j < n; j++)
        {
            printf("\n%d  %d :  ", i + 1, j + 1);
            pr_way(i + 1, j + 1);
        }
    }
    printf("\n\n");
    pr_dis(dp); //输出
    return 0;
}
```

## Dijkstra算法

用于求解非负权图的单源最短路径。

运用[贪心](/oiblogs/basic基本思想/贪心/)思想，时间复杂度 $O(n^2)$ 或优化后 $O(n\log{n})$，空间复杂度 运行空间 $O(n)$ 和存图 $O(m)$。

用 $dis[i]$ 存贮从起始节点到第 $i$ 号节点的相对最短路径长度，并标记已经确定最短路径的顶点。

1. 初始化：设起始节点编号为 $k$，则 $dis[k]=0$，$i$ 与 $k$ 相连则 $dis[i]=边权$，其余的 $dis[j]=\infty$。
2. 松弛：在 $dis$ 数组中寻找未确定最短路径中 $dis[i]$ 最小，将 $i$ 加入已确定的顶点集合，并用其连接的边尝试使周围节点的 $dis$ 更小。(若存在负权，则有可能存在走负权边将以确定节点的最短路径变更小的可能，因此算法失效)

例子：

<img src="Dijkstra.jpg" alt="dijkstra" style="zoom: 70%;" />

**最暴力的code:**

```c++
#include <cstdio>
#include <vector>
const int maxe = 1e5 + 9, INF = 2147483647;
struct node //邻接链表存图
{
    int next, val;
};
std::vector<node> edges[maxe];
int n, m, sta, dis[maxe];
bool ji[maxe]; //记录是否已经确定答案
inline int lowest() //查找未加入点集中最小的dis
{
    int ans, lowt = INF;
    for (int i = 1; i <= n; i++)
    {
        if (!ji[i] && dis[i] < lowt)
        {
            lowt = dis[i];
            ans = i;
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d%d", &n, &m, &sta);
    for (int i = 1; i <= n; i++) //初始化
    {
        dis[i] = INF;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b, v;
        scanf("%d%d%d", &a, &b, &v);
        edges[a].push_back(node{b, v});
    }
    dis[sta] = 0;  //自己倒自己为0
    int now = sta; //当前要被加入点集的节点编号
    for (int i = 1; i < n; i++)
    {
        ji[now] = 1; //表示已加入
        int len = edges[now].size();
        for (int j = 0; j < len; j++) //尝试松弛相连节点
        {
            if (dis[now] + edges[now][j].val < dis[edges[now][j].next])
                dis[edges[now][j].next] = dis[now] + edges[now][j].val;
        }
        now = lowest(); //找到下一个加入点集的节点
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", dis[i]);
    }
    return 0;
}
```

**优化后code：**

用堆(优先队列)来找到dis最小的结点的复杂度为 $O(\log{n})$。

当一个节点的dis从 $\infty$ 被更新到一个值时会被加入优先队列，若没有更改，则所有可能到达的点的最小dis都被加入优先队列。

```c++
#include <cstdio>
#include <vector>
#include <queue>
const int maxe = 1e5 + 9, INF = 2147483647;
struct node //邻接链表存图
{
    int next, val;
    bool friend operator<(node a, node b)
    {
        return a.val > b.val;
    }
};
std::vector<node> edges[maxe];
std::priority_queue<node> run;
int n, m, sta, dis[maxe];
bool ji[maxe]; //记录是否已经确定答案
int main()
{
    scanf("%d%d%d", &n, &m, &sta);
    for (int i = 1; i <= n; i++) //初始化
    {
        dis[i] = INF;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b, v;
        scanf("%d%d%d", &a, &b, &v);
        edges[a].push_back(node{b, v});
    }
    dis[sta] = 0;  //自己到自己为0
    int now = sta; //当前要被加入点集的节点编号
    for (int i = 1; i < n; i++)
    {
        ji[now] = 1; //表示已加入
        int len = edges[now].size();
        for (int j = 0; j < len; j++) //尝试松弛相连节点
        {
            if (dis[now] + edges[now][j].val < dis[edges[now][j].next])
            {
                dis[edges[now][j].next] = dis[now] + edges[now][j].val;
                run.push(node{edges[now][j].next, dis[edges[now][j].next]}); //更新优先队列中的dis
            }
        }
        while (!run.empty() && ji[run.top().next]) //清空已加入点集的点
            run.pop();
        if(run.empty()) //防止不能连通出现死循环
            break;
        now = run.top().next;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", dis[i]);
    }
    return 0;
}
```

## SPFA算法

Bellman-Ford算法的队列优化算法的别称。

空间复杂度为 $O(n)$ 级别(不算图的存储)。

在正常情况下(数据随机构造或出题人很善良)，期望的时间复杂度为 $O(km)\space,\space k<2$，但是如果你碰上一个很厉(e)害(xin)的出题人，存在针对性数据，能把你卡成 $O(nm)$​，直接 **T** 飞！

因此如果边权不为负的话，还是老老实实用Dijkstra叭。

SPFA算法的实现有两种方式：

- DFS：在判定负环上优势明显，但求最短路即使各种优化，仍不及BFS。
- BFS：整体速度高于DFS，但应在仅需判断负环的题中弃用。

因此，应按照题目要求，选择对应的算法和方式。

### BFS方式

最常见也是综合最优。

1. 初始化：将dis数组除起点外赋值为 $\infty$ ，起点dis为$0$​，将起点加入run队列。
2. 松弛：将队头弹出，并使用与其相连的边更新其他相连节点的dis值，若 $i$ 号节点的dis值被更新并且 $i$ 号节点不再run队列中，则将 $i$ 加入run的队尾。
3. 重复执行松弛操作，直到队列为空。

优化原理：因为并不是dis一更新就继续迭代，而是很可能dis被更新多次之后才再次迭代，因此比DFS更优。

```c++
#include <cstdio>
#include <queue>
#include <vector>
const int maxe = 1e5 + 9, INF = 2147483647;
int n, m, sta, dis[maxe];
//1
struct node //邻接链表存图
{
    int next, val;
};
std::vector<node> edges[maxe];
std::queue<int> run;
bool in[maxe];
int main()
{
    scanf("%d%d%d", &n, &m, &sta);
    for (int i = 1; i <= n; i++) //初始化
    {
        dis[i] = INF;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b, v;
        scanf("%d%d%d", &a, &b, &v);
        edges[a].push_back(node{b, v});
    }
    run.push(sta); //将起点加入队列
    dis[sta] = 0;
    while (!run.empty())
    {
        int now = run.front();
        run.pop();
        in[now] = 0; //使队列中没有now
        int len = edges[now].size();
        for (int i = 0; i < len; i++)
        {
            if (dis[edges[now][i].next] > dis[now] + edges[now][i].val) //松弛操作
            {
                dis[edges[now][i].next] = dis[now] + edges[now][i].val;
                //2
                if (!in[edges[now][i].next]) //如果队列中没有
                {
                    run.push(edges[now][i].next); //加入队列并标记
                    in[edges[now][i].next] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", dis[i]);
    }
    return 0;
}
```

#### 对于负环的判断

记录当前路径的最短路经过的边的数量，若边数大于总节点数，则说明一定有一条边被走了两次，证明有负环的存在。

代码实现也很简单：

```c++
//在上面标号1的地方加入
int pass[maxe];
```

```c++
//在上面标号2的地方加入
pass[edges[now][i].next] = pass[now] + 1;
if (pass[edges[now][i].next] > n)
{
	printf("orz");
	return 0;
}
```

还有一种比较玄学的判负环方式，就是如果扩展了MAXN次还没出结果，就判定有负环。（MAXN为根据题目规模自拟的常量）

原理简单易懂：跑了这么久还没出结果，当然是有负环咯~~NB的是经实测正确率还相当高！当然相当高还是牺牲了算法的正确性的，因此不到万不得已之时不建议使用(玄学你懂的)。

#### 一些优化的方法

总体思想就是在你被出题人构造数据的情况下，如何能另辟蹊径，做出一些让出题人意想不到、另人捧腹大笑的sao操作，从而达到骗分的效果。

1. 简单的优化(只能让你的spfa跑的快一点，适用于常数大的同学。至于卡了spfa的题，仍旧没有什么用处。)
   1. **SLF(Small Label First)优化：** 在使用queue作为spfa的辅助数据结构时，将队列替换为双端队列，每当插入元素 $now$ 时，与队首进行比较，若 $dis[q.front()] > dis[now]$，将 $now$ 从队首插入，否则从队尾插入，使得更可能更新出节点最优解的节点最先进行更新，减少无用迭代次数。
   2. **LLL(Large Label Last）优化：** 使用双端队列，维护目前队列中元素到起点的距离的平均值（即 $\sum^{tail}_{i=head}dis[edges[i]/n]$），设该数为 $k$，若 $dis[now] > k$，则从队尾插入，否则从队首插入，用处不大。
2. 升级的优化 (能过数据不刁钻的卡spfa的题，至于某些丧心病狂的出题人，拜拜了您嘞)
   1. **容错后的SLF：** 定义容错值 $val$，当满足 $dis[now] > dis[q.front()] + val$ 时从队尾插入，否则从队首插入，可以让程序不陷入局部最优解。
   2. **mcfx优化：** 定义区间 $[l,r]$，当入队节点的入队次数属于这个区间的时候，从队首插入，否则从队尾插入，如过某个节点出发的大多数边都只能更新一个次解，那么它在队列中的优先级就会降低，防止链式结构卡死你。
   3. **Swap-SLF：** 若队列改变且 $dis[q.front()] > dis[q.back()]$​​，交换队首队尾，比较玄学。
3. 玄学的优化(都是sao操作，能过多少看人品)
   1. **边序随机：** 将读入给你的边随机打乱后进行spfa
   2. **队列随机：** 每个节点入队时，以 $\frac{1}{2}$ 的概率从队首入队，$\frac{1}{2}$​ 的概率从队尾入队。
   3. **队列随机优化版：** 累计 $m$ 次入队后，将队列元素随机打乱。

### DFS方式

经过极其强大的优化后速度可能和BFS同级，但是在仅判断负环的问题中十分快。

1. 初始化：将dis数组除起点外赋值为 $\infty$ ，起点dis为$0$，将起点加入run队列。
2. 递归松弛：使用与当期节点相连的边更新其他相连节点的dis值，若 $i$ 号节点的dis值被更新，则对 $i$​ 号节点递归操作。
3. 重复递归，直到无法更新。

由于这种东西的实用性过低，不给出标程(实际上是懒得)。

#### 关于优化

[姜碧野的《spfa算法的优化及应用》](http://www.doc88.com/p-49816668344446.html)十分详细且难以理解。

#### 对于负环的判断

十分新奇，其实只需要记住结论即可。证明：[文档](./SPFA-DFS负环证明.md)

结论即为：若存在负环，则**一定**存在特定的至少一对终止点之间的不重叠顶点最短路径的边权从起点**依次**相加**始终**为负。

所以，我们可以将dis数组初始值设为 $0$​，然后以每个节点为起点DFS，如果路径dis为正数就结束递归，这样相比于BFS方式可以忽略掉众多无用的边。

但是，这种方法不能求最短路。

```c++

```

## 最短路图

对于只能在最短路径上操作且可能同时存在多条最短路的问题时，可以采用建最短路图的方法。

将在 $i$ 和 $j$ 的最短路径上的边放入一个新的图当中，使得问题可以在一个DAG（有向无环图）上操作，因为最短路保证不出现环。

最短路图的建立(有一点点dp的感jio)：

首先，分别以 $i$ 和 $j$​ 跑一遍单源最短路(会用到)。

首先，思考一个事情，如何判断一条边是否在最短路图中？

当且仅当其满足 $dis_i[start]+val+dis_j[end]=dis_i[j]$ 时。

翻译一下，就是从 $i$ 到边起点的最短路径长度加上路径的权值再加 $j$ 到路径终点的最短路径长度等于 $i$ 到 $j$​ 的最短路径长度，因为只有这样，才能保证最短路径长度不变，即一种可能的情况。

```c++

```

## 分层图最短路

用于求解一些有复杂决策的问题。

在一个正常的图上可以进行 k 次决策，对于每次决策，不影响图的结构，只影响目前的状态或代价。一般将决策前的状态和决策后的状态之间连接一条权值为决策代价的边，表示付出该代价后就可以转换状态了。

就是将每个点根据状态的不同拆成若干个点，用拆出来的所有点建立新图并跑最短路。

一般有两种方案：

1. 建图时直接建成k+1层。

2. 多开一维记录其余(决策)信息，但是对于多种决策用处不大。

然后，在新建立的图中跑最短路。
