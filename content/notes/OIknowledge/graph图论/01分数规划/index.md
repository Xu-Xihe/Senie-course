---
title: "01分数规划"
linkTitle: "01分数规划"
type: blog
weight: 11
date: 2021-10-18
description: >
  解分式？
---

# 01分数规划

## 问题

使两个线性函数的比值最大或最小的问题，称作分数规划问题或双曲线问题。

而01分数规划和01背包问题差不多：

我们现在有 $n$ 个物品，每一个物品均有一个 $val$ 和 $cost$，$x_i\in[0,1]$ 表示第 $i$ 物品是(1)否(0)选择。

从 $n$ 个物品必须选择 $k$ 个，求下式的最大/最小值。
$$
\frac{\sum_{i=1}^nval_i\times{x_i}}{\sum_{i=1}^ncost_i\times{x_i}}
$$

## 二分解法

[二分在这边](/oiblogs/basic基本思想/分治/)

假设答案为 $ans$
$$
ans=min(\frac{\sum_{i=1}^nval_i\times{x_i}}{\sum_{i=1}^ncost_i\times{x_i}})
$$
则一定有
$$
ans\times{\sum_{i=1}^ncost_i\times{x_i}}=\sum_{i=1}^nval_i\times{x_i}
$$
即
$$
\sum_{i=1}^nval_i\times{x_i}-ans\times{\sum_{i=1}^ncost_i\times{x_i}}=0
$$
所以，将每个物品的权值置为 $v-r\times{c}$，排序后，判断前k个物品的权值和与 $0$ 比较，进而缩小二分界限，得出 $ans$ 值。

# 最大比率环

和01分数规划思路基本相同，建立好模型后二分答案。

通过判断图内是否存在负环来调整二分界限

![fa](https://img-blog.csdnimg.cn/20210213120449912.png)