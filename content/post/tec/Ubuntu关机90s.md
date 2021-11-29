---
# Documentation: https://wowchemy.com/docs/managing-content/

title: "Ubuntu关机90s"
subtitle: ""
summary: "Ubuntu关机的时候出现等待1min30s的情况的解决办法。"
authors: [XXH]
tags: [Ubuntu,解决方案]
categories: [tec]
date: 2021-11-22T15:15:41+08:00
lastmod: 2021-11-22T15:15:41+08:00
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

## 现象

通常情况下，他会显示一个啥啥啥 is running，然后后面有一个括号 `(..s/1min30s)` 这种。

## 解决方法

虽然我们并不知道为啥，但是我们确实有一种解决的方法。

1. 用root权限（其实就是加个 `sudo`）编辑 ` /etc/systemd/system.conf`，找到里面有一个 `DefaultTimeoutStopSec=90s`，把行首的 `#` 去掉，并改成 `DefaultTimeoutStopSec=1ms`，保存，退出。
2. 执行 `sudo systemctl daemon-reload` 更新配置文件。

{{< comment >}}
