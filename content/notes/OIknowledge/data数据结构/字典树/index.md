---
title: "字典树"
linkTitle: "字典树"
type: book
weight: 10
date: 2021-10-17
summary: 让一部字典长成一棵树。
---

# 字典树

## 这是一棵神奇的树

~~字典树，顾名思义，就是一个字典。~~

字典树，又称前缀树，作用是储存一些字符串……方便查询与修改。

具体来说，就是将每一个字符串变成树上的一条链，从 $root$ 到每个叶子节点就是我们要储存的一个字符串。

举个栗子，我们要储存 $ababa$ 、$badab$ 、$adace$ 、$abace$ 、$cdeab$ 、$abcab$ 、$ccc$ ，就是下图：

<img src="%E5%AD%97%E5%85%B8%E6%A0%91.png" alt="fa" style="zoom:80%;" />

当然，我们也可以在边上存储字符，具体操作可按照个人喜好来搞，均可以实现字典树的种种操作。

对于字符串 $aba$ 改如何储存呢？很简单，在其结尾打一个 $tag$ 即可。

## 基本操作

注意，我们下面讨论的都是节点存储字符的情况，而并非字符存储在边上。~~其实都差不多，就是如何理解的问题。~~

### 结构

```c++
int tot; //记录总节点个数，用于分配新的节点
struct node //每个节点储存节点编号、节点上的字符和是否是结尾
{
    int id;
    char val;
    bool tag;
};
std::vector<node> next[maxe]; //储存每个节点的儿子,便于查找
```

### 插入

```c++
inline void ins(char *in)     //本来应该是dfs的,只不过优化为循环了
{
    int now = 0, len = strlen(in); //标记当前节点的编号,字符串的长度
    for (int i = 0; i < len; i++)
    {
        int ci = next[now].size(); //遍历子节点
        bool is = 0;               //记录是否找到可以用的链
        for (int j = 0; j < ci; j++)
        {
            if (next[now][j].val == in[i])
            {
                if (i == len - 1) //如果是字符串结尾就打tag
                    next[now][j].tag = 1;
                is = 1;
                now = next[now][j].id; //跳转到这个儿子，继续ins
                break;
            }
        }
        if (!is) //如果没有匹配的节点,就要新建一个
        {
            next[now].push_back(node{++tot, in[i], i == len - 1 ? true : false});
            now = tot; //跳转到新建的节点
        }
    }
}
```

### 查找

```c++
inline bool find(char *in) //本来应该是dfs的,只不过优化为循环了
{
    int now = 0, len = strlen(in); //标记当前节点的编号,字符串的长度
    for (int i = 0; i < len; i++)
    {
        int ci = next[now].size(); //遍历子节点
        bool is = 0;               //记录是否找到可以用的链
        for (int j = 0; j < ci; j++)
        {
            if (next[now][j].val == in[i])
            {
                is = 1;           //标记找到了
                if (i == len - 1) //如果是结尾,则判断是否有tag(若没有,就是字典中某个字符串的前缀)
                    is = next[now][j].tag;
                now = next[now][j].id;
                break;
            }
        }
        if (!is) //如果没找到合适的子节点,说明树中没有这个字符串
            return false;
        if (i == len - 1) //如果全部匹配,则字典中有所查询的字符串
            return true;
    }
}
```

### 另一种

我们还可以按照边来储存字符，并且我们可以在一定程度上用时间换空间(其实只是减小了常数)。

直接对于每个节点开出字符范围大小的数组，对应位置储存对应字符的儿子节点(如果有的话)，这样就省去了查找子节点是啥子的时间，但是同时要在空间上做出一定的牺牲，适用于字符范围较小的字典。

[FaiOJ #30034. 「一本通 2.1 例 2」图书管理](http://faioj.brynhild.online/problem/30034) ~~就是板子~~

```c++
#include <cstdio>
struct node
{
    int next[60];//我们直接开出全部字符范围,然后按照下标存储
    bool tag; //0~29  30~59
} nodes[3000000];
int root = 1, tot = 1;
inline void ins(char *in)
{
    int pos = root, val;//val就是让你省一点代码
    for (; *in; ++in) //这玩意和 for(int i = 0;i < len;i++)一个意思
    {
        val = (*in) >= 'A' && (*in) <= 'Z' ? (*in) - 'A' : (*in) - 'a' + 30;//找到相对应的下标
        if (!nodes[pos].next[val])//没有这个节点
            nodes[pos].next[val] = ++tot;
        pos = nodes[pos].next[val];//跳转到下一个,继续插入
    }
    nodes[pos].tag = true;//结尾打tag
}
inline bool find(char *in)
{
    int pos = root, val;
    for (; *in; ++in)
    {
        val = (*in) >= 'A' && (*in) <= 'Z' ? (*in) - 'A' : (*in) - 'a' + 30;
        if (!nodes[pos].next[val])
            return false;
        pos = nodes[pos].next[val];
    }
    return nodes[pos].tag>0?true:false;
}
int len;
char ord[10], name[500];
int main()
{
    scanf("%d", &len);
    while (len--)
    {
        scanf("%s %[^\n]", ord, name);
        if (ord[2] == 'd')
            ins(name);
        else
            printf("%s\n", find(name) ? "yes" : "no");
    }
    return 0;
}
```

## 这玩意能干啥

字典树因为其特有的结构，在大量字符串的查找、修改、比较中有较大的优势。

还可以进行转化，用于比较二进制($k$进制)下的数字大小等。亦可以用于关于前缀的若干问题。

但是，还是那句话，数据结构都是用来在暴力的情况下进行优化的……

# $01$​-Trie

## 没错，这个东西用来搞二进制的

**01-trie**是将整数的二进制表示（位数固定，补前导零）看做一个字符串，按二进制位**从高到低**的顺序插入构建出的字符集为 $\{0,1\}$ 的字典树。

事实上，与平衡树类似，01-trie也可以用于维护一个有序集合，支持插入、删除、数查排名、排名查数等操作。但由于空间开销大等原因，很少见到这样使用01-trie的OI选手。~~(我会[平衡树](./平衡树.md)，还要这玩意干屁)~~

01-trie 最常见的应用是快速计算数 $x$ 与字典树中所有数异或结果的**最大值**或最小值。以最大值为例，具体的做法是从树根开始（即按二进制位从高到低）贪心：

- 若存在与 $x$ 当前位上的值相反的边，则走这条边，使这一位的异或结果成为 $1$；
- 若不存在，则走相同的边，使这一位的异或结果为 $0$。

答案从高位到低位~~(说话算数的到说话不算数的)~~依次构造，正确性显然。

## 板子

[FaiOJ #30050. 「一本通 2.3 例 2」The XOR Largest Pair](http://faioj.brynhild.online/problem/30050)

