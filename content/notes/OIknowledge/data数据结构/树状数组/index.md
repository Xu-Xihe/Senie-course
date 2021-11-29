---
title: "树状数组"
linkTitle: "树状数组"
type: blog
weight: 7
date: 2021-10-17
description: >
  长得像一棵树一样的数组。
---

# 树状数组

一种~~[**倍增?**](/oiblogs/basic基本思想/倍增)[**分治？**](/oiblogs/basic基本思想/分治)~~思想下的奇奇怪怪的东西…………

~~先放个图~~<img src="%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84.png" alt="树状数组" style="zoom: 50%;" />

## 用的地方

1. 正常数组的单点修改时间复杂度为$O(1)$，区间查询为$O(n)$;
   而树状数组的单点修改和区间查询均为$O(\log{n})$。（因为树的高度为$\log{n}$）

2. 相比于某个更sb的东西：

**优点：**

1. 单次操作时间复杂度为$O(\log{n})$且常数很小，实际运行效率远优于[线段树](/oiblogs/data数据结构/线段树/)~~(虽然理论上时间复杂度相同)~~

2. 空间复杂度$O(n)$，在某些场景下较[线段树](/oiblogs/data数据结构/线段树/)($O(4n)$)有极大优势
3. 理解以后很好写(它很短，不费手，不需Debug $_{除非手残}$​  ~~(不理解也很好背)~~  ~~(理解是不可能理解的)~~

**缺点：**

适用范围比[线段树](/oiblogs/data数据结构/线段树/)**小的多**。树状数组能有的操作，线段树**一定有**；线段树有的操作，树状数组**大部分没有**。

## 最最最奇怪的地方

<img src="fenwick1.png" alt="&运算" style="zoom:68%;" />

~~你这玩意谁想的粗来？~~

### 先搞一个题外话——C++中对于负整数是如何存储的。

~~默认都知道变量会预留一个二进制位为符号位，虽然但是并没有什么关系且不知道也不影响~~

对于一个负整数，存贮方法为先将这个数的**绝对值取反**，**再$+1$**​。~~(是不是十分反人类!?)~~

举个栗子(上图也有)：$1$​​ --> $(0001)_2$​   $-1$​ --> $(1110)_2+(0001)_2$​​ --> $(1111)_2$

### 然后，我们惊喜的发现：

咦，如果我们吧原数和原数的相反数与起来好像不错……

$1\&-1$ = $(0001)_2$ ~~好像又回来了？~~

其实是我们得到了原数的lowbit，即原数二进制表示中为$1$的最低位。

再观察，它好像正好转换成十进制就是它的长度…………

~~这个世界好神奇!!!~~

~~不理解就放过自己吧，背住就好~~

## 终于，进入正题

~~最最最奇诡的东西过去了，剩下的就简单?了~~

树状数组的第$i$位维护以第$i$位为终点，长度为$i\&-i$的**区间和**。

更新时注意要将压在上面的**全部**更新

查找时只能查找从$1\sim i$的区间和；要想查找区间$[i,j]$的和，请用 $1\sim j$ 的区间和减去 $1\sim(i-1)$ 的区间和。

###### **注意! 是 $i-1$​​ 而不是 $i$​​ ​！！！**

从第$i$位开始向上查找，将所跳转到的求和，直到下标为$0$​。

```c++
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
```

## 区间修改和单点查询

用到一个比较神奇但是还能理解的东西[差分数组](/oiblogs/others杂项/差分数组/)。

用树状数组维护差分数组，以达到快速区间修改和单点查询的操作。

```c++
#include <cstdio>
const int maxe = 5e5 + 9;
int tree[maxe], n, m;
inline void add(int x, int val) //没啥不一样
{
    for (; x <= n; x += x & -x)
        tree[x] += val;
}
inline int sum(int x)
{
    int ans = 0;
    for (; x > 0; x -= x & -x)
        ans += tree[x];
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    int a, last = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        add(i, a - last); //建立差分数组
        last = a;
    }
    while (m--)
    {
        int a, b, c, d;
        scanf("%d%d", &a, &b);
        if (a == 1)
        {
            scanf("%d%d", &c, &d);
            add(b, d);      //将区间起点加val
            add(c + 1, -d); //将区间终点后一位减val,消除贡献
        }
        else
            printf("%d\n", sum(b));
    }
    return 0;
}
```
## 区间求和

~~奇妙~~

先让我们看一个$long\space long $的式子：
$$
\begin{aligned}
sum([1,r])=&\sum_{i=1}^{r} a_i=\sum_{i=1}^r\sum_{j=1}^i b_j\\=&\sum_{i=1}^r b_i\times(r-i+1)\\=&(r+1)\times \color{red}{\sum_{i=1}^r b_i}-\color{red}{\sum_{i=1}^r b_i\times i}
\end{aligned}
$$
~~你感受到数学的魅力了吗？是不是每一个字符你都认识，但是就是不懂它们组合起来是啥意思~~

亿点点地看，

$a$ 数组为原始数组(初始值)

$b$ 数组为树状数组维护的差分数组

下面把上面那段鬼话变成人话……不用数学符号就是有点长……
$$
\begin{aligned}
\sum([1,r])=&a_1+a_2+a_3+\cdots+a_{r-1}+a_r\\=&(b_1)+(b_1+b_2)+(b_1+b_2+b_3)+\cdots+(b_1+b_2+\cdots+b_{r-1})+(b_1+b_2+\cdots+b_{r-1}+b_r)\\=&(b_1\times r)+(b_2\times(r-1))+(b_3\times(r-2))+\cdots+(b_{r-1}\times2)+(b_r\times1)\\=&\sum_{i=1}^r b_i\times(r-i+1)\\=&\color{red}{(r+1)\times\sum_{i=1}^r b_i-\sum_{i=1}^r b_i\times i}
\end{aligned}
$$
推导之后，我们发现，用树状数组维护两个值($b_i$ 和 $b_i\times i$)即可。

## 二维、多维树状数组

~~最简单的一种**树套树**~~           ~~直接套娃即可~~          ~~这辈子也别想画出示意图~~

在外层树状数组的每个节点上维护一棵树状数组

查询/更新时使用二重循环即可。

[百度百科](https://baike.baidu.com/item/%E4%BA%8C%E7%BB%B4%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84)  ~~看懂是不可能看懂的，慎重尝试~~

```c++
#include <cstdio>
const int maxe = 5e2 + 9;
int n, m, q, tree[maxe][maxe];
inline void add(int x, int y, int val) //注意不能直接调用y,双重循环
{
    for (int i = x; i <= n; i += i & -i)
    {
        for (int j = y; j <= m; j += j & -j)
        {
            tree[i][j] += val;
        }
    }
}
inline int sum(int x, int y)
{
    int ans = 0;
    for (int i = x; i > 0; i -= i & -i)
    {
        for (int j = y; j > 0; j -= j & -j)
        {
            ans += tree[i][j];
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int a;
            scanf("%d", &a);
            add(i, j, a);
        }
    }
    while (q--)
    {
        char aa[100];
        int a, b, c, d;
        scanf("%s%d%d%d", aa, &a, &b, &c);
        if (aa[0] == 'A')
            add(a, b, c);
        else
        {
            scanf("%d", &d);
            printf("%d\n", sum(b, d) + sum(a - 1, c - 1) - sum(b, c - 1) - sum(a - 1, d));
            //二维前缀和
            //减一不搞好,亲人两行泪
        }
    }
    return 0;
}
```

## 树状数组上的二分

建议直接移步[平衡树](/oiblogs/data数据结构/平衡树/)或者[线段树](/oiblogs/data数据结构/线段树/)。

**摘抄如下：**

类似于线段树上二分，树状数组上也可以进行二分。

使用**树状数组上二分**（可能需要预先离散化），可以$O(log\space{n})$​查询第 $k$​ 小/大元素，实现类似**平衡树**的效果。

主要思想是：按二进制位从高到低逐渐二分出答案。

```c++
int kth(int k) {
    int r = 0, t;
    for (int i = LOG_N; i>=0; --i) {
        t = r | 1 << i;     
        if (t <= n && d[t] < k)k -= d[t], r = t;
    }
    return r + 1;
}
```

