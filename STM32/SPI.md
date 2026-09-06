SPI是Serial Peripheral Interface的缩写，翻译为中文就是“串行外设接口”
适用于高速、双向数据传输场景
SPI由四条总线组成
- MOSI
- MISO
- SCK
- NSS
# 分别解释一下这四条总线
## MOSI
MOSI是Mastert Output Slave Input的缩写
Master代表主机
Output代表输出
Slave代表从机
Input代表输入
那MOSI的意思就是主机发送从机接收
因此对于主机来说MOSI是数据发送引脚，对于从机来说MOSI是数据接收引脚
接线时我们应该将所有主机的MOSI和所有从机的MOSI连接在一起 ，主机通过这条线向从机发送数据
规则是低电压表示0，高电压表示1
## MISO
MISO是Master Input Slave Output的缩写
意思是主机接收从机发送
那么在接线时应该把主机的MISO和从机的MISO相连，主机通过MISO这条线从从机接收数据
规则是低电压表示0，高电压表示1
## SCK
SCK是Serial Clock的缩写
Serial是串行
Clock是时钟
SCK的意思是串行时钟线
接线时应该把主机的SCK和所有从机的SCK相连
在传输数据的过程中时钟信号由主机产生并通过SCK发送给从机，而且每个时钟周期发送一个位。因此时钟的频率就决定了通信速度的快慢，时钟频率越高，数据传输的速率就越快
## NSS
NSS是Negative Slave Select的缩写
Negative代表低电压有效
Slave代表从机
Select代表选择
那么NSS的意思就是从机选择线（低电压有效）
主机向对应的NSS发送低电压就可以选择对应的从机
接线过程中我们应该把主机的NSS和从机的NSS对应相连
例如主机的NSS有这几条线
```
NSS1
NSS2
NSS3
```
然后有三个设备A、B、C
A、B、C都有自己的NSS
那么，实现主机和从机A、B、C之间的SPI通信，就可以把NSS1和A的NSS连接，把NSS2和B的NSS连接，把NSS3和C的NSS连接。
假如主机想选择从机A，那么就只需要给NSS1发送低电压即可。对于从机B和C同理。
## 最终连接方式示例
![](主机引脚和从机引脚连接示例.png)
(图片来自铁头山羊的视频)

# SPI的五个参数
这五个参数分别是
- 波特率
- 比特位传输顺序（MSB First / LSB First）
- 数据位长度（8位/16位）
- 时钟的极性
- 时钟的相位
## 波特率
波特率=每秒钟传输高低电压的数量
波特率越大，数据传输的速率就越快
SPI总线没有规定波特率的范围，一般取几兆到几十兆bps
SPI波特率选取的规则
- 选择允许的最大值
- 考虑设备所能承受的极限（可以在设备的数据手册内部找到）
- 考虑电路板所能承受的极限（像正常的杜邦线、面包板连接在一起的设备一般能承受的极限是10Mbps）
## 比特位传输顺序
对于一个无符号八位整数，由八位组成：
```
bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0
```
从bit0到bit7，其权重依次为2的0次方，2的1次方，....，2的7次方
bit0称为LSB，是Least Significant Bit的缩写，最低有效位
bit7称为MSB，是Most Significant Bit的缩写，代表最高有效位
这样以来，就有了两种比特位传输顺序
- MSB First，代表先传最高有效位
- LSB First，代表先传最低有效位
实际做嵌入式开发时选择MSB First还是LSB First应该根据实际情况来分析
## 数据位长度
数据位长度分为8-bit和16-bit
### 8-bit
8位一组，每组1字节
### 16-bit
16位一组，每组1个16位整数
### 例子
假如说现在有一个数据`0xb51f`要发送，并且采用MSB First的方式来发送
如果采用8-bit的数据位长度，那么就会把这个`0xb51f`拆分为`0xb5`和`0x1f`然后分别发送
如果采用16-bit的数据位长度，就会直接把`0xb51f`直接转换为二进制数据然后发送
## 时钟极性
时钟极性有低和高
时钟极性为低时，空闲状态为低电压
时钟极性为高时，空闲状态为高电压
对于时钟极性为低时，第一边沿为上升沿，第二边沿为下降沿
对于始终极性为高时，第一边沿为下降沿，第二边沿为上升沿
## 时钟的相位
时钟的相位分为第一边沿采集和第二边沿采集
有了时钟的极性和时钟的相位，可以把时钟分为四种模式

