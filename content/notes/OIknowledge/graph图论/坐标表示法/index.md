---
title: "坐标距离"
linkTitle: "坐标距离"
type: blog
weight: 12
date: 2021-10-18
description: >
  嗯？两个点之间的距离竟然有好几种？
---

# 坐标之间的常用距离

通常，OI中使用到的两点之间坐标(针对于维度大于一的坐标系)通常用如下三种。

## 欧几里得距离

定义为**以两点为端点的线段的长度**。

如下图，欧几里得距离为<font color="red">线段d</font>的长度。

<img src="geogebra-export.png" alt="adf" style="zoom:16%;" />

$S=\sqrt{\abs{1-3}^2+\abs{5-2}^2}\approx3.61$

## 曼哈顿距离

两点 $x,y,z\space\cdots\cdots$ 坐标差的绝对值之和。

如下图，曼哈顿距离为<font color="red">线段d和线段g</font>的长度之和。

<img src="geogebra-export-16292841405421.png" alt="adsf" style="zoom:16%;" />

$S=\abs{5-2}+\abs{1-3}=3+2=5$

## 切比雪夫距离

两点 $x,y,z\space\cdots\cdots$ 坐标差的绝对值的最大值。

如下图，切比雪夫距离为<font color="red">线段d和线段g</font>中长度较大的那一个，即<font color="red">线段d</font>。

<img src="geogebra-export-16292841405421.png" alt="fa" style="zoom:16%;" />

$S=max(\abs{5-2},\abs{1-3})=max(3,2)=3$

## 坐标转化

一般提示距离的字眼：

- **欧几里得距离：**平面最短距离。
- **曼哈顿距离：**从一个点出发，可以上下左右移动到另一点，移动的最小步数。
- **切比雪夫距离：**从一个点出发，可以向八个方向（包括斜向）移动，移动点最小步数。(因为斜着移动同时改变两个坐标)

曼哈顿距离和切比雪夫距离之间可以通过坐标的变换进行相互转化：

- 将每一个点 $(x,y)$ 转化为 $(x+y,x−y)$ ，新坐标系下的切比雪夫距离即为原坐标系下的曼哈顿距离。

- 将每一个点 $(x,y)$ 转化为 $(\frac{x+y}{2},\frac{x−y}{2})$，新坐标系下的曼哈顿距离即为原坐标系下的切比雪夫距离。

~~这一段背住得了，[证明](https://zhuanlan.zhihu.com/p/32878257)不看也罢。~~

