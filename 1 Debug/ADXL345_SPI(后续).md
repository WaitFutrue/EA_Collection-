## [通信协议] ADXL345在不同速率下，竟然读取到不懂的ID值!

### 🛠️ 硬件/模块

- 硬件版本：ADXL345
- 相关代码：CUBEMX

### 🔍 问题现象

- 由于好久没搞毕设，打算重新温习一下，在重新配置的时候，我加入了DMA到SPI里面，但是竟然不能用，于是我开始怀疑是DMA的问题影响到了我的SPI

### ✅ 解决方案

1.  我改变了Clock Phase (CPHA)，把他改为了`2 edge` ，竟然能用了，此后无论我SPI是多少，他都可以！

### 🤔原因分析

1. 是因为ADXL345的数据手册里面就是这么要求的（😅但是当时我没看懂），以下是原文
   
   > The maximum SPI clock speed is 5 MHz with 100 pF,maximum loading, and the timing scheme follows clock polarity,(CPOL) = 1 and clock phase (CPHA) = 1
   > 
   > 但是在CUBE MX 里面他没有0和1，只有1 EDGE 和2 EDGE

### 📚 经验教训

- **系统学习** ：有时候不系统的去学习，总会遇到玄学问题！没有理论，全是玄学！！！

### ⏰ 最近更新——【2025年4月14日】（计划断更）
