# 项目介绍(最近更新——2025年3月2日⌛)
 **记录一些常见的有意义的BUG或者经验教训，方便大家学习交流
**

## 文件上传的「黄金法则」✔
### （1）三不上传原则❌
- **不上传原始工程文件**

Altium Designer 等大型工程 → 只上传 PDF 版原理图 + STEP 模型

- **不上传二进制构建产物**

固件 .bin 文件 → 通过 GitHub Releases 管理

- **不上传临时调试数据**

逻辑分析仪原始数据 → 精选关键波形截图 + 文字分析

## 分支管理🔀
- main 分支——展示最终版本
- dev  分支——审核期版本，定期向 main 分支提交
- feature_作者1昵称————此分支为贡献者分支，由大家维护并分享日常BUG或经验
- feature_作者2昵称————此分支为贡献者分支，由大家维护并分享日常BUG或经验