|     | 第一边沿 | 第二边沿 |
| --- | ---- | ---- |
| 低极性 | 模式0  | 模式1  |
| 高极性 | 模式2  | 模式3  |
# STM32在CubeMX中配置SPI
在CubeMX中配置SPI时会看到一个叫Mode的选项，点击后会出现很多选项，这些选项的内容和用途如下

| CubeMX 选项 | 用途 | 典型信号线 |
| --- | --- | --- |
| `Full-Duplex Master` | 主机，全双工收发 | `SCK + MOSI + MISO + NSS/CS` |
| `Full-Duplex Slave` | 从机，全双工收发 | `SCK + MOSI + MISO + NSS` |
| `Half-Duplex Master` | 主机，单根数据线双向通信 | `SCK + 单根数据线 + NSS/CS` |
| `Half-Duplex Slave` | 从机，单根数据线双向通信 | `SCK + 单根数据线 + NSS` |
| `Receive Only Master` | 主机，只接收数据，但 STM32 仍产生时钟 | `SCK + MISO + NSS/CS` |
| `Receive Only Slave` | 从机，只接收主机发来的数据 | `SCK + MOSI + NSS` |
| `Transmit Only Master` | 主机，只发送数据 | `SCK + MOSI + NSS/CS` |
然后我们介绍下面的Configuration选项
**1. Frame Format：Motorola**

SPI 的帧格式/时序规范。STM32 常见选项有：

- `Motorola`：标准 SPI 时序，绝大多数 SPI Flash、OLED、屏幕、传感器、ADC 等都使用它。
- `TI`：TI 同步串行格式，时序和片选行为不同，只有从设备手册明确要求时才用。

一般选择：

```text
Motorola
```

---

**2. Data Size：8 Bits**

每次 SPI 传输的数据位数。

- `8 Bits`：一次发送或接收 1 字节，最常用。
- 部分外设可能要求 `16 Bits`，例如某些 DAC、音频芯片或特定传感器。

选择时以外设协议为准。对于常见寄存器读写协议，通常使用：

```text
8 Bits
```

例如发送 `0x9F` 读取 Flash JEDEC ID，本质上就是先发送一个 8 位命令字节。

---

**3. First Bit：MSB First**

规定一个字节中，哪一位最先在 `MOSI` 上发送。

- `MSB First`：先发最高位 `bit7`，即从左到右发送，例如 `1010 0101` 先发最左侧的 `1`。
- `LSB First`：先发最低位 `bit0`。

绝大多数 SPI 外设使用：

```text
MSB First
```

除非外设手册明确写了 `LSB first`，否则不要改。

---

**4. Prescaler (for Baud Rate)：2**

SPI 时钟分频系数。SPI 实际时钟为：

```text
SPI_SCK = SPI 外设时钟 PCLK / Prescaler
```

你当前是 `Prescaler = 2`，CubeMX 显示波特率为：

```text
36.0 MBit/s
```

在 STM32F103 中，SPI1 时钟来自 APB2。若 APB2 为 `72 MHz`，则：

```text
72 MHz / 2 = 36 MHz
```

可选分频一般是：

```text
2 / 4 / 8 / 16 / 32 / 64 / 128 / 256
```

需要注意：`36 MHz` 对不少外设过快。应查看从设备手册的 `SPI clock frequency` 或 `fSCK max`。

例如，若外设最高只支持 `10 MHz`，可设：

```text
Prescaler = 8
72 MHz / 8 = 9 MHz
```

建议首次调试使用较低时钟，如 `Prescaler = 64` 或 `128`；确认读写正确、示波器波形正常后，再逐步提高。

---

**5. Baud Rate：36.0 MBit/s**

这是 CubeMX 根据系统时钟和分频系数算出的 SPI 速率，严格说更接近：

