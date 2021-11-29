---
title: "差分约束"
linkTitle: "差分约束"
type: book
weight: 10
date: 2021-10-17
summary: 不等式和最短路到底有什么关系？
---

[难懂但是比较全的博文](https://blog.csdn.net/consciousman/article/details/53812818?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162925274616780265475802%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162925274616780265475802&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-53812818.pc_search_result_control_group&utm_term=%E5%B7%AE%E5%88%86%E7%BA%A6%E6%9D%9F&spm=1018.2226.3001.4187)

## 这是啥子?

简单来说，差分约束就是把不等式转变成图的一种思想。因为题目可能会给你很多不等式，使用数学方法很有可能无解，而且难以找到这些不等式之间的联系。但是当我们把它们转化成图之后，就可以使用图论的思想来解题。

通常，差分约束是用来解决求一组形如 $a-b\leq{c}$ 的不等式的可能最大/最小解。

对于每一个 $i-j\le z$，建立一条从 $j$ 到 $i$ 权值为 $z$ 的有向边，将求解 $a-b\le{c}$ 的最大/最小值转化为求从 $b$ 到 $a$ 的最短/最长路径长度。

## 三角不等式

若有一个不等式组：

$$
\begin{cases}\begin{aligned}\begin{array}{rcl}
&C-B\le{a}\newline&C-A\le{b}\newline&B-A\le{c}
\end{array}\end{aligned}\end{cases}
$$

则根据上述条件，可以建图如下：

<img src="graph.png" alt="adf" style="zoom:95%;" />

由不等式相加组合，可得到 $max(C-A)=min(b,a+c)$，这也正好对应图中 $A$ 到 $C$ 的最短路。

对于最大值：
$$
\begin{aligned}
\begin{cases}\begin{array}{rcl}
&C-B\ge{a}\newline&C-A\ge{b}\newline&B-A\ge{c}
\end{array}
\end{cases}
\end{aligned}
$$
由不等式相加组合，可得到 $min(C-A)=max(b,a+c)$，这也正好对应图中 $A$ 到 $C$ 的最长路。

因此，对三角不等式加以推广，变量 $n$ 个，不等式 $m$ 个，要求 $C-A$ 的最大/最小值，便就是求取建图后 $A-C$ 的最短/最长路。

另：

1. 若出现 $C-A=b$ 的情况，可以拆分为 $C-A\ge{b}$ 和 $C-A\le{b}=A-C\ge{-b}$ 或 $C-A\ge{b}=A-C\le{-b}$ 和 $C-A\le{b}$ 两条边。
2. 若出现 $C-A>b$的情况，因为题目中大多是整形数据，因此变为 $C-A\ge{b+1}$ 即可。
3. 值得注意的一点是：若建立的图不联通，则需要加入一个超级源点 $S$，在 $S$ 和其他的每个点之间建立一条权值为 $0$ 的**无向边**，然后从 $S$ 点开始求解即可。

## 无名算法

流程：

1. 构建基于不等式的关系图。
2. 跑[最短路](./最短路径.md)(注意，最长路可以通过spfa求出来，只需要改下松弛的方向即可，即`if(dis[v] < dis[u] + val(u,v)) dis[v] = dis[u] + val(u,v)`。当然我们可以把图中所有的边权取负，求取最短路，两者是等价的。)
3. 建图后不一定存在最短路/最长路，因为可能存在负环/正环，判断差分约束系统是否存在解一般判环即可。

一些注意事项：

1. 根据条件把题意通过变量组表达出来得到不等式组，注意要发掘出隐含的不等式，比如说前后两个变量之间隐含的不等式关系。
2. 建好图之后直接spfa求解，一般不能用dijstra算法，因为通常存在负边。
3. 注意初始化的问题。

[洛谷P5960](https://www.luogu.com.cn/problem/P5960)

```c++

```

{{< comment >}}
