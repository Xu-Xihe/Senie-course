---
title: "强连通分量与缩点"
linkTitle: "强连通分量与缩点"
type: blog
weight: 6
date: 2021-10-18
description: >
  断环成树？
---

# 强连通分量与缩点

## 又是啥玩意

### 强连通

~~在**有向图** $G$ 中，两个顶点 $u$，$v$ 间有一条从 $u$ 到 $v$ 的有向路径，同时还有一条从 $v$ 到 $u$ 的有向路径，则节点 $u$ 和 节点 $v$ 强连通。~~

啥玩意嘛。

简单一点，**有向图**中，两个节点之间可以**互相**到达，则这两个节点强连通。

### 强连通图

若有向图 $G$ 的每两个顶点都强连通，则 $G$ 是一个强连通图。

### 强连通分量

~~有向非强连通图的极大强连通子图，称为强连通分量。~~

又是嘛?

一个图 $G$，如果是有向图，但是不是强连通图，则图 $G$ 的所有是强连通图的子图中最大的(节点数最多的)称为强连通分量。

## 咋求？~~(向你缓缓打出一个？)~~ 

### Tarjan算法

经典算法？

首先，需要知道关于[DFS生成树](/oiblogs/graph图论/搜索/搜索/)的一些东西。

观察发现，任何一个强连通分量中必须有至少一个返祖边，因此如果结点 $u$ 是某个强连通分量在搜索树中遇到的第一个结点，那么这个强连通分量的其余结点肯定是在搜索树中以 $u$ 为根的子树中。$u$ 被称为这个强连通分量的根。Tarjan便以此为基础，进行求解。

#### 维护变量

- $dfn[i]$：维护节点 $i$ 的[dfs搜索序](/oiblogs/graph图论/搜索/搜索/)。
- $low[i]$：维护节点 $i$ 的子树中和子树中通过一条不在搜索树上的边能到达的所有结点的最小dfn值。
- $stack:run$：维护一个队列，保证上面的节点在以底下第一个 $low[i]=dfn[i]$ 的节点为根的强连通分量中。

从而我们得到两个推论：

1. 上节点的 $dfn$ 都大于该结点的 $dfn$ 。
2. 从根开始的一条路径上的 $dfn$ 严格递增，$low$ 严格非降。

#### 三种情况

对于当前节点 $u$，有一条 $u\rightarrow{v}$ 的边：

1. 节点 $v$ 未被访问过：继续对 $v$ 进行深度搜索。在回溯过程中，更新 $low[u]=min(low[u],low[v])$。
2. 节点 $v$ 被访问过，并且在栈中：说明找到一个返祖边，直接更新 $low[u]=min(low[u],low[v])$ 即可。
3. 节点 $v$ 被访问过，并且不在栈中：节点 $v$ 的强连通分量的根节点已经被找到，其强连通分量已经确定，不用操作。

#### 注意

<img src="graph%20(1).png" style="zoom: 75%;" />

当我们回溯到节点 $i$，发现其 $low[i]=dfn[i]$ 时，说明我们找到一个强连通分量的根节点，栈中在节点 $i$ 上面的都在以节点 $i$ 为根的强连通分量中，因此，对于 $\forall{}\space node\space x\in{upper\space i},\space low[x]=dfn[i]$ 。

否则，看上图…………经过细致的观察，我们发现，节点 $1、7、5、8、3、4$ 为强连通分量。如果你不在出栈的时候再更新一次，你就惊喜的发现，$low[4]=4$ ？？？因为搜索到 $4\rightarrow8$ 这条边的时候，因为节点 $8$ 刚刚搜搜索到一条至 $low=4$ 的节点，所以$low[8]=4$，就导致 $low[4]=4$，而后没有边再访问到节点 $4$，因此其 $low$ 值无法得到更新，始终为 $4$ ！！！然而，这显然是错的…………

然后，注意一定要在子树都搜索完成后，在进行弹栈操作。这样，保证横叉边也可以积攒在栈中。

#### 缩点

~~看起来好高深的ya子~~

这玩意菜的一批。

就是对于原来图中的边 $u\rightarrow v$ ，若 $low[u]\neq low[v]$ ，则在新图中连接一条 $low[u]\rightarrow low[v]$ 的边；若 $low[u]=low[v]$ ，则不执行任何操作。

这时候，我们会发现有可能连重了…………不影响的，好吧，不要强迫症。

#### 板子

[洛谷P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)

```c++
#include <cstdio>
#include <stack>
#include <vector>
#include <bitset>
#include <algorithm>
using std::max;
using std::min;
const int maxn = 1e4 + 9;
std::vector<int> next[maxn];
std::vector<int> nnet[maxn];
std::vector<int> root;
std::stack<int> run;
int n, m, val[maxn], dfn[maxn], low[maxn], cnt, nval[maxn], ans;
std::bitset<maxn> ins;
void tarjan(int now) //我们直接使用dfn[i]==0?来判断节点 i 是否被访问过
{
	ins[now] = 1; //对于任何一个没有被访问过的节点,有可能是根,加入栈
	run.push(now);
	dfn[now] = low[now] = ++cnt; //我们不清楚其子树
	for (int i : next[now])		 //遍历所有出度
	{
		if (!dfn[i]) //如果没有访问过,递归查找并update
		{
			tarjan(i);
			low[now] = min(low[now], low[i]);
		}
		else if (ins[i]) //如果访问过,直接更新
		{
			low[now] = min(low[now], low[i]);
		}
	}
	if (dfn[now] == low[now]) //我们搜索完了整个子树,若成立,即可判断当前节点是强连通分量的根
	{
		while (!run.empty() && dfn[run.top()] != low[run.top()]) //将压在当前节点上的都弹出
		{
			nval[low[now]] += val[run.top()];				//统计强连通分量中节点权值和
			low[run.top()] = min(low[run.top()], low[now]); //标记所有强连通分量的节！！！
			ins[run.top()] = 0;								//不在栈中了
			run.pop();
		}
		run.pop(); //同上
		ins[now] = 0;
		nval[low[now]] += val[now];
	}
}
void find(int now) //直接DFS暴搜找到最大路径
{
	cnt += nval[now];
	int len = nnet[now].size();
	if (!len)
	{
		ans = max(ans, cnt);
	}
	for (int i = 0; i < len; i++)
	{
		find(nnet[now][i]);
	}
	cnt -= nval[now];
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &val[i]);
	}
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		next[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) //防止出现非连通图,对于所有没被遍历到的点做Tarjan
	{
		if (!dfn[i])
		{
			ins.reset(); //多次不清空,暴零两行泪
			while (!run.empty())
				run.pop();
			tarjan(i);
		}
	}
	ins.reset(); //废物利用qwq
	for (int j = 1; j <= n; j++)
	{
		for (int i : next[j])
		{
			if (low[j] != low[i]) //这就是传说中的缩点
			{
				nnet[low[j]].push_back(low[i]);
				ins[low[i]] = 1; //记录入度
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (!ins[i]) //找到图中所有入度为0的点为根(非连通图可能有多个根)
		{
			root.push_back(i);
		}
	}
	for (int now : root) //对于每个根,跑DFS
	{
		cnt = 0; //又是废物利用qwq
		find(now);
	}
	printf("%d", ans);
	return 0;
}
```

