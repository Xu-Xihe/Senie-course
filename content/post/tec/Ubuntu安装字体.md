---
# Documentation: https://wowchemy.com/docs/managing-content/

title: "Ubuntu安装字体"
subtitle: ""
summary: "众所周知，Linux向来是自己动手丰衣足食，因此，字体这玩意，当然得自己安。"
authors: [XXH]
tags: [Ubuntu,支持]
categories: [tec]
date: 2021-11-22T15:19:39+08:00
lastmod: 2021-11-22T15:19:39+08:00
featured: false
draft: false

# Featured image
# To use, add an image named `featured.jpg/png` to your page's folder.
# Focal points: Smart, Center, TopLeft, Top, TopRight, Left, Right, BottomLeft, Bottom, BottomRight.
image:
  caption: ""
  focal_point: ""
  preview_only: false

# Projects (optional).
#   Associate this post with one or more of your projects.
#   Simply enter your project's folder or file name without extension.
#   E.g. `projects = ["internal-project"]` references `content/project/deep-learning/index.md`.
#   Otherwise, set `projects = []`.
projects: []
---

## 引言

众所周知，`Ubuntu` 是一个著名的Linux开源发行版。但是，开源……这就意味着，那些不开源的字体用不了！

所以，本着~~开源~~务实的精神，我们要安装字体。（除非你想每天都被你的老师叫过去解决PPT的各种奇奇怪怪的问题）

而字体文件？当然是，Windows！~~虽然，有些blabla~~

## 复制字体

1. 如果你的网络不好，可以选择从一台安装有Windows系统的计算机进行拷贝。将 `C:\Windows\Fonts` 目录中的<b><font color=red size="5">所有</font></b>文件拷贝到移动介质中待用。

>至于为什么是所有，别问我，就问那帮人为啥动不动就老用一些奇奇怪怪的字体，为了防止多次安装的惨痛后果，除非你非常清楚你需要什么，建议全部安装。(反正就500来MB，也不大)

2. 如果你的网络尚可或者你身边并没有一台Windows电脑，则可以点击下面:point_down:的链接进行下载后解压。

> 地址1：腾讯coding [直接下载](https://xu-xihe.coding.net/p/windows-fonts/d/fonts/git/archive/main/?download=true) [访问项目](https://xu-xihe.coding.net/public/windows-fonts/fonts/git/files)
>
> 地址2：Gitee ~~众所周知，这玩意下载Zip必须登录~~ [访问项目](https://gitee.com/xu-xihe/windos-fonts.git)

## 安装字体

1. 移动所有字体文件致 `/usr/share/fonts/` 或者其子文件夹中。**注意：**如果你想要进行分类的话，可以自行新建子文件夹。
2. 修改字体文件权限，使得所有用户都可以访问，请执行 `sudo chmod -R /usr/share/fonts/{yourname} 755`。若不清楚是否执行成功，请跳过并继续。
3. 运行 `mkfontscale` 。若提示 `mkfontscale: command not found`，则先执行 `sudo apt install ttf-mscorefonts-installer` 后重试。
4. 运行 `mkfontdir` 和 `fc-cache -fv`。
5. 打开字体管理器，确认安装。

{{< comment >}}
