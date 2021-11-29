---
title: "树链刨分"
linkTitle: "树链刨分"
type: blog
weight: 7
date: 2021-10-18
description: >
  把一棵树劈开的多重方法……
---

# 树链刨分

一种极致优化的树上算法，据说07年被某个集训队队员搞出来的。

关于DFN序，参见[搜索](/oiblogs/graph图论/搜索/搜索/)。

## 一波约定

为方便起见,我们约定一棵树的某些数据如下：

- $siz[i]$ 表示 $i$ 结点的子树大小

- $dep[i]$ 表示 $i$ 结点的所在深度(定义根的所在深度为$1$)

- $fa[i]$ 表示 $i$ 结点的父结点编号

- $bson[i]$ 表示 $i$ 节点的重儿子的编号

- $top[i]$ 表示 $i$ 节点所在链的顶端节点

## 儿子还分轻重?

对于任意一个**非叶子**结点，它的子结点中 $siz$ 最大的定义为它的重儿子，其余的子结点定义为它的轻儿子。注意：重儿子有且仅有一个，若有多个最大子树，任意选择一个为重儿子，其余为轻儿子即可。叶子节点没有重儿子。

> 很好理解，从字面上来看，重儿子就是子树中节点数最多的那一个，比较“重”；而剩下的儿子的子树节点数比较少，所以就“轻”。

这样，我们可以将树上的边也分为两类：父结点与重儿子之间连接的边为**重边**，与轻儿子连接的边为**轻边**。

进而推广到，由多条重边连接而成的路径为**重链**。

看一个例子：

<img src="%E6%A0%91%E9%93%BE%E5%89%96%E5%88%86.png" alt="adf" style="zoom:80%;" />

其中，<font color="ffbf00">黄色节点</font>为其父亲节点的<font color="ffbf00">重儿子</font>，白色为轻儿子；<font color="red">红色边</font>为<font color="red">重边</font>，黑色为轻边；<font color="green">绿色底</font>为<font color="green">重链</font>。

如此划分，则：

1. 轻边 $(u,v)$ 中, $size(u)≤ size(\frac{v}{2})$

>至少存在一个重儿子大于等于自己的 $size$。

2. 从根到某一点的路径上,不超过 $\log{n}$ 条轻链和不超过 $\log{n}$ 条重链。

3. 树中任意两个节点之间的路径，都可以将其拆分为不超过 $4\log{n}$ 条重链 + 轻边

## 它来了

~~本质上是一种优化暴力~~

首先，完成树链剖分，有如下操作：

1. 求出每个节点的子树大小(找到重儿子)，每个节点的深度

2. 在第 $1$ 步的基础上，找出每条轻链和重链

简化一下，就是先DFS一次，求DFS序，把烂七八糟的填上；然后再来一次，把轻链和重链搞出来，完事。

第一次：

```c++
inline void dfs1(int now, int deep)
{
    dep[now] = deep;
    int big = 0; //别忘了初始化
    for (auto i : next[now])
    {
        if (!fa[i]) //无向图判断是否是父节点，防止死循环
        {
            fa[i] = now; //子节点的父亲是自己
            dfs1(i, deep + 1); //递归遍历
            if (size[i] > big) //有更重的儿子
            {
                big = size[i];
                son[now] = i; //标记重儿子
            }
            size[now] += size[i]; //加上这个儿子的size
        }
    }
    size[now]++; //加上自己的1个
    return;
}
```

第二次：

```c++
inline void dfs2(int now, int t, bool big)
{
    //这里如果要维护区间的话，要记录dfn序，注意先遍历重儿子
    top[now] = t; //维护链顶端顶点
    if (!son[now]) //叶子节点
        return;
    dfs2(son[now], t, 1); //先递归查找重链
    for (int i : next[now])
    {
        if (i != fa[now] && i != son[now])
        {
            dfs2(i, i, 0); //递归轻边
        }
    }
}
```



## 一些细节

1. **轻链：**

很多博文中，我们又看到了一个新的东西——轻链。

其实，你是**不能**把轻边连成一条链的，看下图：

<img src="graph%20(3)-16332643443841.png" style="zoom:70%;" />

我们观察发现，如果我们将 $9$ 挂到 $3$ 上面的话，就和 $3\rightarrow8\rightarrow10$ 这条重链重了，造成求解的失败。

2. **top：**

在树链刨分中，我们要把一条重链上的点看做一个点，即这条重链的顶点，比较是均以顶点去比较。

3. **跳转fa：**

注意，每次跳转的时候，都要跳转到顶点的fa，否则就死循环卡那了。

## 实战：求解LCA

LCA，最近公共祖先。

结点 $u$ 和 $v$ 向上跳，每次将**深度较大**的结点跳到自己所在的链的顶端结点，重复执行直至两个结点位于同一条重链上。

一个一个的跳，防止跳过了。

选择深度较大的点，保证了在跳到的链上从顶点到原先的深度可以反复横跳，这样，如果另一个深度较小的点也跳到了同一个链上，则上链深度一定在深度较大的点的横跳范围之内，所以就是LCA。

这里注意，每次将**链顶深度**大的点向上跳，当在同一条链上时，取**深度较小**的点为LCA。

时间复杂度为 $O(\log{n})$

[洛谷 P3379 【模板】最近公共祖先（LCA）][https://www.luogu.com.cn/problem/P3379]

```c++
#include <cstdio>
#include <vector>
#include <algorithm>
const int maxn = 5e5 + 9;
int n, m, root, size[maxn], son[maxn], top[maxn], dep[maxn], fa[maxn];
std::vector<int> next[maxn];
inline void dfs1(int now, int deep)
{
    dep[now] = deep;
    int big = 0, ji = 0;
    for (auto i : next[now])
    {
        if (!fa[i])
        {
            fa[i] = now;
            dfs1(i, deep + 1);
            if (size[i] > big)
            {
                big = size[i];
                son[now] = i;
            }
            size[now] += size[i];
        }
    }
    size[now]++;
    return;
}
inline void dfs2(int now, int t, bool big)
{
    top[now] = t;
    if (!son[now])
        return;
    dfs2(son[now], t, 1);
    for (int i : next[now])
    {
        if (i != fa[now] && i != son[now])
        {
            dfs2(i, i, 0);
        }
    }
}
inline int lca(int a, int b)
{
    while (top[a] != top[b])
    {
        if (dep[top[a]] < dep[top[b]])
            std::swap(a, b);
        a = fa[top[a]];
    }
    return dep[a] > dep[b] ? b : a;
}
int main()
{
    scanf("%d%d%d", &n, &m, &root);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        next[a].push_back(b);
        next[b].push_back(a);
    }
    fa[root] = root;
    dfs1(root, 1);
    dfs2(root, root, 0);
    while (m--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", lca(a, b));
    }
    return 0;
}
```