```text
SCK = 36 MHz
```

对 8 位 SPI 来说，每秒大约可传输 36 Mbit 的串行位数据。它不是 UART 那种异步“波特率”概念，但 CubeMX 界面中也常这样标示。

---

**6. Clock Polarity (CPOL)：Low**

`CPOL` 决定时钟线 `SCK` 在空闲状态下的电平：

- `Low`：空闲时 `SCK = 0`
- `High`：空闲时 `SCK = 1`

你现在选了：

```text
CPOL = Low
```

所以没有传输数据时，用万用表或示波器观察 `SCK`，应保持低电平。

---

**7. Clock Phase (CPHA)：1 Edge**

`CPHA` 决定在时钟的哪个边沿采样数据。

- `1 Edge`：第一个跳变沿采样数据
- `2 Edge`：第二个跳变沿采样数据

注意：CubeMX 中的 `1 Edge` 和 `2 Edge` 指“第几个边沿”，并不是简单等同于上升沿或下降沿；具体边沿还受 `CPOL` 影响。

你当前参数为：

```text
CPOL = Low
CPHA = 1 Edge
```

这就是最常见的：

```text
SPI Mode 0
```

四种标准 SPI 模式如下：

| SPI 模式 | CPOL | CPHA | SCK 空闲状态 | 采样沿 |
|---|---:|---:|---|---|
| Mode 0 | Low | 1 Edge | 低 | 上升沿 |
| Mode 1 | Low | 2 Edge | 低 | 下降沿 |
| Mode 2 | High | 1 Edge | 高 | 下降沿 |
| Mode 3 | High | 2 Edge | 高 | 上升沿 |

不能凭经验直接选 Mode 0，必须查看外设手册。例如手册中写：

```text
CPOL = 0, CPHA = 0
```

则配置为：

```text
Clock Polarity = Low
Clock Phase = 1 Edge
```

若手册写：

```text
CPOL = 1, CPHA = 1
```

则配置为：

```text
Clock Polarity = High
Clock Phase = 2 Edge
```

---

**8. CRC Calculation：Disabled**

是否启用 SPI 硬件 CRC 校验。

- `Disabled`：不使用 CRC，最常用。
- `Enabled`：STM32 会在收发末尾处理 CRC，用于检测通信数据错误。

普通 SPI 外设通常有自己定义的校验方式，或者根本不用 CRC；此处随意启用会改变传输字节数，导致协议错误。因此一般保持：

```text
CRC Calculation = Disabled
```

只有在你明确设计 STM32 与另一台 STM32 的 SPI 通信、双方都启用了并约定了硬件 CRC 时才考虑使用。

---

**9. NSS Signal Type：Software**

`NSS` 就是 SPI 的片选信号，常标为 `CS`、`SS`、`nCS` 或 `CE`。

- `Software`：由普通 GPIO 手动控制片选。
- `Hardware`：由 SPI 外设硬件管理 NSS 引脚。

多个 SPI 从设备共享 `SCK/MOSI/MISO` 时，每个从设备都需要独立的 CS。此时最适合软件 NSS：

```c
HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET);
// SPI 收发
HAL_SPI_TransmitReceive(&hspi1, tx, rx, len, 100);
HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);
```

你的场景建议保持：

```text
NSS Signal Type = Software
```

并把外设的 `CS` 接到一个普通 GPIO，例如 `PA4`。截图中 `PA4` 是空闲的，常可作为 SPI1 外设的片选脚使用。

**对普通 SPI 外设的推荐起始配置：**

```text
Mode                 = Full-Duplex Master
Frame Format         = Motorola
Data Size            = 8 Bits
First Bit            = MSB First
Prescaler            = 64 或 128（首次联调）
CPOL                 = 按从设备手册
CPHA                 = 按从设备手册
CRC Calculation      = Disabled
NSS Signal Type      = Software
```

你当前的 `Mode 0、8 位、MSB First、Software NSS` 都是常规配置；最需要确认的是从设备支持的 **SPI 模式** 与 **最高 SCK 频率**。