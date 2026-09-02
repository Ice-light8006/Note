这里我们以学习资料最多的STM32F103C8T6为例
首先需要安装STM32CubeMX这个软件
[STM32CubeMX下载链接](https://www.st.com/content/st_com/en/stm32cubemx.html)
我们还需要一个IDE，推荐Keil_v5或者STM32CubeIDE
我们这里使用Keil_v5,网上到处都是破解资源，可以自行去搜索

然后我们进入STM32CubeMX，来看看利用STM32CubeMX配置STM32F103C8T6的步骤
首先点击ACCESS TO MCU SELECTOR
（可能会卡十几秒，稍微等待一下即可）
![](STM32CubeMX-1.png)
然后在文本框Commercial Part Number中搜索STM32F103C8T6
![](STM32CubeMX-2.png)
然后在这里点击一下STM32F103C8T6
![](STM32CubeMX-3.png)
之后点击右上角的Start Project
我们首先配置外部时钟，在System Core中点击RCC
![](STM32CubeMX-4.png)
右边有
- High Speed Clock(HSE)
- Low Speed Clock(LSE)
High Speed Clock代表高速外部时钟
Low Speed Clock代表低速外部时钟
而每个都有下面这三个可选择
- Disable
- BYPASS Clock Source
- Crystal/Ceramic Resonator
三者的对比表如下

| CubeMX 选项                   | 外面接什么      | STM32 是否参与振荡 |
| --------------------------- | ---------- | ------------ |
| `Disable`                   | 什么都不接      | 不使用 HSE/LSE  |
| `BYPASS Clock Source`       | 已经产生好的时钟信号 | 不参与，只接收      |
| `Crystal/Ceramic Resonator` | 无源晶振/陶瓷谐振器 | 参与振荡         |

可以这样理解
```
Disable
→ 不用 HSE

BYPASS
→ 别人把 Clock 直接喂给 STM32

Crystal/Ceramic Resonator
→ 给 STM32 一块晶体，STM32 自己把它振起来
```
如果你的板子上的高速晶振有很常见的**8MHz无源晶振**，那么High Speed Clock就选Crystal/Ceramic Resonator
如果你的板子上的低速晶振有很常见的**32.768kHz**无源晶振，那么Low Speed Clock就选Crystal/Ceramic Resonator
如果没有外部晶振就选Disable，即利用芯片内部自带的时钟源
这里我使用了8MHz无源晶振，High Speed Clock选Crystal/Ceramic Resonator
然后再选择SYS
![](STM32CubeMX-5.png)
右边的Debug一定不要选错，否则可能导致芯片锁死
这里选择Serial Wire
![](STM32CubeMX-6.png)
然后点击GPIO，根据你的需求配置GPIO
![](STM32CubeMX-7.png)
接着点击上面的Clock Configuration配置时钟源
![](STM32CubeMX-8.png)
如果你使用的是8MHz外部晶振，就直接像我这样配置时钟源即可
![](STM32CubeMX-9.png)
注意红框框中的九倍频，把8MHz进行9倍频得到STM32F103C8T6的最高主频72MHz
配置完时钟之后，点击上面的Project Manager，最上面有一个Project Name，输入你的项目的名字
然后配置IDE
![](STM32CubeMX-10.png)
如果你使用的是Keil，那么选择MDK-ARM
如果你使用的是STM32CubeIDE，那么选择STM32CubeIDE
我这里选择MDK-ARM
然后再点击左侧的Code Geneeator
在STM32Cube MCU packages and embedded software packs中勾选Copy only the necessary library files
![](STM32CubeMX-11.png)
这个的意思是
>只把当前工程实际需要的 HAL/CMSIS 等库文件复制到工程中，而不是把整个 STM32CubeF1 软件包复制进去。

这个作为普通工程很合适

在Generated files中勾选Generate peripheral initialization as a pair of '.c/.h' files per peripheral
![](STM32CubeMX-12.png)
这个的意思是：
不开：
```
main.c
├── GPIO 初始化
├── USART 初始化
├── SPI 初始化
└── TIM 初始化
```
勾上以后：
```
Core/
├── Src/
│   ├── main.c
│   ├── gpio.c
│   ├── usart.c
│   └── tim.c
│
└── Inc/
    ├── gpio.h
    ├── usart.h
    └── tim.h
```
也就是**按外设拆分初始化代码**，工程结构更清晰。CubeMX 官方文档对此选项的定义正是“将每个外设的初始化生成到独立的 `.c/.h` 文件中，而不是都放在 `main.c`”。

然后点击右上角的GENERATE CODE生成代码
![](STM32CubeMX-13.png)
之后会弹出一个对话窗，在这个对话窗中你可以点击在文件夹中打开，也可以点击打开项目通过IDE打开